/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/14 09:12:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "ft_utils.h"

#define NM "ft_nm"

typedef struct                          s_obj
{
    const char      *path;
    const void      *data;
    size_t          size_data;
    uint32_t        magic;
    cpu_type_t      cputype;         /* cpu specifier */
    cpu_subtype_t   cpusubtype;      /* machine specifier */
    uint32_t        filetype;        /* type of file */
    uint32_t        ncmds;           /* number of load commands */
    uint32_t        sizeofcmds;      /* the size of all the load commands */
    struct          load_command *lc;
}                                       t_obj;



void nm(t_obj *obj);

/*
** handle
*/

void handle_64(void *ptr);

void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr);

#endif