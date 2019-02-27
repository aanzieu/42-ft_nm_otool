/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 09:19:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/11 11:25:11 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

//! Byte ft_swap unsigned short
uint16_t ft_swap_uint16(uint16_t val)
{
	return (val << 8) | (val >> 8);
}

//! Byte ft_swap short
int16_t ft_swap_int16(int16_t val)
{
	return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte ft_swap unsigned int
uint32_t ft_swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

//! Byte ft_swap int
int32_t ft_swap_int32(int32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | ((val >> 16) & 0xFFFF);
}

//! Byte ft_swap int64
int64_t ft_swap_int64(int64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

//! Byte ft_swap unsigned int 64
uint64_t ft_swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

//   union {
//         uint64_t ll;
//         uint32_t l[2];
//     } w, r;
//     w.ll = x;
//     r.l[0] = bswap_32 (w.l[1]);
//     r.l[1] = bswap_32 (w.l[0]);
//     return r.ll;
