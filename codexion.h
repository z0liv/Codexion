/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:54:04 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/12 13:40:30 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int		n_coders;
	int		n_dongles;
	int		n_comp_req;
	int		t_burn;
	int		t_debug;
	int		t_comp;
	int		t_refact;
	int		t_d_cooldown;
	char	*scheduler;
}			t_data;

int	parser(char *arg);

#endif
