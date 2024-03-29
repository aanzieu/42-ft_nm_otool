/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:24:56 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 18:43:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"

static uint32_t		get_magic_number(t_obj *obj)
{
	obj->magic = 42;
	if (check_sizeoff(obj, obj->data, sizeof(uint32_t)))
		obj->magic = (*(uint32_t *)obj->data);
	return (obj->magic);
}

static int			find_header_type(t_obj *obj)
{
	uint32_t mg;

	mg = get_magic_number(obj);
	if (obj->magic == MH_CIGAM || obj->magic == MH_CIGAM_64
			|| obj->magic == FAT_CIGAM)
		obj->swap = True;
	else
		obj->swap = False;
	return (mg);
}

static int			choose_handler(t_obj *obj, uint32_t mg)
{
	if (mg == MH_MAGIC_64 || mg == MH_CIGAM_64)
		return (handle_64(obj));
	else if (obj->magic == MH_MAGIC || obj->magic == MH_CIGAM)
		return (handle_32(obj));
	else if (obj->magic == FAT_MAGIC || obj->magic == FAT_CIGAM)
	{
		obj->is_fat = True;
		return (handle_fat_32(obj));
	}
	else if (obj->magic == FAT_CIGAM_64 || obj->magic == FAT_MAGIC_64)
	{
		obj->is_fat = True;
		return (handle_fat_64(obj));
	}
	else if (check_sizeoff(obj, obj->data, SARMAG) &&
			!ft_strncmp(ARMAG, (char *)obj->data, SARMAG))
	{
		obj->flags->print_lib = True;
		ft_putstr_fd("Archive : ", 1);
		ft_putstr_fd(obj->path, 1);
		ft_putchar_fd('\n', 1);
		return (handle_static_lyb(obj));
	}
	return (errors_fd(ERR_MAP, "<Malformed>", 1, Err));
}

int					otool(t_obj *obj)
{
	uint32_t head;

	head = find_header_type(obj);
	if (head == 42)
		return (errors_fd(ERR_MAP, "", 1, Err));
	return (choose_handler(obj, obj->magic));
}
