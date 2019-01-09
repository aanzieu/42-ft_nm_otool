/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/09 11:00:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check every number magic

#include "../../../include/ft_nm.h"

void	*secure_add(t_arch input, const void *start_add, size_t length)
{
	int64_t		diff;
	uint8_t		start;

	start = (uint8_t *)start_add - (uint8_t *)input.data;
	diff = (input.data + input.length) - (start_add + length);
	if (start + length > input.length || diff < 0)
		return (NULL);
	return ((void *)start_add);
}

uint32_t	get_magic(t_arch *input)
{
	if (secure_add(*input, input->data, sizeof(uint32_t)))
	{
		input->magic = (*(uint32_t *)input->data);
		if (input->magic == MH_CIGAM || input->magic == MH_CIGAM_64
												|| input->magic == FAT_CIGAM)
			input->is_swap = True;
		else
			input->is_swap = False;
		return (*(uint32_t *)input->data);
	}
	return (0);
}

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