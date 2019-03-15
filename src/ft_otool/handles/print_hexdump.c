/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexdump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:56:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/15 14:27:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"

void		print_hexadump(char *start, uint16_t nb, t_bool space, t_bool swap)
{
	uint16_t	i;

    (void)space;
    (void)swap;
	// if (space)
	// 	return (print_hex_space(start, nb, swap));
	i = 1;
	while (i <= nb)
	{
        ft_putnbr_ll_base((0x000000f0 & (*(char *)start)) >> 4, "0123456789abcdef", 1);
		ft_putnbr_ll_base((0x0000000f & (*(char *)start)), "0123456789abcdef", 1);
		if (!space || (i / 4 && !(i % 4)))
			ft_putchar(' ');
		start++;
		i++;
	}
}