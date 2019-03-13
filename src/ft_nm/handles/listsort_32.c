/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsort_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:51:13 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/12 16:20:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int			cpy_sect32(t_obj *obj, t_seg_list *elem_sym,
					struct segment_command *seg, size_t index)
{
	struct section *sect;

	if (!(sect = check_sizeoff_move(obj, seg, sizeof(struct segment_command))))
		return (Err);
	if (!(sect = check_sizeoff_move(obj, sect, index * sizeof(struct section))))
		return (Err);
	if (check_sizeoff(obj, sect->segname, 16))
		ft_memcpy(elem_sym->segname, sect->segname, 16);
	if (seg->nsects > 0 && check_sizeoff(obj, sect->sectname, 16))
		ft_memcpy(elem_sym->sectname, sect->sectname, 16);
	else
		ft_memcpy(elem_sym->sectname, "undefined\0", 10);
	return (0);
}

int					find_segname_32(struct nlist symbol, t_seg_list *elem_sym,
					t_obj *obj)
{
	struct load_command		*lc;
	size_t					i;
	size_t					tot;
	int						ret;

	lc = obj->lc;
	i = 0;
	tot = 0;
	ret = 0;
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

static t_list		*parse_nlist_32(t_obj *obj, char *stringtable,
					struct nlist array)
{
	t_seg_list	*elem_sym;
	t_list		*elem;

	if (!obj->swap)
		swap_nlist(&array);
	if (!(elem_sym = (t_seg_list *)ft_memalloc(sizeof(t_seg_list) + 1)))
		return (NULL);
	elem_sym->name = checkoff_string(obj, stringtable, array.n_un.n_strx);
	elem_sym->n_value = (uint64_t)array.n_value;
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

t_list				*sort_32(t_obj *obj,
					struct symtab_command *sym, char *stringtable)
{
	struct nlist	*array;
	t_list			*lst;
	t_list			*elem;
	int64_t			index;

	index = -1;
	lst = NULL;
	if (!(array = check_sizeoff_move(obj, obj->data, sym->symoff)))
		return (NULL);
	while (++index < sym->nsyms)
	{
		if (!(elem = parse_nlist_32(obj, stringtable, array[index])))
			return (NULL);
		ft_lstadd(&lst, elem);
	}
	sort_ascii(obj, &lst);
	return (lst);
}
