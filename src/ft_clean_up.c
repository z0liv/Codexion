/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:27:35 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 18:11:49 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	ft_clean_dongles(t_hub *hub)
{
	int	counter;

	counter = 0;
	if (hub -> dongles)
	{
		while(counter < hub -> n_dongles)
		{
			pthread_mutex_destroy(&hub -> dongles[counter].mutex);
			pthread_cond_destroy(&hub -> dongles[counter].cond);
			ft_heap_destroy(&hub -> dongles[counter].queue);
			counter ++;
		}
		free(hub -> dongles);
	}
}

static void	ft_clean_coders(t_hub *hub)
{
	int counter;

	counter = 0;
	if (hub -> coders)
	{
		counter = 0;
		while(counter < hub -> n_coders)
		{
			pthread_mutex_destroy(&hub -> coders[counter].coder_mutex);
			counter ++;
		}
		free(hub -> coders);
	}
}

void	*ft_clean_up(t_hub *hub)
{
	if (!hub)
		return (NULL);
	ft_clean_dongles(hub);
	ft_clean_coders(hub);
	pthread_mutex_destroy(&hub -> print_mutex);
	pthread_mutex_destroy(&hub -> hub_mutex);
	pthread_cond_destroy(&hub -> start_cond);
	free(hub);
	return (NULL);
}
