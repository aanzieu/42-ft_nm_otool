/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:07:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 18:55:16 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"
#include <limits.h>

static void				*get_loadcommand64(t_obj *obj)
{
	uint32_t				index;
	struct load_command		*lc;
	char					cmp[16];

	lc = obj->lc;
	ft_memset(cmp, 0, 16);
	index = -1;
	while (++index < obj->ncmds)
	{
		if (ifswap32(obj, lc->cmd) == LC_SEGMENT_64)
		{
			if (!check_sizeoff(obj, lc, sizeof(struct segment_command_64)))
				return (errors_fd_null(MALFORMED, ERR_LC, 1));
			if (!ft_strncmp(((struct segment_command_64 *)lc)->segname,
						SEG_TEXT, 16) ||
				!ft_memcmp(((struct segment_command_64 *)lc)->segname, cmp, 16))
				return (lc);
		}
		if (!(lc = check_sizeoff_move(obj, lc, ifswap32(obj, lc->cmdsize))))
			break ;
	}
	return (errors_fd_null(MALFORMED, ERR_LC, 1));
}

static void				*get_section64(t_obj *obj, void *offset, uint32_t nb)
{
	uint32_t index;

	if (!check_sizeoff(obj, offset, sizeof(struct section_64)))
		return (errors_fd_null(MALFORMED, ERR_SECT64, 1));
	index = -1;
	while (++index < nb)
	{
		if (!check_sizeoff(obj, offset, sizeof(struct section_64)))
			return (errors_fd_null(MALFORMED, ERR_SECT64, 1));
		if (!ft_strncmp(((struct section_64 *)offset)->sectname, SECT_TEXT, 16))
			return (offset);
		if (!(offset = check_sizeoff_move(obj, offset,
						sizeof(struct section_64))))
			break ;
	}
	return (errors_fd_null(MALFORMED, ERR_SECT64, 1));
}

void					*get_text64(t_obj *obj, struct section_64 *sect)
{
	void *offset;

	if (!(offset = get_loadcommand64(obj)))
		return (NULL);
	if (!(check_sizeoff_move(obj, offset, sizeof(struct segment_command_64))))
		return (errors_fd_null(MALFORMED, ERR_SEG64, 1));
	offset = get_section64(obj, offset + sizeof(struct segment_command_64),
			((struct segment_command_64 *)offset)->nsects);
	if (!offset)
		return (errors_fd_null(MALFORMED, ERR_SEG64, 1));
	*sect = *((struct section_64 *)offset);
	if (!obj->swap)
		swap_section_64(sect, 1);
	if (!(offset = check_sizeoff_move(obj, obj->data, sect->offset)))
		return (errors_fd_null(MALFORMED, ERR_SECT64, 1));
	return (offset);
}

static int				checksection_64(t_obj *obj)
{
	struct section_64		sect;
	void					*start;

	if (!(start = get_text64(obj, &sect)))
		return (Err);
	if (!(check_sizeoff(obj, start, sect.size)))
		return (errors_fd(MALFORMED, ERR_SECT, 1, Err));
	if (!obj->flags->print_arch)
		print_cpu_type(obj);
	else if (!obj->flags->print_lib)
		;
	else
	{
		ft_putstr_fd(obj->path, 1);
		ft_putstr_fd(":\n", 1);
	}
	return (print_hex_64(obj, start, sect));
}

int						handle_64(t_obj *obj)
{
	struct mach_header_64 *header;

	if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header_64)))
		return (errors_fd(MALFORMED, ERR_MH, 1, Err));
	if (!(obj->lc = check_sizeoff_move(obj, obj->data,
					sizeof(struct mach_header_64))))
		return (errors_fd(MALFORMED, ERR_LC, 1, Err));
	header = (struct mach_header_64 *)obj->data;
	if (!obj->swap)
		swap_mach_header_64(header);
	obj->cpusubtype = header->cpusubtype;
	obj->cputype = header->cputype;
	obj->ncmds = header->ncmds;
	obj->filetype = header->filetype;
	return (checksection_64(obj));
}
