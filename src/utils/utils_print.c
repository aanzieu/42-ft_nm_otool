/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:54:05 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:36:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

char	ntype_if_upper(char c, uint8_t ntype)
{
	if (ntype & N_EXT)
		return (ft_toupper(c));
	if (c == 'c' || c == 'u')
		return ('?');
	return (c);
}
