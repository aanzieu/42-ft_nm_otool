/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:53:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/06 15:32:03 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int parse_loads_commands_32(t_obj *obj)
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
        if (parse_load_command_32(obj, lc))
            return Err;
        if (!(lc = check_sizeoff_move(obj, lc, lc->cmdsize)))
            return (errors_fd(MALFORMED, ERR_LC, 1, Err));
        i++;
    }
    return (Ok);
}

int handle_32(t_obj *obj)
{
    struct mach_header *header;
    obj->dss = 1;
    obj->tss = 1;
    obj->bss = 1;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header)))
        return (errors_fd(MALFORMED, ERR_MH, 1, Err));
    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header))))
        return (errors_fd(MALFORMED, ERR_LC, 1, Err));
    header = (struct mach_header *)obj->data;
    if (!obj->swap)
        swap_mach_header(header);
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    obj->filetype = header->filetype;
    return (parse_loads_commands_32(obj));
}

static int parse_each_arch_32(t_obj *obj, struct fat_arch *arch)
{
    t_obj tmp;

    if (!(tmp.data = check_sizeoff_move(obj, obj->data, arch->offset)))
        return (errors_fd(MALFORMED, ERR_FH, 1, Err));
    tmp.size_data = arch->size;
    tmp.path = obj->path;
    if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)) || nm(&tmp))
        return (Err);
    return 0;
}

static int for_each_arch_32(t_obj *obj, struct fat_arch *arch, struct fat_header *fat_header)
{
    uint32_t index;

    index = 0;
    while (++index < fat_header->nfat_arch)
    {
        if (parse_each_arch_32(obj, arch))
            return (Err);
        if (!(arch = check_sizeoff_move(obj, arch, sizeof(struct fat_arch))))
            return (errors_fd(MALFORMED, ERR_FH, 1, Err));
    }
    return 0;
}

int parse_fat_arch_32(t_obj *obj, struct fat_header *ft)
{
    struct fat_arch *arch;

    if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_header))))
        return (errors_fd(MALFORMED, ERR_FH, 1, Err));
    if (!obj->swap && arch != NULL)
        swap_fat_arch(arch);
    return (for_each_arch_32(obj, arch, ft));
}