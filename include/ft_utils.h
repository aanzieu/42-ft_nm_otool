/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 08:58:27 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/14 08:39:12 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H
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

typedef	enum		e_bool
{
	False = 1,
	True = 0,
}					t_bool;

#endif