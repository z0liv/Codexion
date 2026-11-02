/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/02 13:39:11 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*ft_hub_init(t_hub *hub)
{
	hub -> coders = malloc(sizeof(t_coder) * hub -> n_coders);
	if (!hub -> coders)
		return (ft_clean_shutdown(hub), NULL);
	hub -> dongles = malloc(sizeof(t_dongle) * hub -> n_dongles);
	if (!hub -> dongles)
		return (ft_clean_shutdown(hub), NULL);
	pthread_mutex_init(&hub -> print_mutex, NULL);
	pthread_mutex_init(&hub -> hub_mutex, NULL);
}

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
	t_hub	*hub;

	if (argc != 9)
		return (ft_handle_n_args());
	hub = malloc(sizeof(t_hub));
	if (!hub)
		return (free(hub), 0);
	ft_data_initializer(argc, argv, hub);
	if (!ft_data_validator(hub))
		return (free(hub), 0);
	printf("n_coders: %lld\n", hub -> n_coders);
	printf("scheduler: %s\n", hub -> scheduler);
	printf("is_edf: %d\n", hub -> is_edf);
	return (free(hub), 0);
}
