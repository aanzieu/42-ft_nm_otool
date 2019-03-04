/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/04 11:57:26 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static uint32_t get_magic_number(t_obj *obj)
{
    obj->magic = 42;

    if (check_sizeoff(obj, obj->data, sizeof(uint32_t)))
        obj->magic = *(uint32_t *)obj->data;
    return obj->magic;
}

static int find_header_type(t_obj *obj)
{
    uint32_t mg;

    mg = get_magic_number(obj);
    if (mg == MH_CIGAM || mg == MH_CIGAM_64 || mg == FAT_CIGAM)
        obj->swap = True;
    else
        obj->swap = False;
    return mg;
}

static int choose_handler(t_obj *obj, uint32_t mg)
{
    if (mg == MH_MAGIC_64 || mg == MH_CIGAM_64)
        return handle_64(obj); //return (M_64);
    else if (obj->magic == MH_MAGIC || obj->magic == MH_CIGAM)
        return handle_32(obj); //return (M_32);
    else if (obj->magic == FAT_MAGIC || obj->magic == FAT_CIGAM)
        return handle_fat_32(obj); //return (M_FAT);
    else if (obj->magic == FAT_CIGAM_64 || obj->magic == FAT_MAGIC_64)
        return handle_fat_64(obj); //return (M_FAT_64);
    
    puts("chooser hnadnerl");
    return (Err);
}

int nm(t_obj *obj)
{
    uint32_t head;

    head = find_header_type(obj);
    if (head == 42)
    {
        puts("not valid binaire");
        return (Err);
    }
    return choose_handler(obj, obj->magic);
}