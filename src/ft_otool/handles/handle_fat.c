/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:37:59 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 11:52:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

int get_header_fat(t_obj *input, void const *add,
                   struct fat_header *header)
{
    if (check_sizeoff(input, add, sizeof(struct mach_header_64)))
    {
        *header = *(struct fat_header *)add;
        if (!input->swap)
            swap_fat_header(header);
        return (0);
    }
    return (1);
}

int handle_fat_32(t_obj *obj)
{
    struct fat_header header;

    if (get_header_fat(obj, obj->data, &header))
    {
        return (errors_fd(MALFORMED,
                          "(offset field of Fat-Header not past)", 1, Err));
    }
    return (parse_fat_arch_32(obj, &header));
}

int handle_fat_64(t_obj *obj)
{
    struct fat_header header;

    if (get_header_fat(obj, obj->data, &header))
    {
        return (errors_fd(MALFORMED,
                          "(offset field of Fat-Header not past)", 1, Err));
    }
    return (parse_fat_arch_64(obj, &header));
}