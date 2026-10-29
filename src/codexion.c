/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/29 13:29:18 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_hub	*data;

	if (argc != 9)
		return (write(2, "program expects 7 arguments", 27));
	data = malloc(sizeof(t_hub));
	if (!data)
		return (free(data), 0);
	ft_data_initializer(argc, argv, data);
	if (!ft_data_validator(data))
		return (free(data), 0);
	printf("n_coders: %ld\n", data -> n_coders);
	printf("scheduler: %s\n", data -> scheduler);
	return (free(data), 0);
}
