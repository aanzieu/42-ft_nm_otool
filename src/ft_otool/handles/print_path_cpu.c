/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path_cpu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:47:42 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 17:36:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_otool.h"

void print_cpu_type(t_obj *obj)
{
	const char *name;

	name = get_arch_type(obj->cputype, obj->cpusubtype).name;
	if (!name)
	{
		ft_putstr_fd(obj->path, 1);
		ft_putstr_fd(" (architecture ):", 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putstr_fd(obj->path, 1);
		ft_putstr_fd(" (architecture ", 1);
		ft_putstr_fd(name, 1);
		ft_putstr_fd("):", 1);
		ft_putchar_fd('\n', 1);
	}
}

int help_otool(void)
{
    ft_putstr_fd("\nUSAGE: /bin/ft_otool -[ht] <input files>\n", 1);
    return (1);
}

