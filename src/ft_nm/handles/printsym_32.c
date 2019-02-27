/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printsym_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:51:59 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/26 15:37:15 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static void print_value_32(struct nlist array, char c, t_obj *obj)
{
    (void)c;
    if ((obj->filetype == MH_OBJECT && (array.n_type & N_TYPE) == N_UNDF && array.n_type & N_EXT && array.n_value > 0) || (array.n_type & N_SECT && array.n_value != 0))
    {
        ft_putnbr_ll_base(array.n_value, "0123456789abcdef");
    }
    else if ((array.n_type & N_SECT && array.n_value == 0))
    {
        ft_putstr("00000000");
    }
    else
        ft_putstr("        ");
    ft_putchar(' ');
}

static int print_nm_32(t_obj *obj, struct nlist array, char *stringtable, char c)
{
    char *check;
    int i;
    // if (get_nm_flags()->a_up)
    // print_path(input);
    // if (!get_nm_flags()->j && !get_nm_flags()->u)
    // {
    // if (!get_nm_flags()->m)
    ft_putchar(c);
    ft_putchar(' ');
    if (array.n_type & N_STAB)
        ft_putstr(" DEBUG SYMBOL ");
    // else if (get_nm_flags()->m)
    // print_m(sym);
    // }
    i = 0;
    check = checkoff_string(obj, stringtable, array.n_un.n_strx);
    if (check)
    {
        while (check_sizeoff(obj, (void *)check, i + 1))
        {
            ft_putchar(check[i]);
            if (check[i] == '\0')
                break;
            i++;
        }
    }
    else
    {
        ft_putstr("bad string index\n");
        return Err;
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

int for_each_symtab_32(t_obj *obj, struct symtab_command *sym, struct nlist *array, char *stringtable)
{
    uint32_t index;
    char c;
    index = 0;

    while (index < sym->nsyms) //
    {
        if (!obj->swap)
        {
            swap_nlist(array[index]);
        }
        c = get_char_type_32(array[index], obj);
        if (array[index].n_type & N_STAB)
            ;
        else
        {
            print_value_32(array[index], c, obj);
            if (print_nm_32(obj, array[index], stringtable, c))
            {
                ft_putstr("erreur nm print function printsym_32\n");
                return Err;
            }
        }

        index++;
    }
    return Ok;
}