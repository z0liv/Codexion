/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_shutdown.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:27:35 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/02 13:40:44 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// TODO: clean all coders array and dongles array with aux func.
void	*ft_clean_shutdown(t_hub *hub)
{
	if (hub)
	{
		pthread_mutex_destroy(&hub -> print_mutex);
		pthread_mutex_destroy(&hub -> hub_mutex);
		free(hub);
	}
	return (NULL);
}
