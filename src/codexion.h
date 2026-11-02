/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:54:04 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/02 09:49:53 by omarquez         ###   ########.fr       */
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

int		ft_data_validator(t_hub *data);
int		ft_isdigit(int c);
long	ft_parser(char *arg);
long	ft_atol(const char *str);
bool	ft_is_valid_input(char *str);
void	ft_data_initializer(int len, char **args, t_hub *data);

#endif
