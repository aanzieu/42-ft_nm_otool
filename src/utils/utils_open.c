/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 09:36:50 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/26 08:09:56 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

int map_file_memory(int const fd, size_t const size, void **ptr)
{
    if ((*ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror("mmap failed");
        return (Err);
    }
    return (Ok);
}

int get_file_statut(int const fd, struct stat *buf)
{
    if (fstat(fd, buf) < 0)
    {
        perror("fstat");
        return (Err);
    }
    if (S_ISDIR(buf->st_mode))
    {
        perror("fstat error DIRECTORI");
        return (Err);
    }
    return (Ok);
}

int open_file(char const *arg)
{
    int fd;

    if ((fd = open(arg, O_RDONLY)) < 0)
    {
        perror("open failed");
        return (-1);
    }
    return fd;
}