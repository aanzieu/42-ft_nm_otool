/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:35:19 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:11:58 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

int		errors_fd(const char *str, const char *line, int fd, t_return err)
{
	ft_putstr_fd(str, fd);
	ft_putchar(' ');
	ft_putstr_fd(C_RED, fd);
	ft_putstr_fd(line, fd);
	ft_putstr_fd(C_NONE, fd);
	ft_putchar('\n');
	return (err);
}

void	*errors_fd_null(const char *str, const char *line, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar(' ');
	ft_putstr_fd(line, fd);
	ft_putchar('\n');
	return (NULL);
}
