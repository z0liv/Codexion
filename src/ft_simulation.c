/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:44:05 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/03 13:05:14 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_get_sim_status(t_hub *hub)
{
	bool	status;

	pthread_mutex_lock(&hub -> hub_mutex);
	status = hub -> simulation_end;
	pthread_mutex_unlock(&hub -> hub_mutex);
	return (status);
}

void	ft_set_sim_status(t_hub *hub, bool value)
{
	pthread_mutex_lock(&hub -> hub_mutex);
	hub -> simulation_end = value;
	pthread_mutex_unlock(&hub -> hub_mutex);
}
