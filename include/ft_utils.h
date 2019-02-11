/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 08:58:27 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/11 11:41:47 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
#define FT_UTILS_H
//  open, openat -- open or create a file for reading or writing - open(2)
#include <fcntl.h>
// close -- delete a descriptor - close(2)
// pwrite, write, writev -- write output - write(2)
#include <unistd.h>
// Fat
#include <mach-o/fat.h>
// Generic
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
// printf -- formatted output
#include <stdio.h>
// calloc, free, malloc, realloc, reallocf, valloc -- memory allocation -- malloc(3) & free(3)
#include <stdlib.h>
// mmap -- allocate memory, or map files or devices into memory - mmap(2)
// munmap -- remove a mapping - mummap(2)
#include <sys/mman.h>
//  fstat, fstat64, lstat, lstat64, stat, stat64, fstatat -- get file status - fstat(2)
#include <sys/stat.h>

#include "../libft/libft.h"
typedef enum s_bool
{
    True,
    False,
} t_bool;

typedef struct s_obj
{
    const char *path;
    const void *data;
    size_t size_data;
    uint32_t magic;
    cpu_type_t cputype;       /* cpu specifier */
    cpu_subtype_t cpusubtype; /* machine specifier */
    uint32_t filetype;        /* type of file */
    uint32_t ncmds;           /* number of load commands */
    uint32_t sizeofcmds;      /* the size of all the load commands */
    struct load_command *lc;
    t_bool swap; /* Define if mg need swap */

    int tss; /*text section syumbol */
    int bss; /*text section data*/
    int dss; /*text section data*/
    // t_list          *list;
} t_obj;

uint32_t ft_swap_uint32(uint32_t val);
int32_t ft_swap_int32(int32_t val);

#endif