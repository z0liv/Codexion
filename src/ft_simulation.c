/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:44:05 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/10 13:43:37 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_get_sim_status(t_hub *hub)
{
	bool	status;

	pthread_mutex_lock(&hub -> hub_mutex);
	status = hub -> simulation_end;
	pthread_mutex_unlock(&hub -> hub_mutex);
	return (status);
}

void	ft_set_sim_status(t_hub *hub, bool value)
{
	pthread_mutex_lock(&hub -> hub_mutex);
	hub -> simulation_end = value;
	pthread_mutex_unlock(&hub -> hub_mutex);
}

void	ft_start_simulation(t_hub *hub)
{
	int			counter;
	pthread_t 	monitor;

	hub -> start_time = ft_get_time_ms();
	counter = 0;
	while (counter < hub -> n_coders)
	{
		hub -> coders[counter].last_t_compiled = hub -> start_time;
		if (pthread_create(
			&hub -> coders[counter].thread,
			NULL, ft_coder_routine, &hub -> coders[counter]) != 0)
			return ;
		counter ++;
	}
	if (pthread_create(&monitor, NULL, ft_monitor_routine, hub) != 0)
		return ;
	pthread_join(monitor, NULL);
	counter = 0;
	while(counter < hub -> n_coders)
	{
		pthread_join(hub -> coders[counter].thread, NULL);
		counter ++;
	}
	return ;
}
