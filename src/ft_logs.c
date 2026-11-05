/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:21:58 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/05 12:10:01 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	ft_get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((
			((long long)tv.tv_sec * 1000) + ((long long)tv.tv_usec / 1000))
	);
}

void	ft_log_action(t_coder *coder, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&coder -> hub -> print_mutex);
	if (!ft_get_sim_status(coder -> hub) || strcmp(msg, "burned out") == 0)
	{
		timestamp = ft_get_time_ms() - coder -> hub -> start_time;
		printf("%lld %lld %s\n", timestamp, coder -> id, msg);
	}
	pthread_mutex_unlock(&coder -> hub -> print_mutex);
}
