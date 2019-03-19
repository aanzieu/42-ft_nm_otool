/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/19 08:38:00 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "ft_utils.h"

# define PROGRAM "ft_otool"

/*
** Function  only for otool
*/

int			help_otool(void);
int			otool(t_obj *obj);
int			handle_static_lyb(t_obj *obj);
int			print_hex_32(t_obj *obj, void *start, struct section section);
int			print_hex_64(t_obj *obj, void *start, struct section_64 section);
void		print_cpu_type(t_obj *obj);
int			handle_32(t_obj *obj);
int			handle_64(t_obj *obj);
int			handle_fat_64(t_obj *obj);
int			handle_fat_32(t_obj *obj);
int			parse_fat_arch_32(t_obj *obj, struct fat_header *ft);

#endif
