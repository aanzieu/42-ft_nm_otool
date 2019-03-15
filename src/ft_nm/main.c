/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:16:11 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 16:05:45 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

static int			help_nm(void)
{
	ft_putstr_fd("\nUSAGE: /bin/ft_nm -[jUurpA] <input files>\n", 1);
	return (1);
}

static int			parse_data_nm(t_obj *obj, int print)
{
	if (print)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(obj->path, 1);
		ft_putstr_fd("\n", 1);
	}
	if (nm(obj))
		return (Err);
	if (munmap((void *)obj->data, obj->size_data) < 0)
		return (errors_fd(ERR_MUNMAP, "", 1, Err));
	return (Ok);
}

static int			open_and_map(const char *arg, t_obj *obj, int print)
{
	int				fd;
	void			*data;
	struct stat		buf;

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
	return (parse_data_nm(obj, print));
}

static int			open_arg(const char *arg, int print, t_obj *obj)
{
	obj->is_fat = False;
	if ((open_and_map(arg, obj, print)) != 0)
		return (Err);
	return (0);
}

int					loop_open_args(const char *paths[], t_obj *obj)
{
	int index;
	int ret;

	index = -1;
	ret = 0;
	while (paths[++index])
	{
		if (open_arg(paths[index], 1, obj) != 0)
			ret = 1;
	}
	return (ret);
}

int					main(int ac, const char **av)
{
	t_obj		obj;
	t_option	opt;

	if (parse_options_flags(ac, av, &opt, "agAnpruUmj"))
		return (help_nm());
	obj.flags = &opt;
	if (ac > obj.flags->opt_ind + 1)
		return (loop_open_args(&av[obj.flags->opt_ind], &obj));
	else if (av[obj.flags->opt_ind])
		return (open_arg(av[obj.flags->opt_ind], 0, &obj));
	return (open_arg("./a.out", 0, &obj));
}
