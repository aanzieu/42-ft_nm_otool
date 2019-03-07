/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typechar_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:56:39 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/07 15:31:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/ft_nm.h"


/**
 * Print search Char type
 * */
static char find_sect_type_64(t_seg_list list, t_obj *obj)
{
    if ((int)list.n_sect == obj->tss)
        return (ntype_if_upper('t', list.n_type));
    else if ((int)list.n_sect == obj->dss)
        return (ntype_if_upper('d', list.n_type));
    else if ((int)list.n_sect == obj->bss)
        return (ntype_if_upper('b', list.n_type));
    return (ntype_if_upper('s', list.n_type));
}

char get_char_type_64(t_seg_list seg_list, t_obj *obj)
{
    int type;

    type = seg_list.n_type & N_TYPE;
    if ((type == N_UNDF || type == N_PBUD) && seg_list.n_sect == NO_SECT)
    {
        if (seg_list.n_value && type != N_PBUD)
            return (ntype_if_upper('c', seg_list.n_type));
        return (ntype_if_upper('u', seg_list.n_type));
    }
    else if (type == N_ABS)
        return (ntype_if_upper('a', seg_list.n_type));
    else if (type == N_SECT && seg_list.n_sect != NO_SECT && seg_list.n_sect <= MAX_SECT)
        return (find_sect_type_64(seg_list, obj));
    else if (type == N_INDR)
        return (ntype_if_upper('i', seg_list.n_type));
    return (ntype_if_upper('?', seg_list.n_type));
}