/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:16:11 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/04 13:59:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

static int parse_data_nm(t_obj *obj)
{
    if (nm(obj))
    {
        puts("error");
        return (EXIT_FAILURE);
    }
    if (munmap((void *)obj->data, obj->size_data) < 0)
    {
        perror("munmap failed");
        return (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/**
 * Check fd and file status 
 * Check map memory and lauch nm
 **/
static int open_and_map(char *arg, t_obj *obj)
{
    int fd;
    void *data;
    struct stat buf;

    data = NULL;
    if ((fd = open_file(arg)) < 0)
        return (EXIT_FAILURE);
    if (get_file_statut(fd, &buf))
        return (EXIT_FAILURE);
    if (map_file_memory(fd, buf.st_size, &data))
        return (EXIT_FAILURE);
    if (obj)
    {
        obj->path = ft_strdup(arg);
        obj->data = data;
        obj->size_data = buf.st_size;
    }
    return (parse_data_nm(obj));
}

static int open_arg(char **arg, int i)
{
    t_obj obj;

    obj.is_fat = False;

    if ((open_and_map(arg[i], &obj)) != 0){
        return (EXIT_FAILURE);
    }
    return (0);
}

// ERROR MESSAGE
// truncated or malformed object (size field of section 0 in LC_SEGMENT_64 command 1 greater than the segment)
// truncated or malformed fat file (offset plus size of cputype (7) cpusubtype (3) extends past the end of the file)

int main(int ac, char **av)
{
    // off_t		st_size;	/* [XSI] file size, in bytes */
    if (ac != 2)
    {
        fprintf(stderr, "Plese give me arg");
        return (EXIT_FAILURE);
    }
    return (open_arg(av, 1));
}