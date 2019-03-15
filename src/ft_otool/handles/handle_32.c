/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:53:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/15 14:42:13 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"
#include <limits.h>

static void *get_loadcommand32(t_obj *obj)
{
    uint32_t index;
    struct load_command *lc;
    char cmp[16];

    lc = obj->lc;
    ft_memset(cmp, 0, 16);
    index = -1;
    while (++index < obj->ncmds)
    {
        if (ifswap32(obj, lc->cmd) == LC_SEGMENT)
        {
            if (!check_sizeoff(obj, lc, sizeof(struct segment_command)))
                return (errors_fd_null(MALFORMED, "offeset NUll", 1));
            if (!ft_strncmp(((struct segment_command *)lc)->segname, SEG_TEXT, 16) ||
                !ft_memcmp(((struct segment_command_64 *)lc)->segname, cmp, 16))
                return (lc);
        }
        if (!(lc = check_sizeoff_move(obj, lc, ifswap32(obj, lc->cmdsize))))
            break;
    }
    return (errors_fd_null(MALFORMED, "offeset NUll", 1));
}

static void *get_section32(t_obj *obj, void *offset, uint32_t nb)
{
    uint32_t index;

    if (!check_sizeoff(obj, offset, sizeof(struct section)))
        return (errors_fd_null(MALFORMED, "offeset NUll", 1));
    index = -1;
    while (++index < nb)
    {
        if (!check_sizeoff(obj, offset, sizeof(struct section)))
            return (errors_fd_null(MALFORMED, "offeset NUll", 1));
        if (!ft_strncmp(((struct section *)offset)->sectname, SECT_TEXT, 16))
            return (offset);
        if (!(offset = check_sizeoff_move(obj, offset, sizeof(struct section))))
            break;
    }
    return (errors_fd_null(MALFORMED, "offeset NUll", 1));
}

void *get_text32(t_obj *obj, struct section *sect)
{
    void *offset;

    if (!(offset = get_loadcommand32(obj)))
        return (NULL);
    if (!(check_sizeoff_move(obj, offset, sizeof(struct segment_command))))
        return (errors_fd_null(MALFORMED, "offeset NUll", 1));
    offset = get_section32(obj, offset + sizeof(struct segment_command),
                              ((struct segment_command *)offset)->nsects);
    if (!offset)
        return (errors_fd_null(MALFORMED, "offeset NUll", 1));
    *sect = *((struct section *)offset);
    if (!obj->swap)
        swap_section(sect, 1);
    if (!(offset = check_sizeoff_move(obj, obj->data, sect->offset)))
        return (errors_fd_null(MALFORMED, "offeset NUll", 1));
    return (offset);
}

static int print_hex_32(t_obj *obj, void *start, struct section section)
{
    uint32_t index;
    uint16_t nb_print;
    t_bool swap;
    t_bool space;

    index = 0;
    swap = !obj->swap;// && GET_ENDIAN == LITTLE;
    space = !(obj->cputype == CPU_TYPE_I386 || obj->cputype == CPU_TYPE_X86_64);
    ft_putstr_fd("Contents of (__TEXT,__text) section\n", 1);
    while (index < section.size)
    {
		ft_putnbr_ll_base(section.addr + index, "0123456789abcdef", 8);
        ft_putchar_fd('\t', 1);
        nb_print = (section.size - index) <= 16 ? (section.size - index) : 16;
        print_hexadump(start + index, nb_print, space, swap);
        ft_putchar('\n');
        index = index + 16;
    }
    return 0;
}

static int checksection_32(t_obj *obj)
{

    struct section sect;
    void *start;

    if (!(start = get_text32(obj, &sect)))
    {
        return (Err);
    }
    if (!(check_sizeoff(obj, start, sect.size)))
    {
        return (errors_fd(MALFORMED, "section", 1, Err));
    }
    ft_putstr_fd(obj->path, 1);
    ft_putstr_fd(":\n", 1);
    return print_hex_32(obj, start, sect);
}

int handle_32(t_obj *obj)
{
    struct mach_header *header;

    obj->dss = 1;
    obj->tss = 1;
    obj->bss = 1;
    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header)))
        return (errors_fd(MALFORMED, ERR_MH, 1, Err));
    if (!(obj->lc = check_sizeoff_move(obj, obj->data,
                                       sizeof(struct mach_header))))
        return (errors_fd(MALFORMED, ERR_LC, 1, Err));
    header = (struct mach_header *)obj->data;
    if (!obj->swap)
        swap_mach_header(header);
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    obj->filetype = header->filetype;
    return (checksection_32(obj));
}

static int parse_each_arch_32(t_obj *obj, struct fat_arch *arch)
{
    t_obj tmp;

    tmp.data = check_sizeoff_move(obj, obj->data, arch->offset);
    tmp.size_data = arch->size;
    tmp.path = obj->path;
    tmp.flags = obj->flags;
    tmp.is_fat = obj->is_fat;
    if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)))
        return (Err);
    return (otool(&tmp));
}

static int for_each_arch_32(t_obj *obj, struct fat_arch *arch,
                            struct fat_header *fat_header, uint32_t index)
{
    struct fat_arch *tmp;
    const char *name;

    tmp = arch;
    while (index--)
    {
        name = get_arch_type(arch->cputype, arch->cpusubtype).name;
        if (!ft_strcmp(name, ARCH_TYPE))
            return (parse_each_arch_32(obj, arch));
        if (!(arch = check_sizeoff_move(obj, arch, sizeof(struct fat_arch))))
            return (errors_fd(MALFORMED, ERR_FH, 1, Err));
        if (!obj->swap)
            swap_fat_arch(arch);
    }
    arch = tmp;
    index = fat_header->nfat_arch;
    obj->flags->print_arch = True;
    while (index--)
    {
        if (parse_each_arch_32(obj, arch))
            return (Err);
        if (!(arch = check_sizeoff_move(obj, arch, sizeof(struct fat_arch))))
            return (errors_fd(MALFORMED, ERR_FH, 1, Err));
    }
    return (0);
}

int parse_fat_arch_32(t_obj *obj, struct fat_header *ft)
{
    struct fat_arch *arch;
    uint32_t index;

    if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_header))))
        return (errors_fd(MALFORMED, ERR_FH, 1, Err));
    if (!obj->swap)
        swap_fat_arch(arch);
    index = ft->nfat_arch;
    return (for_each_arch_32(obj, arch, ft, index));
}
