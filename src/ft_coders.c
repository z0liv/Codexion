/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:29 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/09 13:30:55 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*ft_init_coders(t_hub *hub)
{
	int		counter;
	t_coder	*cod;

	counter = 0;
	while (counter < hub -> n_coders)
	{
		cod = malloc(sizeof(t_dongle));
		cod -> id = counter + 1;
		cod -> c_compiled = 0;
		cod -> last_t_compiled = 0;
		cod -> has_finish = false;
		cod -> hub = hub;
		cod -> status = STAND_BY;
		cod -> l_dongle = hub->dongles[counter];
		cod -> r_dongle = hub->dongles[(counter + 1) % hub -> n_coders];
		hub -> coders[counter] = *cod;
		pthread_mutex_init(&hub -> coders[counter].coder_mutext, NULL);
		counter ++;
	}
	return (NULL);
}
