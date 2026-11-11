/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:52:37 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 18:56:20 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// TODO?: malloc fail?, clean shutdown.

bool	ft_heap_init(t_heap *heap, int capacity, bool is_edf)
{
	heap -> queue = malloc(sizeof(t_request) * capacity);
	if (!heap->queue)
		return (false);
	heap -> capacity = capacity;
	heap -> size = 0;
	heap -> is_edf = is_edf;
	return (true);
}

void	ft_heap_destroy(t_heap *heap)
{
	if (heap -> queue)
	{
		free(heap -> queue);
		heap -> queue = NULL;
	}
	heap -> size = 0;
	heap -> capacity = 0;
}

void	ft_heap_push(t_heap *heap, t_request req)
{
	int			counter;
	int			parent;
	t_request	tmp;

	if (heap -> size >= heap -> capacity)
		return ;
	counter = heap -> size;
	heap -> queue[counter] = req;
	heap -> size++;
	while (counter > 0)
	{
		parent = (counter - 1) / 2;
		if (ft_check_priority(
				heap -> queue[counter],
				heap -> queue[parent],
				heap -> is_edf))
		{
			tmp = heap -> queue[counter];
			heap -> queue[counter] = heap -> queue[parent];
			heap -> queue[parent] = tmp;
			counter = parent;
		}
		else
			break ;
	}
}

// if size is <= 0 should return an empty request.
t_request	ft_heap_pop(t_heap *heap)
{
	t_request	root;
	t_request	tmp;
	int			current;
	int			next;

	if (heap -> size <= 0)
		return ((t_request){0});
	root = heap -> queue[0];
	heap -> queue[0] = heap -> queue[heap -> size - 1];
	heap -> size --;
	current = 0;
	while (1)
	{
		next = ft_get_highest_child(heap, current);
		if (next == current)
			break ;
		tmp = heap -> queue[current];
		heap -> queue[current] = heap -> queue[next];
		heap -> queue[next] = tmp;
		current = next;
	}
	return (root);
}

// return an empty request
t_request	ft_heap_check(t_heap *heap)
{
	if (heap -> size > 0)
		return (heap -> queue[0]);
	return ((t_request){0});
}
