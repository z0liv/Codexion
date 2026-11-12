/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:45:26 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/12 13:49:11 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_handle_monitor_fail(t_hub *hub, int counter, int created)
{
	ft_set_sim_status(hub, true);
	pthread_mutex_lock(&hub->hub_mutex);
	pthread_cond_broadcast(&hub->start_cond);
	pthread_mutex_unlock(&hub->hub_mutex);
	counter = 0;
	while (counter < created)
	{
		pthread_join(hub->coders[counter].thread, NULL);
		counter++;
	}
}

int	ft_create_coders_threads(t_hub *hub, int counter)
{
	int	created;

	created = 0;
	while (counter < hub->n_coders)
	{
		if (pthread_create(&hub->coders[counter].thread,
				NULL, ft_coder_routine,
				&hub->coders[counter]) != 0)
			break ;
		counter++;
		created++;
	}
	return (created);
}
