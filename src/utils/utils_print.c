/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:54:05 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 18:13:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

char	ntype_if_upper(char c, uint8_t ntype)
{
	if (ntype & N_EXT)
		return (ft_toupper(c));
	if (c == 'c' || c == 'u')
		return ('?');
	return (c);
}

void	print_stat_lyb(t_obj *obj, void *offset)
{
	// ft_putchar_fd('\n', 1);
	ft_putstr_fd(obj->path, 1);
	ft_putchar_fd('(', 1);
	ft_putstr_fd(offset + sizeof(struct ar_hdr), 1);
	ft_putstr_fd("):", 1);
	ft_putchar_fd('\n', 1);
}
