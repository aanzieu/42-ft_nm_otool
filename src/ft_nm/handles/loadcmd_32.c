/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadcmd_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:49:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 13:55:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static void		get_index_segname_32(t_obj *obj,
				struct section *sect, uint32_t index)
{
	if (ft_strequ(sect->sectname, "__text"))
		obj->tss = index;
	else if (ft_strequ(sect->sectname, "__data"))
		obj->dss = index;
	else if (ft_strequ(sect->sectname, "__bss"))
		obj->bss = index;
}

static int		read_symbat_command_32(t_obj *obj, struct symtab_command *sym)
{
	char		*stringtable;
	t_list		*new;

	if (!obj->swap)
		swap_symtab_command(sym);
	if (!(stringtable = check_sizeoff_move(obj, obj->data, sym->stroff)))
		return (errors_fd(MALFORMED, ERR_SYMTAB, 1, Err));
	if (!(new = sort_32(obj, sym, stringtable)))
		return (errors_fd(MALFORMED, ERR_SYMTAB, 1, Err));
	if (!obj->flags->print_arch)
		print_cpu_type(obj);
	return (for_each_symtab_32(obj, new));
}

static int		read_section_32(t_obj *obj,
				struct segment_command *segment, size_t index)
{
	struct section	*sect;

	if (!(sect = check_sizeoff_move(obj, segment,
					sizeof(struct segment_command))))
		return (errors_fd(MALFORMED, ERR_SECT, 1, Err));
	if (!(sect = check_sizeoff_move(obj, sect,
					index * sizeof(struct section))))
		return (errors_fd(MALFORMED, ERR_SECT, 1, Err));
	get_index_segname_32(obj, sect, obj->index_sec);
	obj->index_sec++;
	return (Ok);
}

static int		read_segment_command_32(t_obj *obj, struct segment_command *seg)
{
	size_t i;

	if (!obj->swap)
		seg->nsects = ft_swap_uint32(seg->nsects);
	if (ft_strequ(seg->segname, "__TEXT") ||
			ft_strequ(seg->segname, "__DATA") || obj->filetype == MH_OBJECT)
	{
		i = -1;
		while (++i < seg->nsects)
			if (read_section_32(obj, seg, i))
				return (Err);
	}
	return (Ok);
}

int				parse_load_command_32(t_obj *obj, struct load_command *lc)
{
	struct segment_command *seg;

	if (lc->cmd == LC_SEGMENT)
	{
		if (!(seg = (struct segment_command *)lc))
			return (errors_fd(MALFORMED, ERR_SEG, 1, Err));
		return (read_segment_command_32(obj, seg));
	}
	if (lc->cmd == LC_SYMTAB)
	{
		if (!(obj->sym = (struct symtab_command *)lc))
			return (errors_fd(MALFORMED, ERR_SYMTAB, 1, Err));
		return (read_symbat_command_32(obj, obj->sym));
	}
	return (Ok);
}
