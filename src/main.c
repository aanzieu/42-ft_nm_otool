/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:16:11 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/08 14:38:16 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr)
{

    int i;
    char    *stringtable;
    struct nlist_64 *array;

    array = (void*)ptr + symoff;
    stringtable = (void*)ptr + stroff;
    i = 0;
    while (i < nsyms)
    {
        printf("%s\n", stringtable + array[i].n_un.n_strx);
        i++;
    }
}

void handle_64(char *ptr)
{
    int ncmds;
    int i;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;

    header = (struct mach_header_64 *)ptr;
    ncmds = header->ncmds;
    i = 0;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SYMTAB)
        {

            puts("C'est le bon");
            sym = (struct symtab_command *)lc;
            printf("nb symbole %d\n", sym->nsyms);
            print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *)lc + lc->cmdsize; // on veut bouger exactement de dmdsize
        i++;
    }
}

void nm(char *ptr)
{
    int magic_number;

    magic_number = *(int *)ptr;
    if (magic_number == MH_MAGIC_64)
    {
        puts("binaire 64");
        handle_64(ptr);
    }
}

int main(int ac, char **av)
{
    int fd;
    char *ptr;
    struct stat buf;

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
    if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
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