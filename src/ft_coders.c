/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:29 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 17:48:27 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	ft_cleanup_codermutex(t_hub *hub, int count)
{
	while (-- count >= 0)
		pthread_mutex_destroy(&hub -> coders[count].coder_mutex);
	return (false);
}

bool	ft_init_coders(t_hub *hub)
{
	int		counter;
	t_coder	*cod;

	counter = 0;
	while (counter < hub -> n_coders)
	{
		cod = &hub -> coders[counter];
		cod -> id = counter + 1;
		cod -> c_compiled = 0;
		cod -> has_finish = false;
		cod -> hub = hub;
		cod -> status = STAND_BY;
		cod -> l_dongle = &hub->dongles[counter];
		cod -> r_dongle = &hub->dongles[(counter + 1) % hub -> n_dongles];
		if (pthread_mutex_init(&hub -> coders[counter].coder_mutex, NULL) != 0)
			return (ft_cleanup_codermutex(hub, counter));
		counter ++;
	}
	return (true);
}
