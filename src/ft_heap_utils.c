/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:07:14 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/12 13:27:16 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_check_priority(t_request req1, t_request req2, bool is_edf)
{
	if (is_edf)
	{
		if (req1.deadline != req2.deadline)
			return (req1.deadline < req2.deadline);
		if ((req1.coder_id % 2) != (req2.coder_id % 2))
			return (req1.coder_id % 2 == 1);
	}
	if (req1.request_time != req2.request_time)
		return (req1.request_time < req2.request_time);
	return (req1.coder_id < req2.coder_id);
}

int	ft_get_highest_child(t_heap *heap, int i)
{
	int	left;
	int	right;
	int	best;

	left = 2 * i + 1;
	right = 2 * i + 2;
	best = i;
	if (left < heap -> size
		&& ft_check_priority(
			heap -> queue[left],
			heap -> queue[best],
			heap -> is_edf))
		best = left;
	if (right < heap -> size
		&& ft_check_priority(
			heap -> queue[right],
			heap -> queue[best],
			heap -> is_edf))
		best = right;
	return (best);
}

void	ft_push_request(
	t_coder *coder, t_dongle *dongle,
	long long req_time, long long deadline)
{
	t_request	req;

	pthread_mutex_lock(&dongle -> mutex);
	req.coder_id = coder -> id;
	req.request_time = req_time;
	req.deadline = deadline;
	ft_heap_push(&dongle -> queue, req);
	pthread_mutex_unlock(&dongle -> mutex);
}
