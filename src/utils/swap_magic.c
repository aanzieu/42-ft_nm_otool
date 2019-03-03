/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:54:10 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/03 11:31:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void swap_mach_header_64(struct mach_header_64 *h)
{
    h->magic = ft_swap_uint32(h->magic);           /* mach magic number identifier uint32 */
    h->cputype = ft_swap_int32(h->cputype);        /* cpu specifier int */
    h->cpusubtype = ft_swap_int32(h->cpusubtype);  /* machine specifier int */
    h->filetype = ft_swap_uint32(h->filetype);     /* type of file uint32 */
    h->ncmds = ft_swap_uint32(h->ncmds);           /* number of load commands uint32 */
    h->sizeofcmds = ft_swap_uint32(h->sizeofcmds); /* the size of all the load commands uint32 */
    h->flags = ft_swap_uint32(h->flags);           /* flags uint32 */
    h->reserved = ft_swap_uint32(h->reserved);     /* reserved uint32 */
}

void swap_mach_header(struct mach_header *h)
{
    h->magic = ft_swap_uint32(h->magic);           /* mach magic number identifier uint32 */
    h->cputype = ft_swap_int32(h->cputype);        /* cpu specifier int */
    h->cpusubtype = ft_swap_int32(h->cpusubtype);  /* machine specifier int */
    h->filetype = ft_swap_uint32(h->filetype);     /* type of file uint32 */
    h->ncmds = ft_swap_uint32(h->ncmds);           /* number of load commands uint32 */
    h->sizeofcmds = ft_swap_uint32(h->sizeofcmds); /* the size of all the load commands uint32 */
    h->flags = ft_swap_uint32(h->flags);           /* flags uint32 */
}

void swap_symtab_command(struct symtab_command *sym)
{
    sym->cmd = ft_swap_uint32(sym->cmd);
    sym->cmdsize = ft_swap_int32(sym->cmdsize);
    sym->symoff = ft_swap_int32(sym->symoff);
    sym->nsyms = ft_swap_uint32(sym->nsyms);
    sym->stroff = ft_swap_uint32(sym->stroff);
    sym->strsize = ft_swap_uint32(sym->strsize);
}

void    swap_load_commands(struct load_command *lc)
{
    lc->cmd = ft_swap_uint32(lc->cmd);
    lc->cmdsize = ft_swap_uint32(lc->cmdsize);
}

void	swap_nlist(struct nlist *symbol)
{
	symbol->n_un.n_strx = ft_swap_int32(symbol->n_un.n_strx);
	symbol->n_desc = ft_swap_int16(symbol->n_desc);
	symbol->n_value = ft_swap_int32(symbol->n_value);
}

void	swap_nlist_64(struct nlist_64 *symbol)
{
	symbol->n_un.n_strx = ft_swap_int32(symbol->n_un.n_strx);
	symbol->n_desc = ft_swap_int16(symbol->n_desc);
	symbol->n_value = ft_swap_int64(symbol->n_value);
}
