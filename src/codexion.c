/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/02 10:23:04 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_handle_n_args(void)
{
	fprintf(stderr, "All arguments are mandatory\n");
	fprintf(stderr, "You must run:\n");
	fprintf(stderr, "./codexion <coders> <time_to_burnout> <time_to_compile>");
	fprintf(stderr, " <time_to_debug> <time_to_refactor>");
	fprintf(stderr, " <nb_compiles_required> <dongle_cooldown> <scheduler>\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_hub	*data;

	if (argc != 9)
		return (ft_handle_n_args());
	data = malloc(sizeof(t_hub));
	if (!data)
		return (free(data), 0);
	ft_data_initializer(argc, argv, data);
	if (!ft_data_validator(data))
		return (free(data), 0);
	printf("n_coders: %lld\n", data -> n_coders);
	printf("scheduler: %s\n", data -> scheduler);
	printf("is_edf: %d\n", data -> is_edf);
	return (free(data), 0);
}
