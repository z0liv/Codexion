NAME = codexion

CC = cc
FLAGS = -pthread -Wall -Wextra -Werror
OBJS_DIR = ./objs

SRCS = src/codexion.c \
	src/ft_data_initializer.c \
	src/ft_data_validator.c \
	src/ft_parser.c \
	src/ft_atol.c \
	src/ft_is_valid_input.c \
	src/ft_isdigit.c \
	src/ft_heap.c \
	src/ft_heap_utils.c \
	src/ft_dongles.c \
	src/ft_dongles_utils.c \
	src/ft_coders.c \
	src/ft_simulation.c \
	src/ft_logs.c \
	src/ft_coder_routine.c \
	src/ft_monitor_routine.c \
	src/ft_clean_shutdown.c \
		
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) -o $@ $^

run: $(NAME)
	clear
	./codexion

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
