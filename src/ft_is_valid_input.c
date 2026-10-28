/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 09:21:27 by omarquez          #+#    #+#             */
/*   Updated: 2026/10/28 09:55:52 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_is_valid_input(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == ' '
			|| str[counter] == '-'
			|| str[counter] == '+')
		{
			if ((str[counter] == '-'
					&& (str[counter + 1] && !ft_isdigit(str[counter + 1])))
				|| (str[counter] == '+'
					&& (str[counter + 1] && !ft_isdigit(str[counter + 1]))))
				return (false);
			counter ++;
		}
		else if (!ft_isdigit(str[counter]))
			return (false);
		else
			counter ++;
	}
	if (ft_atol(str) > 2147483647
		|| ft_atol(str) < -2147483648)
		return (false);
	return (true);
}
