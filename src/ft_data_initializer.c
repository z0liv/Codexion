/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_initializer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:06:21 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 16:27:43 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_data_initializer(int len, char **args, t_hub *hub)
{
	int		counter;

	counter = 1;
	while (counter < len)
	{
		if (counter == 1)
		{
			hub -> n_coders = ft_parser(args[counter++]);
			hub -> n_dongles = hub -> n_coders;
		}
		else if (counter == 2)
			hub -> t_burn = ft_parser(args[counter++]);
		else if (counter == 3)
			hub -> t_comp = ft_parser(args[counter++]);
		else if (counter == 4)
			hub -> t_debug = ft_parser(args[counter++]);
		else if (counter == 5)
			hub -> t_refact = ft_parser(args[counter++]);
		else if (counter == 6)
			hub -> n_comp_req = ft_parser(args[counter++]);
		else if (counter == 7)
			hub -> t_d_cooldown = ft_parser(args[counter++]);
		else if (counter == 8)
			hub -> scheduler = args[counter++];
	}
}
