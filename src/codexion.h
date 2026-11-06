/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:54:04 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/06 10:06:59 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_status
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNED_OUT,
	TOOK_DONGLE,
}	t_coder_status;

typedef struct e_request
{
	int			coder_id;
	long long	request_time;
	long long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*queue;
	int			capacity;
	int			size;
	bool		is_edf;
}	t_heap;

typedef struct s_dongle
{
	int				id;
	bool			is_in_use;
	long long		available_at;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_heap			queue;
}					t_dongle;

typedef struct s_coder
{
	pthread_t			thread;
	long long			id;
	long long			c_compiled;
	long long			last_c_compiled;
	bool				has_finish;
	t_dongle			l_dongle;
	t_dongle			r_dongle;
	pthread_mutex_t		coder_mutext;
	struct s_hub		*hub;
}						t_coder;

typedef struct s_hub
{
	bool			is_edf;
	bool			simulation_end;
	char			*scheduler;
	long long		n_coders;
	long long		n_dongles;
	long long		n_comp_req;
	long long		t_burn;
	long long		t_debug;
	long long		t_comp;
	long long		t_refact;
	long long		t_d_cooldown;
	long long		start_time;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	hub_mutex;
}					t_hub;

/* Parse and validations */
int			ft_data_validator(t_hub *data);
int			ft_isdigit(int c);
long		ft_parser(char *arg);
long		ft_atol(const char *str);
bool		ft_is_valid_input(char *str);
void		ft_data_initializer(int len, char **args, t_hub *data);

/* Heap Functions */
bool		ft_heap_init(t_heap *heap, int capacity, bool is_edf);
void		ft_heap_destroy(t_heap *heap);
void		ft_heap_push(t_heap *heap, t_request req);
t_request	ft_heap_pop(t_heap *heap);
t_request	ft_heap_check(t_heap *heap);

int			ft_get_highest_child(t_heap *heap, int i);
bool		ft_check_priority(t_request req1, t_request req2, bool is_edf);

/* Dongles Functions */
void		*ft_init_dongles(t_hub *hub);
void		ft_acquire_dongles(t_coder *coder);
void		ft_acquire_one_dongle(t_coder *coder, t_dongle *dongle);
t_dongle	ft_decide_dongle(t_coder *coder, bool min);

/* Logs Functions */
long long	ft_get_time_ms(void);
void		ft_log_action(t_coder *coder, char *msg);
void		ft_precise_usleep(long long time_in_ms, t_hub *hub);

/* Coder Functions */
void		*ft_init_coders(t_hub *hub);

/* Hub Functions */
bool		ft_get_sim_status(t_hub *hub);
void		ft_set_sim_status(t_hub *hub, bool value);

/* Cleanup functions */
void		*ft_clean_shutdown(t_hub *data);

#endif
