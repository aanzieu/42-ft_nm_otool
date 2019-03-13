/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:38:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:38:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

uint16_t		ft_swap_uint16(uint16_t val)
{
	return (val << 8) | (val >> 8);
}

uint32_t		ft_swap_uint32(uint32_t x)
{
	return (((x & 0xff000000) >> 24) | \
			((x & 0x00ff0000) >> 8) | \
			((x & 0x0000ff00) << 8) | \
			((x & 0x000000ff) << 24));
}

uint64_t		ft_swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL)
		| ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL)
		| ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}
