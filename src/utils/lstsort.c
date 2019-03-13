/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:45:12 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 13:12:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

static t_bool cmp_num(t_obj *obj, t_list *lst_a, t_list *lst_b)
{
	t_seg_list *a;
	t_seg_list *b;
	int ret;

	a = (t_seg_list *)(lst_a->content);
	b = (t_seg_list *)(lst_b->content);
	// if (ft_strcmp(a->name, b->name) == 0)
	// return True;
	ret = a->n_value < b->n_value;
	if (!ret)
	{
		if (checkoff_endofstring(obj, a->name) && checkoff_endofstring(obj, b->name))
		{
			return (False);
		}
		if (!(a->name) || !(b->name))
			return (False);
		if (ft_strcmp(a->name, b->name) < 0)
			ret = True;
		else
			ret = False;
	}
	return ((t_bool)ret);
}

static t_bool cmp_ascii(t_obj *obj, t_list *lst_a, t_list *lst_b)
{
	t_seg_list *a;
	t_seg_list *b;
	int ret;

	a = (t_seg_list *)(lst_a->content);
	b = (t_seg_list *)(lst_b->content);
	if (checkoff_endofstring(obj, a->name) && checkoff_endofstring(obj, b->name))
	{
		if (a->n_value == b->n_value)
			return True;
		return (a->n_value > b->n_value);
	}
	if (!(a->name) || !(b->name))
		return (a->n_value < b->n_value);
	if (ft_strcmp(a->name, b->name) < 0)
		ret = True;
	else if (ft_strcmp(a->name, b->name) == 0)
		ret = a->n_value > b->n_value;
	else
		ret = False;
	return ((t_bool)ret);
}

void sort_ascii(t_obj *obj, t_list **lst)
{
	t_list *new_lst;
	t_list *smaller;
	t_list *index;

	new_lst = NULL;
	if (!lst || !*lst)
		return;
	while (*lst)
	{
		index = *lst;
		smaller = *lst;
		while (index)
		{
			if (cmp_ascii(obj, smaller, index))
				smaller = index;
			index = index->next;
		}
		ft_lstremove(lst, smaller);
		ft_lstadd(&new_lst, smaller);
	}
	*lst = new_lst;
}

void sort_num(t_obj *obj, t_list **lst)
{
	t_list *new_lst;
	t_list *smaller;
	t_list *index;

	new_lst = NULL;
	if (!lst || !*lst)
		return;
	while (*lst)
	{
		index = *lst;
		smaller = *lst;
		while (index)
		{
			if (!cmp_num(obj, smaller, index))
				smaller = index;
			index = index->next;
		}
		ft_lstremove(lst, smaller);
		ft_lstadd(&new_lst, smaller);
	}
	*lst = new_lst;
}
