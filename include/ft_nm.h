/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 10:05:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "ft_utils.h"

#define NM "ft_nm"



void nm(t_obj *obj);
void swap_magic(void);

/*
** handle
*/

void handle_64(t_obj *obj);
void handle_32(void *ptr);

/*
**
*/
void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr);


int check_sizeoff(t_obj *obj, const void *start, size_t size);
void    *check_sizeoff_move(t_obj *obj, const void *start, size_t size);

#endif