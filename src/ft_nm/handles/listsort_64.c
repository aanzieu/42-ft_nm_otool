/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsort_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:19:08 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/27 15:02:57 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

struct s_index
{
	uint32_t first;
	uint32_t last;
};

// void		swap_list(struct nlist_64  **list, uint32_t i, uint32_t j)
// {
// 	struct nlist_64  swap;

// 	swap = *list[i];
// 	list[i] = list[j];
// 	*list[j] = swap;
// }

// uint32_t	split_64(struct nlist_64  **list, struct s_index index, char *stringtable,
// 		uint32_t piv)
// {
// 	struct nlist_64 swap;
// 	uint32_t	i;
// 	uint32_t	j;
// 	(void)stringtable;
// 	// char *s1;
// 	// char *s2;
// 	i = index.first;
// 	j = index.first;
// 	swap = list[piv];
// 	list[piv] = list[index.last -1];
// 	*list[index.last -1] = swap;
// 	while (i < index.last -1)
// 	{
// 			dprintf(1, "%s\n", stringtable + (*list)[i].n_un.n_strx);
// 		// s1 = stringtable + (*(list))[i].n_un.n_strx;
// 		// s2 = stringtable + (*(list))[index.last -1].n_un.n_strx;
// 		// if (ft_strcmp(s1, s2) < 0)
// 		// 	swap_list(list, i, j++);
// 		// else if (ft_strcmp(s1, s2) == 0 && (*(list))[i].n_value < (*(list))[index.last -1].n_value)
// 		// 	swap_list(list, i, j++);
// 		// i++;
// 	}
// 	swap = *list[index.last -1];
// 	list[index.last -1] = list[j];
// 	*list[j] = swap;
// 	return (j + 1);
// }

// void		quicksort_64(struct nlist_64 **list, uint32_t first, uint32_t last, char *stringtable)
// {
// 	uint32_t piv;
// 	struct s_index index;
// 	// (void)
// 	// (void)
//     // char c;

// 	if (first < last)
// 	{
// 		index.first = first;
// 		index.last = last;
// 		piv = split_64(list, index, stringtable, first - 1);
// 		quicksort_64(list, first, piv - 1, stringtable);
// 		quicksort_64(list, piv + 1, last, stringtable);
// 	}
// }

// int is_sorted(t_obj *obj, struct nlist_64 *array,
// 			  struct symtab_command *s)
// {
// 	uint32_t i;
// 	char *stringtable;
// 	char *s1;
// 	char *s2;

// 	if (!(stringtable = check_sizeoff_move(obj, obj->data, s->stroff)))
// 	{
// 		puts("Stringable Err");
// 		return 1;
// 	}
// 	i = 0;
// 	while (i + 1 < s->nsyms)
// 	{
// 		s1 = stringtable + array[i].n_un.n_strx;
// 		s2 = stringtable + array[i + 1].n_un.n_strx;
// 		if (ft_strcmp(s1, s2) > 0)
// 			return (0);
// 		else if (ft_strcmp(s1, s2) == 0)
// 			if (array[i].n_value > array[i + 1].n_value)
// 				return (0);
// 		i++;
// 	}
// 	return (1);
// }

void swap_arr(struct nlist_64 a, struct nlist_64 b)
{
	struct nlist_64 swap;

	// if ((a->n_type & N_STAB) || b->n_type & N_STAB) {
	// 	return;
	// }
	swap = a;
	a = b;
	b = swap;
}
#include <string.h>

void 		sort_ascii_64(t_obj *obj,
					struct nlist_64 *array, struct symtab_command *s)
{
	struct nlist_64 swap;

	// if ((a->n_type & N_STAB) || b->n_type & N_STAB) {
	// 	return;
	// }
	
	uint32_t i;
	char *s1;
	char *s2;
	// char *s3;
	char *stringtable;
	int truef = 1;
	uint32_t end = s->nsyms;
	i = 0;
	if (!(stringtable = check_sizeoff_move(obj, obj->data, s->stroff)))
	{
		puts("Stringable Err");
		return;
	}
	while (truef)
	{
		truef = 0;
		while (i + 1 < end)
		{
			s1 = stringtable + array[i].n_un.n_strx;
			s2 = stringtable + array[i + 1].n_un.n_strx;
			// if (array[i].n_value < array[i + 1].n_value)
			// {
			// 	swap_arr(array[i], array[i + 1]);
			// 	s3 = stringtable + array[i].n_un.n_strx;
			// 	truef = 1;
			// }
			// else if (array[i].n_value == array[i + 1].n_value)
			// {
			// 	if (ft_strcmp(s1, s2) > 0)
			// 	{
			// 		swap_arr(array[i], array[i + 1]);
			// 		truef = 1;
			// 	}
			// }
			if (ft_strcmp(s1, s2) > 0)
			{
				swap = array[i + 1];
				dprintf(1, "%s\n", stringtable + swap.n_un.n_strx);
				// array[i+ 1] = array[i];
				array[i].n_un.n_strx = swap.n_un.n_strx;
				array[i].n_sect = swap.n_sect;
				array[i].n_type = swap.n_type;
				array[i].n_desc = swap.n_desc;
				// swap_arr(&(array[i + 1]), (array[i]));
				truef = 1;
			}
			else if (ft_strcmp(s1, s2) == 0)
			{
				if (array[i].n_value > array[i + 1].n_value){
					swap = array[i];
					// array[i] = array[i+1];
					// array[i + 1] = swap;
				}
					// swap_arr((array[i]), (array[i + 1]));
				// swap_arr(array, i, i + 1);
				truef = 1;
			}
			i++;
		}
		// end--;
	}
	// return (array);
}

// void ascii_sort_64(t_obj *obj,
// 							   struct nlist_64 *array, struct symtab_command *s)
// {
// 	// while (1)
// 	// {
// 	// if (!(array =
// 	// return(sort_ascii_64(obj, array, s));
// 		// return (NULL);
// 	// if (is_sorted(obj, array, s))
// 	// break ;
// 	// }
// 	// return (array);
// }

struct nlist_64 *sort_64(t_obj *obj, struct symtab_command *sym, char *stringtable)
{
	// struct nlist_64 *array;
	if (!(obj->list64 = check_sizeoff(obj, obj->data, sym->symoff)))
		return (NULL);
	(void)stringtable;
	// if (strchr(obj->opt, 'p'))
	// return (array);
	// if (strchr(obj->opt, 'r'))
	// {
	// if (strchr(obj->opt, 'n'))
	// return (array = reverse_digit_sort_64(ptr, array, s));
	// else
	sort_ascii_64(obj, obj->list64, sym);
	// return (ascii_sort_64(obj, array, sym));
	return (obj->list64);
	// }
	// if (strchr(obj->opt, 'n'))
	// return (array = digit_sort_64(ptr, array, s));
	// else
	// return (array = ascii_sort_64(ptr, array, s));
}