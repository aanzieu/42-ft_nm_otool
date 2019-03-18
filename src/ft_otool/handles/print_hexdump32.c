/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexdump32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:56:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 11:56:33 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"

static void		print_number(char number[8], t_bool swap)
{
	int		index;

	if (!swap)
	{
		index = 0;
		while (index < 8)
		{
			ft_putnbr_ll_base(number[index], "0123456789abcdef", 1);
			ft_putnbr_ll_base(number[index + 1], "0123456789abcdef", 1);
			index += 2;
		}
	}
	else
	{
		index = 7;
		while (index > 0)
		{
			ft_putnbr_ll_base(number[index - 1], "0123456789abcdef", 1);
			ft_putnbr_ll_base(number[index], "0123456789abcdef", 1);
			index -= 2;
		}
	}
}

static void		print_hex_space(char *start, uint16_t nb, t_bool swap)
{
	char		number[8];
	uint16_t	i;
	int			k;

	ft_memset(number, 0, 8);
	i = 1;
	k = 0;
	while (i <= nb)
	{
		if (k == 8)
		{
			print_number(number, swap);
			k = 0;
		}
		number[k] = (0x000000f0 & (*(char *)start)) >> 4;
		number[k + 1] = (0x0000000f & (*(char *)start));
		if (i / 4 && !(i % 4) && i != 4)
			ft_putchar(' ');
		start++;
		i++;
		k += 2;
	}
	print_number(number, swap);
	ft_putchar(' ');
}

static void		print_hexadump(char *start, uint16_t nb, t_bool space, t_bool swap)
{
	uint16_t	i;

	if (space)
		return (print_hex_space(start, nb, swap));
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

int print_hex_32(t_obj *obj, void *start, struct section section)
{
    uint32_t index;
    uint16_t nb_print;
    t_bool space;
  
    index = 0;
    space = !(obj->cputype == CPU_TYPE_I386 || obj->cputype == CPU_TYPE_X86_64);
    ft_putstr_fd("Contents of (__TEXT,__text) section\n", 1);
    while (index < section.size)
    {
		ft_putnbr_ll_base(section.addr + index, "0123456789abcdef", 8);
        ft_putchar_fd('\t', 1);
        nb_print = (section.size - index) <= 16 ? (section.size - index) : 16;
        print_hexadump(start + index, nb_print, space, obj->swap);
        ft_putchar('\n');
        index = index + 16;
    }
    return 0;
}

