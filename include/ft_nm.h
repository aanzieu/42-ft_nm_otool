/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/09 10:25:51 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include "ft_utils.h"
# define NM "ft_nm"

void nm(void *ptr);

/*
** handle
*/

void handle_64(void *ptr);




void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr);

#endif