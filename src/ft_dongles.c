/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dongles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:33 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 16:35:41 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*ft_init_dongles(t_hub *hub)
{
	int			counter;
	t_dongle	dngl;

	counter = 0;
	while (counter < hub -> n_dongles)
	{
		dngl.id = counter;
		dngl.is_in_use = false;
		dngl.available_at = 0;
		hub -> dongles[counter] = dngl;
		pthread_mutex_init(&hub -> dongles[counter].mutex, NULL);
		pthread_cond_init(&hub -> dongles[counter].cond, NULL);
		if (ft_heap_init(
				&hub -> dongles[counter].queue,
				hub -> n_dongles,
				hub -> is_edf) != true)
			return (NULL);
		counter ++;
	}
	return (NULL);
}

void	ft_acquire_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = ft_decide_dongle(coder, true);
	second = ft_decide_dongle(coder, false);
	ft_acquire_one_dongle(coder, first);
	ft_acquire_one_dongle(coder, second);
}

void	ft_acquire_one_dongle(t_coder *coder, t_dongle *dongle)
{
	t_request	req;
	long long	wait_time;

	pthread_mutex_lock(&dongle -> mutex);
	req.coder_id = coder -> id;
	req.request_time = ft_get_time_ms();
	req.deadline = coder -> last_t_compiled;
	ft_heap_push(&dongle -> queue, req);
	while (true)
	{
		if (ft_get_sim_status(coder -> hub))
		{
			pthread_mutex_unlock(&dongle -> mutex);
			return ;
		}
		if (ft_heap_check(&dongle -> queue).coder_id != coder->id || dongle -> is_in_use)
		{
			pthread_cond_wait(&dongle -> cond, &dongle -> mutex);
			continue ;
		}
		if (ft_get_time_ms() < dongle -> available_at)
		{
			wait_time = dongle -> available_at - ft_get_time_ms();
			pthread_mutex_unlock(&dongle -> mutex);
			if (wait_time > 0)
				usleep(wait_time * 1000);
			pthread_mutex_lock(&dongle -> mutex);
			continue ;
		}
		break ;
	}
	ft_heap_pop(&dongle -> queue);
	dongle -> is_in_use = true;
	pthread_mutex_unlock(&dongle -> mutex);
	ft_log_action(coder, "has taken a dongle");
}

void	ft_release_dongles(t_coder *coder)
{
	ft_release_one_dongle(coder, coder -> l_dongle);
	ft_release_one_dongle(coder, coder -> r_dongle);
}

void	ft_release_one_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle -> mutex);
	dongle -> available_at = ft_get_time_ms() + coder -> hub -> t_d_cooldown;
	dongle -> is_in_use = false;
	pthread_cond_broadcast(&dongle -> cond);
	pthread_mutex_unlock(&dongle -> mutex);
}
