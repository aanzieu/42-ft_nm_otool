/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/08 16:13:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check every number magic

#include "ft_nm.h"

void    nm(char *ptr)
{
    unsigned int magic_number;

    magic_number = *(unsigned int *)ptr;
    if (magic_number == MH_MAGIC_64)
    {
        puts("binaire 64");
        handle_64(ptr);
    }
}

// #define FAT_MAGIC	0xcafebabe
// #define FAT_CIGAM	0xbebafeca	/* NXSwapLong(FAT_MAGIC) */
// #
// power pc - PPC (32-64)
// 