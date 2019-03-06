/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:14:42 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/06 14:04:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

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