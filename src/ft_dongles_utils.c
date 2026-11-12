/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dongles_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:09:56 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/12 15:37:37 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_cleanup_dongles(t_hub *hub, int count)
{
	while (-- count >= 0)
	{
		pthread_mutex_destroy(&hub -> dongles[count].mutex);
		pthread_cond_destroy(&hub -> dongles[count].cond);
		ft_heap_destroy(&hub -> dongles[count].queue);
	}
	return (false);
}

t_dongle	*ft_decide_dongle(t_coder *coder, bool min)
{
	if (min)
	{
		if (coder -> l_dongle -> id < coder -> r_dongle -> id)
			return (coder -> l_dongle);
		return (coder -> r_dongle);
	}
	else
	{
		if (coder -> l_dongle -> id > coder -> r_dongle -> id)
			return (coder -> l_dongle);
		return (coder -> r_dongle);
	}
}

bool	ft_can_take_both(t_coder *coder, t_dongle *first, t_dongle *second)
{
	long long	now;

	if (first == second)
		return (false);
	now = ft_get_time_ms();
	if (first -> is_in_use || second -> is_in_use)
		return (false);
	if (now < first -> available_at || now < second -> available_at)
		return (false);
	if (ft_heap_check(&first->queue).coder_id != coder -> id)
		return (false);
	if (ft_heap_check(&second->queue).coder_id != coder -> id)
		return (false);
	return (true);
}

void	ft_take_both_locked(t_coder *coder, t_dongle *first, t_dongle *second)
{
	first->is_in_use = true;
	second->is_in_use = true;
	ft_heap_pop(&first->queue);
	ft_heap_pop(&second->queue);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	ft_log_action(coder, "has taken a dongle");
	ft_log_action(coder, "has taken a dongle");
}
