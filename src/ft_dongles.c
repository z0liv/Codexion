/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dongles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:33 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/04 13:19:04 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*ft_init_dongles(t_hub *hub)
{
	int			counter;
	t_dongle	*dngl;

	counter = 0;
	while (counter < hub -> n_dongles)
	{
		dngl = malloc(sizeof(t_dongle));
		dngl -> id = counter;
		dngl -> is_in_use = false;
		dngl -> available_at = 0;
		hub -> dongles[counter] = *dngl;
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
	t_dongle	first;
	t_dongle	second;

	first = ft_decide_dongle(coder, true);
	second = ft_decide_dongle(coder, false);
}
