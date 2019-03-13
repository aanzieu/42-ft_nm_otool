/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:53:45 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:20:52 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

uint16_t	ifswap16(t_obj *obj, uint16_t x)
{
	if (!obj->swap)
		return (ft_swap_int16(x));
	return (x);
}

uint32_t	ifswap32(t_obj *obj, uint32_t x)
{
	if (!obj->swap)
		return (ft_swap_uint32(x));
	return (x);
}

uint64_t	ifswap64(t_obj *obj, uint64_t x)
{
	if (!obj->swap)
		return (ft_swap_int64(x));
	return (x);
}
