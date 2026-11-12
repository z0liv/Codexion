/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:44:05 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/12 13:45:51 by omarquez         ###   ########.fr       */
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

static void	ft_open_start_gate(t_hub *hub)
{
	int	counter;

	pthread_mutex_lock(&hub -> hub_mutex);
	counter = 0;
	while (counter < hub -> n_coders)
	{
		pthread_mutex_lock(&hub -> coders[counter].coder_mutex);
		hub -> coders[counter].last_t_compiled = hub -> start_time;
		pthread_mutex_unlock(&hub -> coders[counter].coder_mutex);
		counter ++;
	}
	hub -> ready_to_start = true;
	pthread_cond_broadcast(&hub -> start_cond);
	pthread_mutex_unlock(&hub -> hub_mutex);
}

bool	ft_start_simulation(t_hub *hub)
{
	int			counter;
	int			created;
	pthread_t	monitor;

	counter = 0;
	hub -> start_time = ft_get_time_ms();
	created = ft_create_coders_threads(hub, counter);
	if (pthread_create(&monitor, NULL, ft_monitor_routine,
			hub) != 0)
	{
		ft_handle_monitor_fail(hub, counter, created);
		return (false);
	}
	ft_open_start_gate(hub);
	pthread_join(monitor, NULL);
	counter = 0;
	while (counter < hub->n_coders)
	{
		pthread_join(hub->coders[counter].thread, NULL);
		counter++;
	}
	return (true);
}
