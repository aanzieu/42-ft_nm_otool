/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:14:42 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 09:16:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr)
{

    int                 i;
    char                *stringtable;
    struct nlist_64     *array;
    // uint8_t              type;

    array = (void *)ptr + symoff;
    stringtable = (void *)ptr + stroff;
    i = 0;
    while (i < nsyms)
    {
        // printf("%c - %s\n",array[i].n_type, stringtable + array[i].n_un.n_strx);
        dprintf(1, "%s\n",stringtable + array[i].n_un.n_strx);
        // printf("coucou\n");
        i++;
    }
}