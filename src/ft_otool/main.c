/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:46:25 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 17:46:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_otool.h"

static int parse_data_otool(t_obj *obj)
{
    if (otool(obj))
        return (Err);
    if (munmap((void *)obj->data, obj->size_data) < 0)
        return (errors_fd(ERR_MUNMAP, "", 1, Err));
    return (Ok);
}

static int open_and_map(const char *arg, t_obj *obj)
{
    int fd;
    void *data;
    struct stat buf;

    data = NULL;
    if ((fd = open_file(arg)) < 0)
        return (errors_fd(ERR_OPEN, arg, 1, Err));
    if (get_file_statut(fd, &buf))
        return (errors_fd(ERR_STAT, arg, 1, Err));
    if (map_file_memory(fd, buf.st_size, &data))
        return (errors_fd(ERR_MAP, arg, 1, Err));
    if (obj)
    {
        obj->path = ft_strdup(arg);
        obj->data = data;
        obj->size_data = buf.st_size;
    }
    close(fd);
    return (parse_data_otool(obj));
}

static int open_arg(const char *arg, t_obj *obj)
{
    obj->is_fat = False;
    obj->flags->print_arch =  False;
    if ((open_and_map(arg, obj)) != 0)
        return (Err);
    return (0);
}

int loop_open_args(const char *paths[], t_obj *obj)
{
    int index;
    int ret;

    index = -1;
    ret = 0;
    while (paths[++index])
        if (open_arg(paths[index], obj) != 0)
            ret = 1;
    return (ret);
}

int					main(int ac, const char **av)
{
	t_obj		obj;
	t_option	opt;

	if (parse_options_flags(ac, av, &opt, "ht") || av[1][0] != '-')
		return (help_otool());
	obj.flags = &opt;
	if (ac > obj.flags->opt_ind + 1)
		return (loop_open_args(&av[obj.flags->opt_ind], &obj));
	else if (av[obj.flags->opt_ind])
		return (open_arg(av[obj.flags->opt_ind], &obj));
    return (help_otool());
}
