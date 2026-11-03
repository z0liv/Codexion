/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:52:37 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/03 13:08:21 by omarquez         ###   ########.fr       */
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
