/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:24:01 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/17 15:12:18 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_parser(char *arg)
{
	long	num;

	if (!ft_is_valid_input(arg))
		return (-1);
	num = ft_atol(arg);
	return (num);
}
