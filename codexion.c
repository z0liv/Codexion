/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/12 13:47:15 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		counter;

	counter = 1;
	if (argc < 2)
		return (0);
	else if (argc != 9)
		printf("Wrong parameters");
	while(counter < argc)
	{
		if (counter == 1)
		{
			data.n_coders = atoi(argv[counter]);
			data.n_dongles = atoi(argv[counter]);
		}
		else if (counter == 2)
			data.t_burn = atoi(argv[counter]);
		else if (counter == 3)
			data.t_comp = atoi(argv[counter]);
		else if (counter == 4)
			data.t_debug = atoi(argv[counter]);
		else if (counter == 5)
			data.t_refact = atoi(argv[counter]);
		else if (counter == 6)
			data.n_comp_req = atoi(argv[counter]);
		else if (counter == 7)
			data.t_d_cooldown = atoi(argv[counter]);
		else if (counter == 8)
			if (!strncmp("fifo", argv[counter], 5)
				&& !strncmp("edf", argv[counter], 5))
				return (0);
			data.scheduler = argv[counter];
		counter ++;
	}
	printf("n_coders = %d \n", data.n_coders);
	printf("scheduler = %s \n", data.scheduler);
	return (0);
}
