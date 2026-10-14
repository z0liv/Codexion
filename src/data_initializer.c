/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:06:21 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/14 13:23:49 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_data(int len, char **args, t_hub *data)
{
	int		counter;

	counter = 1;
	while (counter < len)
	{
		if (counter == 1)
		{
			data -> n_coders = atoi(args[counter]);
			data -> n_dongles = atoi(args[counter++]);
		}
		else if (counter == 2)
			data -> t_burn = atoi(args[counter++]);
		else if (counter == 3)
			data -> t_comp = atoi(args[counter++]);
		else if (counter == 4)
			data -> t_debug = atoi(args[counter++]);
		else if (counter == 5)
			data -> t_refact = atoi(args[counter++]);
		else if (counter == 6)
			data -> n_comp_req = atoi(args[counter++]);
		else if (counter == 7)
			data -> t_d_cooldown = atoi(args[counter++]);
		else if (counter == 8)
			data -> scheduler = args[counter++];
	}
}
