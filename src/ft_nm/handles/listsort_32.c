/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsort_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:51:13 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/09 16:11:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int		cpy_sect32(t_obj *obj, t_seg_list *elem_sym,
					struct segment_command *segment, size_t index)
{
	struct section_64			*sect;

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

int find_segname_32(struct nlist symbol, t_seg_list *elem_sym,
					t_obj *obj)
{

	struct load_command *lc = obj->lc;
	size_t i = 0;
	size_t tot = 0;
	int ret;

	// init_find_seg_sect_name(obj, &i, &tot, &lc);
	while (lc && i++ < obj->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			if (tot + ((struct segment_command *)lc)->nsects >= symbol.n_sect)
			{
				ret = cpy_sect32(obj, elem_sym,
											((struct segment_command *)lc), symbol.n_sect - tot - 1);
				return (ret);
			}
			tot += ((struct segment_command *)lc)->nsects;
		}
		
		if (!(lc = check_sizeoff_move(obj, lc, lc->cmdsize)))
			return (Err);
	}
	return (0);
}

static t_list *parse_nlist_32(t_obj *obj, char *stringtable, struct nlist array)
{
	t_seg_list *elem_sym;
	t_list *elem;

	if (!obj->swap)
		swap_nlist(&array);
	if (!(elem_sym = (t_seg_list *)ft_memalloc(sizeof(t_seg_list) + 1)))
		return (NULL);
	elem_sym->name = checkoff_string(obj, stringtable, array.n_un.n_strx);
	elem_sym->n_value = (uint64_t)array.n_value;
	// elem_sym->arch = ARCH_32;
	elem_sym->n_type = array.n_type;
	elem_sym->n_sect = array.n_sect;
	elem_sym->n_desc = array.n_desc;
	if (find_segname_32(array, elem_sym, obj))
	{
		free(elem_sym);
		return (NULL);
	}
	elem = ft_lstnew(elem_sym, (sizeof(t_seg_list) + 1));
    free(elem_sym);
	return (elem);
}

t_list *sort_32(t_obj *obj, struct symtab_command *sym, char *stringtable)
{
	struct nlist *array;
	t_list *lst;
	int64_t index;

	index = -1;
	lst = NULL;
	if (!(array = check_sizeoff_move(obj, obj->data, sym->symoff)))
		return (NULL);
	while (++index < sym->nsyms)
	{
		ft_lstadd(&lst, parse_nlist_32(obj, stringtable, array[index]));
	}
	// if (strchr(obj->opt, 'p'))
	// return (array);
	// if (strchr(obj->opt, 'r'))
	// {
	// if (strchr(obj->opt, 'n'))
	// return (array = reverse_digit_sort_32(ptr, array, s));
	// else
	sort_ascii(obj, &lst);
	
	return (lst);
}