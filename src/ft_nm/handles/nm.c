/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:07:21 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 09:30:33 by aanzieu          ###   ########.fr       */
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
        return 1;
    return mg;
}

void choose_handler(t_obj *obj, uint32_t mg)
{
    if (mg == MH_MAGIC_64)// || mg == MH_CIGAM_64)
        handle_64(obj);
    else if (mg == MH_MAGIC || mg == MH_CIGAM)
        handle_32(obj);
    // else if (mg == FAT_MAGIC || mg == FAT_CIGAM)
    // else if (mg == FAT_CIGAM_64 || mg == FAT_MAGIC_64)
}

void nm(t_obj *obj)
{
    uint32_t head;

    head = find_header_type(obj);
    if (head == 42)
    {
        puts("not valid binaire");
        exit(EXIT_FAILURE);
    }
    else if (head == 1)
    {
        swap_magic();
    }
    choose_handler(obj, obj->magic);
}