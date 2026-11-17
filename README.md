*This project has been created as part of the 42 curriculum by omarquez*

# Codexion

## Description

Codexion is a concurrency and resource-synchronization simulation written in C, inspired by the classic Dining Philosophers problem. In this scenario, multiple coders sit around a circular co-working space sharing a central Quantum Compiler and a limited number of USB dongles (one placed between each pair of adjacent coders).

To compile their quantum code, a coder must simultaneously acquire both their left and right USB dongles. Once compilation finishes, they release both dongles and transition through debugging and refactoring phases before attempting to compile again. If a coder fails to start compiling within their time_to_burnout threshold, they burn out and the simulation halts.

The primary goal of this project is to master POSIX threads (pthread), mutexes, condition variables, and deterministic priority scheduling (FIFO and EDF — Earliest Deadline First) using custom binary heaps, ensuring deadlock freedom, starvation prevention, cooldown enforcement, and sub-10ms burnout detection precision.

## Instructions

### Compilation

The project includes a Makefile at the root of the repository that compiles the source files using cc with -Wall -Wextra -Werror -pthread.

To build the executable, run:
```
make
```
Additional Makefile rules available:

- **```make clean```**: Removes object files.

- **```make fclean```**: Removes object files and the codexion binary.

- **```make re```**: Recompiles the entire project from scratch.

### Execution

Run the program with the 8 mandatory arguments:
```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

### Parameters
1. `number_of_coders`: Total number of coders (and USB dongles).
2. `time_to_burnout`: Maximum time (in ms) a coder can go without starting a compilation before burning out.
3. `time_to_compile`: Duration (in ms) of the compiling phase while holding two dongles.
4. `time_to_debug`: Duration (in ms) of the debugging phase.
5. `time_to_refactor`: Duration (in ms) of the refactoring phase.
6. `number_of_compiles_required`: Target number of compilations per coder to successfully conclude the simulation.
7. `dongle_cooldown`: Cooldown period (in ms) after a dongle is released before it can be acquired again.
8. `scheduler`: Arbitration policy for dongle priority queues (`fifo` or `edf`).

#### Usage Examples
```bash
# 5 coders: EDF scheduling, 200ms compile, 100ms debug/refactor, 5 compiles, 0ms cooldown
./codexion 5 610 200 100 100 5 0 edf

# 4 coders: FIFO scheduling, 200ms compile, 150ms debug/refactor, 3 compiles, 50ms cooldown
./codexion 4 800 200 150 150 3 50 fifo

# Balanced run: 4 coders with EDF scheduling (should complete without burnout)
./codexion 4 1000 200 100 150 5 50 edf

# Single coder: Should burn out immediately as only 1 dongle is available
./codexion 1 800 200 100 100 3 0 fifo

# Tight burnout: 5 coders with strict timing margins under EDF scheduling
./codexion 5 610 200 100 100 5 0 edf

# Impossible timing: Burnout deadline shorter than a full compile/debug/refactor cycle
./codexion 3 300 200 100 100 5 10 fifo

# Odd count: 5 coders under FIFO scheduling to stress resource fairness
./codexion 5 800 200 200 200 7 0 fifo

# Long cooldown: 4 coders with 400ms dongle cooldown under EDF scheduling
./codexion 4 1000 100 100 100 5 400 edf

# Stress test: 200 coders running concurrently under EDF scheduling
./codexion 200 1000 100 100 100 3 10 edf
```
## Blocking Cases Handled

To guarantee liveness and strict compliance with the simulation constraints, the following concurrency hazards are explicitly handled:

1. **Deadlock Prevention (Coffman's Conditions):**
   * **Circular Wait & Hold-and-Wait:** Broken through **resource hierarchy ordering** (always ordering dongle locks by ascending dongle ID) combined with **atomic dual-dongle acquisition**. A coder never holds one dongle while waiting indefinitely for the second; instead, a coder only claims both dongles when it is at the top of the priority queue for *both* left and right dongles simultaneously and both are free of cooldown.
2. **Starvation Prevention:**
   * **FIFO Policy:** Requests are served strictly in arrival order using monotonic request timestamps/sequence counters inside a min-heap.
   * **EDF Policy:** Requests are prioritized by the earliest burnout deadline (`last_compile_start + time_to_burnout`). Ties in deadlines are deterministically broken using the coder's unique ID to ensure predictable, starvation-free scheduling under feasible parameters.
3. **Dongle Cooldown Enforcement:**
   * When a coder finishes compiling and releases their dongles, each dongle records its `available_at` timestamp (`current_time + dongle_cooldown`). Waiting threads verify the cooldown expiration before acquiring a dongle and use timed waits (`pthread_cond_timedwait`) or wake-up broadcasts to avoid busy-waiting.
4. **Precise Burnout Detection (< 10 ms):**
   * A dedicated monitor thread continuously inspects each coder's `last_compile_start` timestamp at high-frequency intervals (e.g., 500–1000 µs). Upon detecting `current_time - last_compile_start >= time_to_burnout`, it immediately updates the shared simulation stop flag, broadcasts to all condition variables to unblock waiting coders, and prints the burnout log within the 10 ms tolerance window.
5. **Log Serialization:**
   * All standard output logging is guarded by a dedicated `log_mutex` alongside a check on the simulation active flag, preventing interleaved characters and ensuring no state transitions are printed after a burnout event is announced.

---

## Thread Synchronization Mechanisms

The implementation relies on standard POSIX threading primitives to coordinate state across coder threads and the monitor thread without data races:

* **`pthread_mutex_t`:**
  * **Dongle / Arbitration Mutexes:** Protect dongle availability states, cooldown timestamps, and access to each dongle's binary min-heap priority queue.
  * **Coder State Mutexes:** Protect individual coder metrics (`last_compile_start` and `compile_count`) read by the monitor thread and updated by the coder thread.
  * **Start Barrier Mutex (`start_mutex`):** Synchronizes thread startup so all coders begin executing at the exact same `start_time` baseline once `pthread_create` has completed for every thread.
  * **Log & Simulation State Mutex (`log_mutex` / `sim_mutex`):** Serializes `printf` calls and safely guards reads/writes to the global `simulation_stopped` flag.
* **`pthread_cond_t`:**
  * **Start Condition (`start_cond`):** Holds newly spawned coder threads at the entry barrier until the main thread broadcasts that initialization is complete.
  * **Dongle Wait Queues (`dongle_cond` / `pthread_cond_wait`):** Allows coders waiting for dongle availability, priority turns, or cooldown expirations to sleep efficiently without burning CPU cycles, waking up immediately when a neighbor releases dongles, a cooldown expires, or the monitor signals simulation termination.

### Thread-Safe Communication Flow (Coders ↔ Monitor)
When a coder acquires both `l_dongle` and `r_dongle`, it locks `coder_mutex`, updates `last_t_compiled` with the current timestamp (and increments `c_compiled`), and unlocks `coder_mutex` before logging `is compiling`. Simultaneously, the monitor thread locks each coder's `coder_mutex` to safely read `last_t_compiled`, `c_compiled`, and `has_finish`. If a coder burns out or all coders reach `n_comp_req`, the monitor locks `hub_mutex` in `t_hub`, sets `simulation_end = true`, and triggers `pthread_cond_broadcast` across all dongle waiting queues so every blocked thread exits cleanly and joins without deadlocks or memory leaks.

## Resources
- [Basic guide for pthread](https://medium.com/@dipakkardel93/getting-started-with-threads-in-c-using-pthread-create-and-pthread-join-95e2a59808b1)
- [Mutexes in C](https://medium.com/@sherniiazov.da/mutexes-in-c-ac2b0f1a6d34)
- [POSIX](https://en.wikipedia.org/wiki/POSIX)
- [How to implement thread safe queues](https://stackoverflow.com/questions/10721148/how-to-implement-thread-safe-queues)
- [Helper Web App to visualize the simulation](https://codexion-visualizer.sacha-dev.me/)

### AI Usage Disclosure
In accordance with the 42 AI guidelines, AI tools were used strictly as a learning and debugging assistant for the following tasks:
* **Concurrency & Log Analysis:** Assisting in diagnosing race conditions, non-atomic dongle acquisition, and thread startup desynchronization by comparing execution traces against expected visualizer behavior.
* **Documentation:** Structuring and formatting the sections of this `README.md` to ensure clarity and completeness against project requirements.
* All core C algorithms, binary heap data structures, memory management, and POSIX synchronization primitives were manually implemented, tested, and verified.
