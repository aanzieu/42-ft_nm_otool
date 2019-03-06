/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:12:03 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/06 15:29:42 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int parse_loads_commands_64(t_obj *obj)
{
    uint32_t i;
    struct load_command *lc;

    i = 0;
    obj->index_sec = 1;
    lc = obj->lc;
    while (i < obj->ncmds)
    {
        if (!obj->swap)
            swap_load_commands(lc);
        if (parse_load_command_64(obj, lc))
            return Err;
        if (!(lc = check_sizeoff_move(obj, lc, lc->cmdsize)))
            return (errors_fd(MALFORMED, ERR_LC, 1, Err));
        i++;
    }
    return (Ok);
}

int handle_64(t_obj *obj)
{
    struct mach_header_64 *header;
    obj->dss = 1;
    obj->tss = 1;
    obj->bss = 1;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header_64)))
        return (errors_fd(MALFORMED, ERR_MH64 , 1, Err));
    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header_64))))
        return (errors_fd(MALFORMED, ERR_LC, 1, Err));
    header = (struct mach_header_64 *)obj->data;
    if (!obj->swap)
        swap_mach_header_64(header);
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    obj->filetype = header->filetype;
    return (parse_loads_commands_64(obj));
}

static int parse_each_arch_64(t_obj *obj, struct fat_arch_64 *arch)
{
    t_obj tmp;

    if (!(tmp.data = check_sizeoff_move(obj, obj->data, arch->offset)))
        return (errors_fd(MALFORMED, ERR_FH64, 1, Err));
    tmp.size_data = arch->size;
    tmp.path = obj->path;
    if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)) || nm(&tmp))
        return (Err);
    return 0;
}

static int for_each_arch_64(t_obj *obj, struct fat_arch_64 *arch, struct fat_header *fat_header)
{
    uint32_t index;

    index = 0;
    while (++index < fat_header->nfat_arch)
    {
        if (parse_each_arch_64(obj, arch))
            return (Err);
        if (!(arch = check_sizeoff_move(obj, arch, sizeof(struct fat_arch_64))))
            return (errors_fd(MALFORMED, ERR_FH64, 1, Err));
    }
    return 0;
}

int parse_fat_arch_64(t_obj *obj, struct fat_header *ft)
{
    struct fat_arch_64 *arch;

    if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_arch_64))))
        return (errors_fd(MALFORMED, ERR_FH64, 1, Err));
    if (!obj->swap)
        swap_fat_arch_64(arch);
    return (for_each_arch_64(obj, arch, ft));
}