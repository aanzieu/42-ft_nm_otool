/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:14:42 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/09 17:04:19 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

static void print_ext(t_seg_list seg)
{

    if (seg.n_type & N_EXT)
    {
        if (seg.n_desc == REFERENCED_DYNAMICALLY)
            ft_putstr_fd("[referenced dynamically] ", 1);
        ft_putstr_fd("external ", 1);
    }
    else if (seg.n_type & N_PEXT)
        ft_putstr("non-external (was a private external) ");
    else
        ft_putstr("non-external ");
}

void print_option_m(t_seg_list seg, t_obj *obj)
{
    char c;

    c = ft_toupper(get_char_type_64(seg, obj));
    if ((seg.n_type & N_TYPE) == N_UNDF && seg.n_value)
        ft_putstr("(common) ");
    else if (c == 'U')
        ft_putstr("(undefined) ");
    else if (c == 'C')
        ft_putstr("(common) ");
    else if (c == 'A')
        ft_putstr("(absolute) ");
    else if (c == 'I')
        ft_putstr("(indirect) ");
    else if ((seg.n_type & N_TYPE) == N_SECT)
    {
        if (seg.sectname[0] && seg.segname[0]) {
            ft_putstr_fd("(", 1);
            ft_putstr_fd(seg.segname, 1);
            ft_putchar_fd(',', 1);
            ft_putstr_fd(seg.sectname, 1);
            ft_putstr_fd(") ", 1);
        }
        else
            ft_putstr("(?,?) ");
    }
    else
        ft_putstr("(?) ");
    print_ext(seg);
}

t_bool print_cpu_type(t_obj *obj)
{
    const char *name;

    name = get_arch_type(obj->cputype, obj->cpusubtype).name;
    if (name && !ft_strcmp(name, ARCH_TYPE))
        return (False);
    if (!name)
    {
        printf("\n%s (for architecture ):\n", obj->path);
        return (False);
    }
    printf("\n%s (for architecture %s):\n", obj->path, name);
    return (False);
}