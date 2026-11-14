/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:45:26 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/14 15:24:07 by omarquez         ###   ########.fr       */
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
	int	count;

	created = 0;
	count = 0;
	while (count < hub -> n_coders)
	{
		hub->coders[count].last_t_compiled = hub->start_time;
		hub->coders[count].status = STAND_BY;
		hub->coders[count].has_finish = false;
		count ++;
	}
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
