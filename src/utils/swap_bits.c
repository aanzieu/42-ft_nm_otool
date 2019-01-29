/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 09:19:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 08:56:28 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

uint16_t	ft_swap_int16(uint16_t x)
{
	return (((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
}