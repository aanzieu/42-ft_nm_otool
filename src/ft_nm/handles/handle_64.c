/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:12:03 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/09 10:26:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

void handle_64(void *ptr)
{
    int ncmds;
    int i;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;

    // origin_ptr + st_size (struct stat check) < ptr + sizeof (macheader) return error
    //
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