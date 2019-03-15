/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:42:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/15 13:39:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void	swap_section(struct section *s, uint32_t nsects)
{
	uint32_t i;

	i = 0;
	while (i < nsects)
	{
		s[i].addr = ft_swap_uint32(s[i].addr);
		s[i].size = ft_swap_uint32(s[i].size);
		s[i].offset = ft_swap_uint32(s[i].offset);
		s[i].align = ft_swap_uint32(s[i].align);
		s[i].reloff = ft_swap_uint32(s[i].reloff);
		s[i].nreloc = ft_swap_uint32(s[i].nreloc);
		s[i].flags = ft_swap_uint32(s[i].flags);
		s[i].reserved1 = ft_swap_uint32(s[i].reserved1);
		s[i].reserved2 = ft_swap_uint32(s[i].reserved2);
		i++;
	}
}

void	swap_section_64(struct section_64 *s, uint32_t nsects)
{
	uint32_t i;

	i = 0;
	while (i < nsects)
	{
		s[i].addr = ft_swap_uint64(s[i].addr);
		s[i].size = ft_swap_uint64(s[i].size);
		s[i].offset = ft_swap_int32(s[i].offset);
		s[i].align = ft_swap_int32(s[i].align);
		s[i].reloff = ft_swap_int32(s[i].reloff);
		s[i].nreloc = ft_swap_int32(s[i].nreloc);
		s[i].flags = ft_swap_int32(s[i].flags);
		s[i].reserved1 = ft_swap_int32(s[i].reserved1);
		s[i].reserved2 = ft_swap_int32(s[i].reserved2);
		s[i].reserved3 = ft_swap_int32(s[i].reserved3);
		i++;
	}
}
