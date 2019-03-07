/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:23:39 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/07 12:39:16 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static void get_flag_options(char flags, t_option *option)
{
    if (flags == 'g')
        option->g = True;
    else if (flags == 'A')
        option->a_upcase = True;
    else if (flags == 'n')
        option->n = True;
    else if (flags == 'r')
        option->r = True;
    else if (flags == 'm')
        option->m = True;
    else if (flags == 'j')
        option->j = True;
    else if (flags == 'U')
        option->u_upcase = True;
    else if (flags == 'p')
    {
        option->n = False;
        option->p = True;
    }
    else if (flags == 'u')
    {
        option->u = True;
        option->u_upcase = False;
        option->a = False;
    }
}

static void init_option(t_option *option)
{
    option->opt_ind = 1;
    option->opt_err = 1;
    option->opt_arg = NULL;
    option->a = False;
    option->g = False;
    option->a_upcase = False;
    option->n = False;
    option->p = False;
    option->r = False;
    option->u = False;
    option->u_upcase = False;
    option->m = False;
    option->j = False;
    option->print_arch = False;
}

int parse_options_flags(int ac, const char **av, t_option *option)
{
    int opt;

    init_option(option);

    // if (!(option = (t_option *)ft_memalloc(sizeof(t_option) + 1)))
    //     return errors_fd("Error Malloc", "", 1, Err);
    while ((opt = get_options(ac, av, "agAnpruUmj", option)) != -1)
    {
        get_flag_options(opt, option);
        if (opt == 'a')
        {
            option->a = True;
            option->u = False;
            option->u_upcase = False;
        }
        if (opt == 'h')
            return (1);
        if (opt == '?')
            return (1);
    }
    return (0);
}
