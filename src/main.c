/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:16:11 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/08 16:14:14 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"








int main(int ac, char **av)
{
    int         fd;
    char        *ptr;
    struct stat buf;

    // stat ftsize

	// off_t		st_size;	/* [XSI] file size, in bytes */
    // 
    if (ac != 2)
    {
        fprintf(stderr, "Plese give me arg");
        return (EXIT_FAILURE);
    }
    if ((fd = open(av[1], O_RDONLY)) < 0)
    {
        perror("open");
        return (EXIT_FAILURE);
    }
    if (fstat(fd, &buf) < 0)
    {
        perror("fstat");
        return (EXIT_FAILURE);
    }
    // PROT_WRITE
    if ((ptr = mmap(0, buf.st_size, PROT_READ , MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror("mmap");
        return (EXIT_FAILURE);
    }


    nm(ptr);
    if (munmap(ptr, buf.st_size) < 0)
    {
        perror("fstat");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}