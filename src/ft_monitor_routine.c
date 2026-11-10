/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:11:12 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/10 10:38:48 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	ft_check_burnout(t_hub *hub, t_coder *coder)
{
	long long	now;
	long long	last_start;

	now = ft_get_time_ms();
	pthread_mutex_lock(&coder -> coder_mutext);
	last_start = coder -> last_t_compiled;
	pthread_mutex_unlock(&coder -> coder_mutext);
	if (now - last_start > hub -> t_burn)
	{
		ft_set_sim_status(hub, true);
		ft_log_action(coder, "burned out");
		return (true);
	}
	ft_log_action(coder, "burned out");
	return (false);
}

static bool	ft_check_all_finished(t_hub *hub)
{
	int	counter;
	int	finished_count;

	if (hub -> n_comp_req <= 0)
		return (false);
	finished_count = 0;
	counter = 0;
	while (counter < hub -> n_coders)
	{
		pthread_mutex_lock(&hub -> coders[counter].coder_mutext);
		if (hub -> coders[counter].c_compiled >= hub -> n_comp_req)
			finished_count ++;
		pthread_mutex_unlock(&hub -> coders[counter].coder_mutext);
	}
	if (finished_count == hub -> n_coders)
	{
		ft_set_sim_status(hub, true);
		return (true);
	}
	return (false);
}

static void	ft_wake_up_all_dongles(t_hub *hub)
{
	int	counter;

	counter = 0;
	while (counter < hub -> n_coders)
	{
		pthread_mutex_lock(&hub -> dongles[counter].mutex);
		pthread_cond_broadcast(&hub -> dongles[counter].cond);
		pthread_mutex_unlock(&hub -> dongles[counter].mutex);
		counter ++;
	}
}

void	*ft_monitor_routine(void *arg)
{
	t_hub	*hub;
	int		counter;

	hub = (t_hub *) arg;
	while (!ft_get_sim_status(hub))
	{
		counter = 0;
		while (counter < hub -> n_coders)
		{
			if (ft_check_burnout(hub, &hub -> coders[counter]))
			{
				ft_wake_up_all_dongles(hub);
				return (NULL);
			}
			counter ++;
		}
		if (ft_check_all_finished(hub))
		{
			ft_wake_up_all_dongles(hub);
			return (NULL);
		}
		ft_precise_usleep(1000, hub);
	}
	return (NULL);
}
