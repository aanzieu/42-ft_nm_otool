/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:55:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/06 15:24:57 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"



int handle_fat_32(t_obj *obj)
{
    struct fat_header fat_header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct fat_header)))
        return (errors_fd(MALFORMED, "(offset field of Fat-Header not past)", 1, Err));
    fat_header = *(struct fat_header *)obj->data;
    if (!obj->swap)
        swap_fat_header(&fat_header);
    return (parse_fat_arch_32(obj, &fat_header));
}

///////---------////


int handle_fat_64(t_obj *obj)
{
    struct fat_header fat_header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct fat_header)))
        return (errors_fd(MALFORMED, "(offset field of Fat-Header not past)", 1, Err));
    fat_header = *(struct fat_header *)obj->data;
    if (!obj->swap)
        swap_fat_header(&fat_header);
    return (parse_fat_arch_64(obj, &fat_header));
}
