/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/08 14:38:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  open, openat -- open or create a file for reading or writing - open(2)
#include <fcntl.h>

// close -- delete a descriptor - close(2)
// pwrite, write, writev -- write output - write(2)
#include <unistd.h>

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
