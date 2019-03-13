/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:54:10 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:34:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void	swap_mach_header_64(struct mach_header_64 *h)
{
	h->magic = ft_swap_uint32(h->magic);
	h->cputype = ft_swap_int32(h->cputype);
	h->cpusubtype = ft_swap_int32(h->cpusubtype);
	h->filetype = ft_swap_uint32(h->filetype);
	h->ncmds = ft_swap_uint32(h->ncmds);
	h->sizeofcmds = ft_swap_uint32(h->sizeofcmds);
	h->flags = ft_swap_uint32(h->flags);
	h->reserved = ft_swap_uint32(h->reserved);
}

void	swap_mach_header(struct mach_header *h)
{
	h->magic = ft_swap_uint32(h->magic);
	h->cputype = ft_swap_int32(h->cputype);
	h->cpusubtype = ft_swap_int32(h->cpusubtype);
	h->filetype = ft_swap_uint32(h->filetype);
	h->ncmds = ft_swap_uint32(h->ncmds);
	h->sizeofcmds = ft_swap_uint32(h->sizeofcmds);
	h->flags = ft_swap_uint32(h->flags);
}

void	swap_load_commands(struct load_command *lc)
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
