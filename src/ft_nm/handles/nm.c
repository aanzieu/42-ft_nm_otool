/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/09 10:30:10 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check every number magic

#include "../../../include/ft_nm.h"

void nm(void *ptr)
{
    uint32_t magic_number;

    magic_number = (*(uint32_t *)ptr);
    dprintf(1, "toto\n");
    if (magic_number == MH_MAGIC_64)
    {
        puts("binaire 64");
        // handle_64(ptr);
    }
    else if (magic_number == MH_MAGIC)
    {
        puts("binaire 32");
        // handle_64(ptr);
    }
    else if (magic_number == MH_CIGAM_64)
    {
        puts("Swap 64");
        // handle_64(ptr);
    }
    else if (magic_number == MH_CIGAM)
    {
        puts("Swap 32");
        // handle_64(ptr);
    }
    else if (magic_number == FAT_MAGIC_64)
    {
        puts("FAT 64");
        // handle_64(ptr);
    }
    else if (magic_number == FAT_MAGIC)
    {
        puts("FAT 32");
        // handle_64(ptr);
    }
    else if (magic_number == FAT_CIGAM_64)
    {
        puts("FAT swap 64");
        // handle_64(ptr);
    }
    else if (magic_number == FAT_CIGAM)
    {
        puts("FAT swap 32");
        // handle_64(ptr);
    }
    else
    {
        puts("not valid binaire");
    }
}

// #define FAT_MAGIC	0xcafebabe
// #define FAT_CIGAM	0xbebafeca	/* NXSwapLong(FAT_MAGIC) */
// #
// power pc - PPC (32-64)
//