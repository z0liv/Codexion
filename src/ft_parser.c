/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:24:01 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/28 10:00:01 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_parser(char *arg)
{
	long	num;

	if (!ft_is_valid_input(arg))
		return (0);
	num = ft_atol(arg);
	return (num);
}
