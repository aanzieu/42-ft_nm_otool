/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:16:11 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/10 09:07:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

int get_file_statut(int fd, struct stat *buf)
{
    if (fstat(fd, buf) < 0)
    {
        perror("fstat");
        return (1);
    }
    if (S_ISDIR(buf->st_mode))
    {
        return (1);
    }
    return (0);
}

int open_file(char *arg)
{

    int fd;

    if ((fd = open(arg, O_RDONLY)) < 0)
    {
        perror("open");
        return (-1);
    }
    return fd;
}

int map_file_memory(int fd, size_t size, void **ptr)
{
    if ((*ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror("mmap");
        return (1);
    }
    return (0);
}
int open_and_map(char *prog, char *arg)
{
    int fd;
    void *ptr;
    struct stat buf;

    (void)prog;
    ptr = NULL;
    if ((fd = open_file(arg)) < 0)
        return (EXIT_FAILURE);
    if (get_file_statut(fd, &buf))
    {
        return (EXIT_FAILURE);
    }
    if (map_file_memory(fd, buf.st_size, &ptr))
    {
        return (EXIT_FAILURE);
    }
    nm(ptr);
    if (munmap(ptr, buf.st_size) < 0)
    {
        perror("mummap");
        return (EXIT_FAILURE);
    }
    return 0;
}

static int open_arg(char **arg, int i)
{
    if ((open_and_map(NM, arg[i])) != 0)
    {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// ERROR MESSAGE
// truncated or malformed object (size field of section 0 in LC_SEGMENT_64 command 1 greater than the segment)
// truncated or malformed fat file (offset plus size of cputype (7) cpusubtype (3) extends past the end of the file)

int main(int ac, char **av)
{

    // stat ftsize

    // off_t		st_size;	/* [XSI] file size, in bytes */
    //
    if (ac != 2)
    {
        fprintf(stderr, "Plese give me arg");
        return (EXIT_FAILURE);
    }
    return (open_arg(av, 1));
}