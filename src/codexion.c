/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/14 13:14:02 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_hub	*data;

	if (argc != 9)
		return (0);
	data = malloc(sizeof(t_hub));
	init_data(argc, argv, data);
	if (!validate_data(data))
		return (free(data), 0);
	printf("n_coders: %ld\n", data -> n_coders);
	printf("scheduler: %s\n", data -> scheduler);
	return (free(data), 0);
}
