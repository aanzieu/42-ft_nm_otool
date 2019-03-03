/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsort_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:51:13 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/03 15:03:06 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static t_list *parse_nlist_32(t_obj *obj, char *stringtable, struct nlist array)
{
	t_seg_list *elem_sym;
	t_list *elem;

	if (!obj->swap)
		swap_nlist(&array);
	if (!(elem_sym = (t_seg_list *)ft_memalloc(sizeof(t_seg_list) + 1)))
		return (NULL);
	elem_sym->name = checkoff_string(obj, stringtable, array.n_un.n_strx);
	elem_sym->n_value = array.n_value;
	// elem_sym->arch = ARCH_32;
	elem_sym->n_type = array.n_type;
	elem_sym->n_sect = array.n_sect;
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