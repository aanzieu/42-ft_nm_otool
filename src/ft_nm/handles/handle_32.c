/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:53:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/12 16:05:06 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"
#include <limits.h>

static int		parse_loads_commands_32(t_obj *obj)
{
	uint32_t			i;
	struct load_command	*lc;

	i = 0;
	obj->index_sec = 1;
	lc = obj->lc;
	while (lc && i++ < obj->ncmds)
	{
		if (!obj->swap)
			swap_load_commands(lc);
		if (parse_load_command_32(obj, lc))
			return (Err);
		if (!(lc = check_sizeoff_move(obj, lc, lc->cmdsize)))
			break ;
	}
	return (Ok);
}

int				handle_32(t_obj *obj)
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
	return (parse_loads_commands_32(obj));
}

static int		parse_each_arch_32(t_obj *obj, struct fat_arch *arch)
{
	t_obj tmp;

	tmp.data = check_sizeoff_move(obj, obj->data, arch->offset);
	tmp.size_data = arch->size;
	tmp.path = obj->path;
	tmp.flags = obj->flags;
	tmp.is_fat = obj->is_fat;
	if (!tmp.data || !(check_sizeoff(obj, tmp.data, tmp.size_data)))
		return (Ok);
	return (nm(&tmp));
}

static int		for_each_arch_32(t_obj *obj, struct fat_arch *arch,
				struct fat_header *fat_header, uint32_t index)
{
	struct fat_arch	*tmp;
	const char		*name;

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

int				parse_fat_arch_32(t_obj *obj, struct fat_header *ft)
{
	struct fat_arch	*arch;
	uint32_t		index;

	if (!(arch = check_sizeoff_move(obj, obj->data, sizeof(struct fat_header))))
		return (errors_fd(MALFORMED, ERR_FH, 1, Err));
	if (!obj->swap)
		swap_fat_arch(arch);
	index = ft->nfat_arch;
	return (for_each_arch_32(obj, arch, ft, index));
}
