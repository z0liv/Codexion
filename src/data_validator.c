/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:05:41 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/14 13:22:17 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	validate_data(t_hub *data)
{
	if (data -> n_coders < 1
		|| data -> n_dongles < 1
		|| data -> n_comp_req < 1
		|| data -> t_burn < 1
		|| data -> t_debug < 1
		|| data -> t_comp < 1
		|| data -> t_refact < 1
		|| data -> t_d_cooldown < 1)
		return (0);
	if (strcmp("fifo", data -> scheduler) != 0
		&& strcmp("edf", data -> scheduler) != 0)
		return (0);
	return (1);
}
