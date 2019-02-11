/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/11 10:01:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "ft_utils.h"

#define NM "ft_nm"

typedef struct s_seg_cmd
{                     /* for 64-bit architectures */
    uint32_t cmd;     /* LC_SEGMENT_64 */
    uint32_t cmdsize; /* includes sizeof section_64 structs */
    char *name;
    char segname[16];  /* segment name */
    uint64_t vmaddr;   /* memory address of this segment */
    uint64_t vmsize;   /* memory size of this segment */
    uint64_t fileoff;  /* file offset of this segment */
    uint64_t filesize; /* amount to map from the file */
    // vm_prot_t maxprot;  /* maximum VM protection */
    // vm_prot_t initprot; /* initial VM protection */
    uint32_t nsects; /* number of sections in segment */
    // uint32_t flags;     /* flags */
} t_seg_cmd;

/**
 * Utils Open function
 **/
int get_file_statut(int const fd, struct stat *buf);
int open_file(char const *arg);
int map_file_memory(int const fd, size_t const size, void **ptr);

/*
** NM function
*/
int nm(t_obj *obj);

/*
** swap Magic function
*/
void swap_magic(void);

/*
** handle
*/

int handle_64(t_obj *obj);
void handle_32(void *ptr);

/*
**
*/
void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr);

int check_sizeoff(t_obj *obj, const void *start, size_t size);
void *check_sizeoff_move(t_obj *obj, const void *start, size_t size);

#endif