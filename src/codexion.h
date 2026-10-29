/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:54:04 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/29 13:28:43 by omarquez         ###   ########.fr       */
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
	TOOK_R_DONGLE,
	TOOK_L_DONGLE,
}	t_coder_status;

typedef struct e_request
{
	int		coder_id;
	long	request_time;
	long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*queue;
	int			capacity;
	int			size;
	int			is_edf;
}	t_heap;

typedef struct s_hub
{
	long			n_coders;
	long			n_dongles;
	long			n_comp_req;
	long			t_burn;
	long			t_debug;
	long			t_comp;
	long			t_refact;
	long			t_d_cooldown;
	char			*scheduler;
	pthread_mutex_t	dongles;
	pthread_mutex_t	printed_actions;
	pthread_mutex_t	hub_mutex;
}					t_hub;

typedef struct s_coder
{
	pthread_t			thread;
	long				id;
	long				c_compiled;
	long				last_c_compiled;
	long				is_burnout;
	long				has_finish;
	long				left_dongle;
	long				right_dongle;
	pthread_mutex_t		l_dongle;
	pthread_mutex_t		r_dongle;
}						t_coder;

int		ft_data_validator(t_hub *data);
int		ft_isdigit(int c);
long	ft_parser(char *arg);
long	ft_atol(const char *str);
bool	ft_is_valid_input(char *str);
void	ft_data_initializer(int len, char **args, t_hub *data);

#endif
