/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coder_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 13:06:15 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 19:01:52 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	ft_set_coder_status(t_coder *coder, t_coder_status status)
{
	pthread_mutex_lock(&coder -> coder_mutex);
	coder -> status = status;
	pthread_mutex_unlock(&coder -> coder_mutex);
}

void	ft_compile_phase(t_coder *coder)
{
	pthread_mutex_lock(&coder -> coder_mutex);
	coder -> last_t_compiled = ft_get_time_ms();
	coder -> status = COMPILING;
	pthread_mutex_unlock(&coder -> coder_mutex);
	ft_log_action(coder, "is compiling");
	ft_precise_usleep(coder -> hub->t_comp, coder -> hub);
	pthread_mutex_lock(&coder -> coder_mutex);
	coder -> c_compiled ++;
	if (coder -> c_compiled >= coder -> hub -> n_comp_req)
		coder -> has_finish = true;
	pthread_mutex_unlock(&coder -> coder_mutex);
}

void	ft_debug_phase(t_coder *coder)
{
	ft_set_coder_status(coder, DEBUGGING);
	ft_log_action(coder, "is debugging");
	ft_precise_usleep(coder -> hub -> t_debug, coder -> hub);
}

void	ft_refact_phase(t_coder *coder)
{
	ft_set_coder_status(coder, REFACTORING);
	ft_log_action(coder, "is refactoring");
	ft_precise_usleep(coder -> hub -> t_refact, coder -> hub);
}

void	*ft_coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder -> hub -> hub_mutex);
	while (!coder -> hub -> ready_to_start && !coder -> hub -> simulation_end)
		pthread_cond_wait(&coder -> hub -> start_cond, &coder -> hub -> hub_mutex);
	pthread_mutex_unlock(&coder -> hub -> hub_mutex);
	while (!ft_get_sim_status(coder -> hub))
	{
		ft_acquire_dongles(coder);
		if (ft_get_sim_status(coder -> hub))
			break ;
		ft_compile_phase(coder);
		ft_release_dongles(coder);
		if (coder -> hub -> n_comp_req > 0
			&& coder -> c_compiled >= coder -> hub -> n_comp_req)
			break ;
		ft_debug_phase(coder);
		ft_refact_phase(coder);
		ft_set_coder_status(coder, STAND_BY);
	}
	return (NULL);
}
