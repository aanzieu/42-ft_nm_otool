/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkoff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 09:15:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 11:16:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

int check_sizeoff(t_obj *obj, const void *start, size_t size)
{
    uint8_t s;
    int64_t d;

    s = (unsigned char *)start - (unsigned char *)obj->data;
    d = (obj->data + obj->size_data) - (start + size);
    if (obj->size_data < s + size || d < 0)
        return 0;
    return 1;
}

void    *check_sizeoff_move(t_obj *obj, const void *start, size_t size)
{
    if (check_sizeoff(obj, start, size))
    {
        return ((void*)start + size);
    }
    return NULL;
}