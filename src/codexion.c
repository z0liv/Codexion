/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 09:53:02 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/14 15:21:07 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*ft_init_hub(t_hub *hub)
{
	hub -> coders = malloc(sizeof(t_coder) * hub -> n_coders);
	if (!hub -> coders)
		return (NULL);
	memset(hub -> coders, 0, sizeof(t_coder) * hub -> n_coders);
	hub -> dongles = malloc(sizeof(t_dongle) * hub -> n_dongles);
	if (!hub -> dongles)
		return (NULL);
	memset(hub -> dongles, 0, sizeof(t_dongle) * hub -> n_dongles);
	if (pthread_mutex_init(&hub -> print_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&hub -> hub_mutex, NULL) != 0)
		return (NULL);
	if (pthread_cond_init(&hub -> start_cond, NULL) != 0)
		return (NULL);
	if (!ft_init_dongles(hub))
		return (NULL);
	if (!ft_init_coders(hub))
		return (NULL);
	hub -> start_time = 0;
	hub -> ready_to_start = false;
	hub -> simulation_end = false;
	return ((void *)hub);
}

static int	ft_handle_n_args(void)
{
	fprintf(stderr, "All arguments are mandatory\n");
	fprintf(stderr, "You must run:\n");
	fprintf(stderr, "./codexion <coders> <time_to_burnout> <time_to_compile>");
	fprintf(stderr, " <time_to_debug> <time_to_refactor>");
	fprintf(stderr, " <nb_compiles_required> <dongle_cooldown> <scheduler>\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_hub	*hub;

	if (argc != 9)
		return (ft_handle_n_args());
	hub = malloc(sizeof(t_hub));
	if (!hub)
		return (1);
	ft_data_initializer(argc, argv, hub);
	if (!ft_data_validator(hub))
		return (free(hub), 1);
	if (!ft_init_hub(hub))
		return (ft_clean_up(hub), 1);
	if (!ft_start_simulation(hub))
		return (ft_clean_up(hub), 1);
	ft_clean_up(hub);
	return (0);
}
