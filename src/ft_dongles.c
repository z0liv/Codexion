/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dongles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:33 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/12 15:17:20 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_init_dongles(t_hub *hub)
{
	int			counter;
	t_dongle	*dngl;

	counter = 0;
	while (counter < hub -> n_dongles)
	{
		dngl = &hub -> dongles[counter];
		dngl -> id = counter;
		dngl -> is_in_use = false;
		dngl -> available_at = 0;
		if (pthread_mutex_init(&hub -> dongles[counter].mutex, NULL) != 0)
			return (ft_cleanup_dongles(hub, counter));
		if (pthread_cond_init(&hub -> dongles[counter].cond, NULL) != 0)
			return (ft_cleanup_dongles(hub, counter));
		if (!ft_heap_init(
				&hub -> dongles[counter].queue,
				hub -> n_dongles,
				hub -> is_edf))
			return (ft_cleanup_dongles(hub, counter));
		counter ++;
	}
	return (true);
}

static void	ft_wait_and_take_dongle(t_coder *coder, t_dongle *dongle)
{
	long long	wait_time;

	pthread_mutex_lock(&dongle -> mutex);
	while (true)
	{
		if (ft_get_sim_status(coder -> hub))
		{
			pthread_mutex_unlock(&dongle -> mutex);
			return ;
		}
		if (ft_heap_check(&dongle -> queue).coder_id != coder->id
			|| dongle -> is_in_use)
		{
			pthread_cond_wait(&dongle -> cond, &dongle -> mutex);
			continue ;
		}
		wait_time = dongle -> available_at - ft_get_time_ms();
		if (wait_time > 0)
		{
			pthread_mutex_unlock(&dongle -> mutex);
			if (wait_time > 1)
				usleep((wait_time - 1) * 1000);
			else
				usleep(100);
			pthread_mutex_lock(&dongle -> mutex);
			continue ;
		}
		break ;
	}
	dongle -> is_in_use = true;
	ft_heap_pop(&dongle -> queue);
	pthread_mutex_unlock(&dongle -> mutex);
	ft_log_action(coder, "has taken a dongle");
}

void	ft_acquire_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	long long	req_time;
	long long	deadline;

	first = ft_decide_dongle(coder, true);
	second = ft_decide_dongle(coder, false);
	req_time = ft_get_time_ms();
	pthread_mutex_lock(&coder -> coder_mutex);
	deadline = coder -> last_t_compiled + coder -> hub -> t_burn;
	pthread_mutex_unlock(&coder -> coder_mutex);
	ft_push_request(coder, first, req_time, deadline);
	ft_push_request(coder, second, req_time, deadline);
	ft_wait_and_take_dongle(coder, first);
	ft_wait_and_take_dongle(coder, second);
}

static void	ft_release_one_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle -> mutex);
	dongle -> available_at = ft_get_time_ms() + coder -> hub -> t_d_cooldown;
	dongle -> is_in_use = false;
	pthread_cond_broadcast(&dongle -> cond);
	pthread_mutex_unlock(&dongle -> mutex);
}

void	ft_release_dongles(t_coder *coder)
{
	ft_release_one_dongle(coder, coder -> l_dongle);
	ft_release_one_dongle(coder, coder -> r_dongle);
}
