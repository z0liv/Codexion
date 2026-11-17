/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:05:41 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/17 19:42:23 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_err_msg(char *param)
{
	fprintf(stderr, "[ERROR] %s should be a valid integer.\n", param);
	return (1);
}

static int	ft_validate_props(t_hub *data)
{
	if (data->n_coders < 1)
		return (ft_err_msg("number_of_coders"));
	if (data->t_burn < 1)
		return (ft_err_msg("time_to_burnout"));
	if (data->t_comp < 0)
		return (ft_err_msg("time_to_compile"));
	if (data->t_debug < 0)
		return (ft_err_msg("time_to_debug"));
	if (data->t_refact < 0)
		return (ft_err_msg("time_to_refact"));
	if (data->n_comp_req < 1)
		return (ft_err_msg("number_of_compiles_required"));
	if (data->t_d_cooldown < 0)
		return (ft_err_msg("dongle_cooldown"));
	return (0);
}

int	ft_data_validator(t_hub *data)
{
	if (ft_validate_props(data) > 0)
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
