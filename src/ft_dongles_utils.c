/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dongles_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:09:56 by omarquez          #+#    #+#             */
/*   Updated: 2026/11/11 13:12:19 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*ft_decide_dongle(t_coder *coder, bool min)
{
	if (min)
	{
		if (coder -> l_dongle -> id < coder -> r_dongle -> id)
			return (coder -> l_dongle);
		return (coder -> r_dongle);
	}
	else
	{
		if (coder -> l_dongle -> id > coder -> r_dongle -> id)
			return (coder -> l_dongle);
		return (coder -> r_dongle);
	}
}
