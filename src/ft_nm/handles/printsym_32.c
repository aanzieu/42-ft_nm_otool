/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printsym_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:51:59 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/09 15:16:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static void print_value_32(t_seg_list array, char c, t_obj *obj)
{
    (void)c;
    if (!obj->flags->a_upcase)
    {
        ft_putstr_fd(obj->path, 1);
        ft_putstr_fd(": ", 1);
    }
    if ((obj->filetype == MH_OBJECT && (array.n_type & N_TYPE) == N_UNDF && array.n_type & N_EXT && array.n_value > 0) || (array.n_type & N_SECT && array.n_value != 0))
    {
        ft_putnbr_ll_base(array.n_value, "0123456789abcdef", 8);
    }
    else if ((array.n_type & N_SECT && array.n_value == 0))
    {
        ft_putstr("00000000");
    }
    else
        ft_putstr("        ");
    ft_putchar(' ');
}

static int print_nm_32(t_obj *obj, t_seg_list array, char c)
{
    int i;

    if (obj->flags->m)
    {
        ft_putchar(c);
        ft_putchar(' ');
    }
    if (array.n_type & N_STAB)
        ft_putstr(" DEBUG SYMBOL ");
    else if (!obj->flags->m)
    {
        print_option_m(array, obj);
    }

    i = 0;
    if (array.name)
    {
        while (check_sizeoff(obj, (void *)array.name, i + 1))
        {
            if (array.name[i] == '\0')
                break;
            ft_putchar(array.name[i++]);
        }
    }
    else
        return (errors_fd(MALFORMED, ERR_STR, 1, Err));
    if ((array.n_sect & N_EXT) == N_UNDF && !obj->flags->m && c == 'U')
    {
        if ((array.n_desc & REFERENCE_TYPE) == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
        {
            ft_putstr(" (from lib)");
        }
    }

    ft_putchar('\n');
    return Ok;
}

// static void		print_name(t_obj *obj)
// {
// 	// if (obj->m_arg)
// 		// printf("\n%s:\n", obj->path);
// 	// else if (ft_strlen(obj->arch_name) > 0)
// 		// printf("\n%s %s:\n", obj->path, stat.arch_name);
// }

int for_each_symtab_32(t_obj *obj, t_list *array)
{
    uint32_t index;
    char c;
    t_seg_list seg;

    index = 0;
    // if (print_cpu_type(obj))
    //     return Err;
    while (array) //
    {
        seg = *(t_seg_list *)array->content;
        c = get_char_type_32(seg, obj);
        if (seg.n_type & N_STAB)
            ;
        else
        {
            if (obj->flags->j && obj->flags->u)
            {
                print_value_32(seg, c, obj);
                if (print_nm_32(obj, seg, c))
                    return Err;
            }
        }
        array = array->next;
    }
    return Ok;
}