/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_static_lyb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:13:28 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 12:30:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"
#include <mach-o/ranlib.h>

#define AR_LONG_NAME sizeof(char[20])
#define SIZEOF_OBJ_H sizeof(struct ar_hdr) + AR_LONG_NAME
#define AR_LEN_BEFORE_SYMTAB SARMAG + SIZEOF_OBJ_H

static void *go_end_string_table(t_obj *obj, void *start)
{
	void *offset;

	offset = start;
	while ((offset = ft_memchr(offset, '#', obj->data + obj->size_data - offset)))
	{
		if (check_sizeoff(obj, offset, 3) && !ft_memcmp(offset, AR_EFMT1, 3))
			return (offset);
		if (!(offset = check_sizeoff_move(obj, offset, 1)))
			return (NULL);
	}
	return (NULL);
}

static t_obj *new_tmp(size_t length, void *offset, t_obj *obj)
{
	t_obj *tmp;

	tmp = NULL;
	if (!(tmp = (t_obj *)ft_memalloc(sizeof(t_obj) + 1)))
		return (NULL); //errors_fd(obj->path, PROGRAM, 1, Err));
	if (!check_sizeoff(obj, offset, 0))
		return (NULL); //errors_fd_null(obj->path, PROGRAM, ERR_MALFORMED));
	tmp->data = check_sizeoff_move(obj, offset, ft_next_align(ft_atoi(offset + 3) + sizeof(struct ar_hdr), 8));
	tmp->size_data = length;
	tmp->path = obj->path;
	tmp->flags = obj->flags;
	tmp->is_fat = obj->is_fat;
	tmp->swap = obj->swap;
	if (!tmp->data || !(check_sizeoff(obj, tmp->data, tmp->size_data - ft_atoi(offset + 3))) || !checkoff_string(obj, offset + sizeof(struct ar_hdr), 0))
		return (errors_fd_null(obj->path, PROGRAM, 1));
	dprintf(1, "\n%s(%s):\n", obj->path, offset + sizeof(struct ar_hdr));
	return (tmp);
}

static int handle_lib_objects(t_obj *obj, void *offset)
{
	t_obj *tmp;
	// t_handler_func *handler_funcs;

	// handler_funcs = get_nm_flags()->funcs;
	tmp = NULL;
	while (offset || !check_sizeoff(obj, offset, sizeof(struct ar_hdr)))
	{
		tmp = new_tmp(ft_atoi(((struct ar_hdr *)offset)->ar_size), offset, obj);
		if (!tmp)
			return (1);
		// if ((ret = exec_handler(handler_funcs, tmp)) == 2)
		// 	return (errors_fd(obj->path, PROGRAM, ERR_INVALID, 1));
		if (!tmp->data || nm(tmp))
			return (Err);
		if (offset + tmp->size_data + sizeof(struct ar_hdr) == (obj->data + obj->size_data))
			break;
		if (!(offset = check_sizeoff_move(obj, offset, tmp->size_data + sizeof(struct ar_hdr))))
			return (errors_fd(obj->path, PROGRAM, 1, Err));
	}
	return (0);
}

int parse_lib(t_obj *obj)
{
	void *offset;

	if (!(offset = check_sizeoff_move(obj, obj->data, AR_LEN_BEFORE_SYMTAB)))
		return (errors_fd(obj->path, PROGRAM, 1, Err));
	if (!check_sizeoff(obj, offset, sizeof(uint32_t) + 1))
		return (errors_fd(obj->path, PROGRAM, 1, Err));
	if (!(offset = check_sizeoff(obj, offset, *(uint32_t *)offset + sizeof(uint32_t))))
		return (errors_fd(obj->path, PROGRAM, 1, Err));
	if (!(offset = go_end_string_table(obj, offset)))
		return (errors_fd(obj->path, PROGRAM, 1, Err));
	return (handle_lib_objects(obj, offset));
}


int				handle_static_lyb(t_obj *obj)
{
	void			*copy_add;

	if (!(copy_add = check_sizeoff_move(obj, obj->data, SARMAG +
														sizeof(struct ar_hdr))))
		return(errors_fd(obj->path, PROGRAM, 1, Err));
	if (!check_sizeoff(obj, copy_add, AR_LONG_NAME))
		return(errors_fd(obj->path, PROGRAM, 1, Err));
	if (!ft_strncmp(SYMDEF, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_SORTED, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64_SORTED, copy_add, AR_LONG_NAME))
		return (parse_lib(obj));
	return (Err);
}