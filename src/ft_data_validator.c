/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:05:41 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/14 15:18:46 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_helper(t_hub *data)
{
	if (data -> n_coders < 1)
		return (fprintf(stderr, "number_of_coders can't be less than 1.\n"));
	else if (data -> t_burn < 1)
		return (fprintf(stderr, "time_to_burnout can't be less than 1.\n"));
	else if (data -> t_comp < 0)
		return (fprintf(stderr, "time_to_compile can't be less than 0.\n"));
	else if (data -> t_debug < 0)
		return (fprintf(stderr, "time_to_debug can't be less than 0.\n"));
	else if (data -> t_refact < 0)
		return (fprintf(stderr, "time_to_refact can't be less than 0.\n"));
	else if (data -> n_comp_req < 1)
	{
		fprintf(stderr, "number_of_compiles_required ");
		return (fprintf(stderr, "can't be less than 1.\n"));
	}
	else if (data -> t_d_cooldown < 0)
		return (fprintf(stderr, "dongle_cooldown can't be less than 0.\n"));
	return (0);
}

int	ft_data_validator(t_hub *data)
{
	if (ft_helper(data) > 0)
		return (0);
	if (strcmp("fifo", data -> scheduler) == 0)
		data -> is_edf = false;
	else if (strcmp("edf", data -> scheduler) == 0)
		data -> is_edf = true;
	else if (strcmp("fifo", data -> scheduler) != 0
		&& strcmp("edf", data -> scheduler) != 0)
	{
		fprintf(stderr, "[ERROR] invalid scheduler.\n");
		fprintf(stderr, "[ERROR] scheduler must be 'fifo' or 'edf'.\n");
		return (0);
	}
	return (1);
}
