/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getoptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:00:44 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:20:29 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

static int		options_init(int argc, char const *argv[], t_option *opt)
{
	if (argc > opt->opt_ind && ft_strequ(argv[opt->opt_ind], "--"))
	{
		opt->opt_ind++;
		return (-1);
	}
	if (argc <= opt->opt_ind || *argv[opt->opt_ind] != '-')
		return (-1);
	return (0);
}

static char		options_curr(char **next, const char **argv, t_option *opt)
{
	char ret;

	if (!*next || !**next)
		*next = (char *)argv[opt->opt_ind] + 1;
	ret = **next;
	if (ret)
		++*next;
	if (!**next)
		opt->opt_ind++;
	opt->opt_opt = ret;
	opt->opt_arg = NULL;
	return (ret);
}

static int		options_check(char search, const char *opstring)
{
	int index;

	index = -1;
	while (opstring && opstring[++index])
		if (opstring[index] == search)
			return (opstring[index + 1] == ':');
	return (-1);
}

static int		options_err(const char *prgm, char curr, int err)
{
	char current[2];

	current[0] = curr;
	current[1] = 0;
	ft_putstr_fd(prgm, 1);
	if (err == ERR_OPT_REQ)
	{
		ft_putstr_fd(ERR_ARG_REQ, 1);
		ft_putstr_fd(current, 1);
	}
	else if (err == ERR_OPT_ILL)
	{
		ft_putstr_fd(ERR_ARG_ILL, 1);
		ft_putstr_fd(current, 1);
	}
	return ((int)'?');
}

int				get_options(int argc, char const *argv[],
				const char *optstring, t_option *opt)
{
	static char *next = NULL;
	int			check;
	char		current;

	if (options_init(argc, argv, opt))
		return (-1);
	current = options_curr(&next, argv, opt);
	check = options_check(current, optstring);
	if (ft_isalnum(current) && check != -1)
	{
		if (check == 1)
		{
			if (*next)
				opt->opt_arg = next;
			else if (argv[opt->opt_ind])
				opt->opt_arg = (char *)argv[opt->opt_ind];
			else
				return (options_err(*argv, current, ERR_OPT_REQ));
			next = NULL;
			opt->opt_ind++;
		}
		return (opt->opt_opt);
	}
	return (options_err(*argv, current, ERR_OPT_ILL));
}
