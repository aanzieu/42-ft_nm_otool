/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/11 11:49:30 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check every number magic

#include "../../../include/ft_nm.h"
// #include <arch.h>

uint32_t get_magic_number(t_obj *obj)
{
    obj->magic = 42;

    if (check_sizeoff(obj, obj->data, sizeof(uint32_t)))
        obj->magic = *(uint32_t *)obj->data;
    return obj->magic;
}

int find_header_type(t_obj *obj)
{
    uint32_t mg;

    mg = get_magic_number(obj);
    if (mg == MH_CIGAM || mg == MH_CIGAM_64 || mg == FAT_CIGAM)
        obj->swap = True;
    else
        obj->swap = False;
    return mg;
}

int choose_handler(t_obj *obj, uint32_t mg)
{
    if (mg == MH_CIGAM_64)
		return handle_64(obj); //return (M_64);
	// else if (obj->magic == MH_MAGIC || obj->magic == MH_CIGAM)
		// return handle_32(obj); //return (M_32);
	// else if (obj->magic == FAT_MAGIC || obj->magic == FAT_CIGAM)
		// handle_fat_32(obj); //return (M_FAT);
	// else if (obj->magic == FAT_CIGAM_64 || obj->magic == FAT_MAGIC_64)
		// handle_fat_64(obj); //return (M_FAT_64);
	// else if (secure_add(*arch, arch->data, SARMAG) &&
				// !ft_strncmp(ARMAG, (char *)arch->data, SARMAG))
		// return (M_LIB);
	return (False);
}

int nm(t_obj *obj)
{
    uint32_t head;

    head = find_header_type(obj);
    if (head == 42)
    {
        puts("not valid binaire");
        return (False);
    }
    return choose_handler(obj, obj->magic);
}