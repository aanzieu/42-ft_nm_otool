/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkoff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 09:15:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/26 13:42:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

int check_sizeoff(t_obj *obj, const void *start, size_t size)
{
    uint8_t s;
    int64_t d;

    s = (unsigned char *)start - (unsigned char *)obj->data;
    d = (obj->data + obj->size_data) - (start + size);
    if (obj->size_data < s + size || d < 0)
        return Ok;
    return Err;
}

void *check_sizeoff_move(t_obj *obj, const void *start, size_t size)
{
    if (check_sizeoff(obj, start, size))
        return ((void *)start + size);
    return NULL;
}

char *checkoff_string(t_obj *obj, char *str, uint32_t off)
{
    char *ret;
    size_t i;

    i = 0;
    if (!(ret = check_sizeoff_move(obj, (void *)str, off)))
        return (NULL);
    while (ret && check_sizeoff(obj, (void *)ret, i))
    {
        if (!check_sizeoff(obj, (void *)ret, i))
            return (NULL);
        i++;
    }
    return (ret);
}