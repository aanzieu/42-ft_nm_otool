/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsort_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:19:08 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/09 16:31:31 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int cpy_sect64(t_obj *obj, t_seg_list *elem_sym,
					  struct segment_command_64 *segment, size_t index)
{
	struct section_64 *sect;

	if (!(sect = check_sizeoff_move(obj, segment, sizeof(struct segment_command_64))))
		return (Err);
	if (!(sect = check_sizeoff_move(obj, sect, index * sizeof(struct section_64))))
		return (Err);
	if (check_sizeoff(obj, sect->segname, 16))
		ft_memcpy(elem_sym->segname, sect->segname, 16);
	if (check_sizeoff(obj, sect->sectname, 16))
		ft_memcpy(elem_sym->sectname, sect->sectname, 16);
	else
		ft_memcpy(elem_sym->sectname, "undefined\0", 10);
	return (0);
}

int find_segname_64(struct nlist_64 symbol, t_seg_list *elem_sym,
					t_obj *obj)
{

	struct load_command *lc = obj->lc;
	size_t i = 0;
	size_t tot = 0;
	int ret = 0;

	// init_find_seg_sect_name(obj, &i, &tot, &lc);
	while (lc && i++ < obj->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (tot + ((struct segment_command_64 *)lc)->nsects >= symbol.n_sect)
			{
				ret = cpy_sect64(obj, elem_sym,
								 ((struct segment_command_64 *)lc), symbol.n_sect - tot - 1);
				break;
			}

			tot += ((struct segment_command_64 *)lc)->nsects;
		}

		if (!(lc = check_sizeoff_move(obj, lc, lc->cmdsize)))
			return (Err);
	}
	return (ret);
}

t_list *parse_nlist_64(t_obj *obj, char *stringtable, struct nlist_64 array)
{
	t_seg_list *elem_sym;
	t_list *elem;

	if (!obj->swap)
		swap_nlist_64(&array);
	if (!(elem_sym = (t_seg_list *)ft_memalloc(sizeof(t_seg_list) + 1)))
		return (NULL);
	elem_sym->name = checkoff_string(obj, stringtable, array.n_un.n_strx);
	elem_sym->n_value = array.n_value;
	// elem_sym->arch = ARCH_32;
	elem_sym->n_type = array.n_type;
	elem_sym->n_sect = array.n_sect;
	elem_sym->n_desc = array.n_desc;
	if (find_segname_64(array, elem_sym, obj))
	{
		free(elem_sym);
		return (NULL);
	}
	elem = ft_lstnew(elem_sym, (sizeof(t_seg_list) + 1));
	free(elem_sym);
	return (elem);
}

t_list *sort_64(t_obj *obj, struct symtab_command *sym, char *stringtable)
{
	struct nlist_64 *array;
	t_list *lst;
	int64_t index;

	index = -1;
	lst = NULL;
	if (!(array = check_sizeoff_move(obj, obj->data, sym->symoff)))
		return (NULL);
	while (++index < sym->nsyms)
	{
		ft_lstadd(&lst, parse_nlist_64(obj, stringtable, array[index]));
	}
	// if (strchr(obj->opt, 'p'))
	// return (array);
	// if (strchr(obj->opt, 'r'))
	// {
	// if (strchr(obj->opt, 'n'))
	// return (array = reverse_digit_sort_64(ptr, array, s));
	// else
	sort_ascii(obj, &lst);
	return (lst);
}