/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:55:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/04 15:47:54 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

int parse_each_arch_32(t_obj *obj, struct fat_arch *arch)
{

    t_obj tmp;
    // if (!(tmp = (t_obj *)ft_memalloc(sizeof(t_obj) + 1)))
	// 	return (errors_fd(__FILE__, 1, Err));
    if (!(tmp.data = check_sizeoff_move(obj, obj->data, arch->offset)))
    {
        return (errors_fd("test for each tempo 32 : \n", 1, Err));
    };
    tmp.size_data = arch->size;
    tmp.path = obj->path;
    if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)) || nm(&tmp))
        return (errors_fd("Error From Eacg tempo : ", 1, Err));

    return 0;
}

int for_each_arch_32(t_obj *obj, struct fat_arch *arch, struct fat_header *fat_header)
{

    // t_obj tmp;
    uint32_t index;
    // struct fat_arch *tempo;

    index = 0;
    // tempo = arch;
    while (index < fat_header->nfat_arch)
    {
        if (parse_each_arch_32(obj, arch))
        {
            // return (errors_fd("test for each tempo 32 : \n", 1, Err));
        }
        // if(!(tmp.data = check_sizeoff_move(obj, obj->data, tempo->offset))) {
        //     return (errors_fd("test for each tempo 32 : ", 1, Err));
        // };
        // tmp.size_data = tempo->size;
        // tmp.path = obj->path;
        // if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)) || nm(&tmp))
        // return (errors_fd("Error From Eacg tempo : ", 1, Err));
        if (!(arch = check_sizeoff_move(obj, arch, sizeof(struct fat_arch))))
            return (errors_fd("error  Handle_64 ARCH : ", 1, Err));
        index++;
    }

    return 0;
}

int parse_fat_arch_32(t_obj *obj, struct fat_header *ft)
{
    struct fat_arch *arch;

    if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_header))))
        return (errors_fd("error  Handle_64 ARCH", 1, Err));
    if (!obj->swap && arch != NULL)
        swap_fat_arch(arch);
    return (for_each_arch_32(obj, arch, ft));
}
int handle_fat_32(t_obj *obj)
{
    struct fat_header fat_header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct fat_header)))
        return (errors_fd("ERROR SizeOff", 1, Err));
    fat_header = *(struct fat_header *)obj->data;
    if (!obj->swap)
        swap_fat_header(&fat_header);
    return (parse_fat_arch_32(obj, &fat_header));
    // return(errors_fd("CA MARCHE", 1, Ok));

    // return 0;
}

int for_each_arch_64(t_obj *obj, struct fat_arch_64 *arch, struct fat_header *ft)
{
    (void)ft;

    t_obj tmp;

    tmp.data = check_sizeoff_move(obj, obj->data, arch->offset);
    if (!tmp.data)
    {
        return (errors_fd("test for each arch 64", 1, Err));
    }
    tmp.size_data = arch->size;
    tmp.path = obj->path;
    if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)))
        return (errors_fd("Error From Eag Arch", 1, Err));
    return 0;
}

int parse_fat_arch_64(t_obj *obj, struct fat_header *ft)
{
    struct fat_arch_64 *arch;

    if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_arch_64))))
        return (errors_fd("error  Handle_64 ARCH", 1, Err));
    if (!obj->swap)
        swap_fat_arch_64(arch);
    return (for_each_arch_64(obj, arch, ft));
}

int handle_fat_64(t_obj *obj)
{
    struct fat_header fat_header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct fat_header)))
        return (errors_fd("ERROR SizeOff", 1, Err));
    fat_header = *(struct fat_header *)obj->data;
    if (!obj->swap)
        swap_fat_header(&fat_header);
    return (parse_fat_arch_64(obj, &fat_header));
}
