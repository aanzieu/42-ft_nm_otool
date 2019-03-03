/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:14:42 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/03 15:38:04 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

t_bool print_cpu_type(t_obj *input)
{
    const char *name;

    name = get_arch_type(input->cputype, input->cpusubtype).name;
    if (name && !ft_strcmp(name, GET_ARCH))
        return (False);
    if (!name)
    {
        printf("\n%s (for architecture ):\n", input->path);
        return (False);
    }
    printf("\n%s (for architecture %s):\n", input->path, name);
    return (True);
}