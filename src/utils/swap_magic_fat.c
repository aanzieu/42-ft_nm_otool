/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_magic_fat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:33:14 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:35:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void	swap_fat_header(struct fat_header *fh)
{
	fh->magic = ft_swap_uint32(fh->magic);
	fh->nfat_arch = ft_swap_uint32(fh->nfat_arch);
}

void	swap_fat_arch(struct fat_arch *fa)
{
	fa->cputype = ft_swap_uint32(fa->cputype);
	fa->cpusubtype = ft_swap_uint32(fa->cpusubtype);
	fa->offset = ft_swap_uint32(fa->offset);
	fa->size = ft_swap_uint32(fa->size);
	fa->align = ft_swap_uint32(fa->align);
}

void	swap_fat_arch_64(struct fat_arch_64 *fa)
{
	fa->cputype = ft_swap_int64(fa->cputype);
	fa->cpusubtype = ft_swap_int64(fa->cpusubtype);
	fa->offset = ft_swap_uint64(fa->offset);
	fa->size = ft_swap_uint64(fa->size);
	fa->align = ft_swap_uint32(fa->align);
	fa->reserved = ft_swap_uint32(fa->reserved);
}

void	swap_symtab_command(struct symtab_command *sym)
{
	sym->cmd = ft_swap_uint32(sym->cmd);
	sym->cmdsize = ft_swap_int32(sym->cmdsize);
	sym->symoff = ft_swap_int32(sym->symoff);
	sym->nsyms = ft_swap_uint32(sym->nsyms);
	sym->stroff = ft_swap_uint32(sym->stroff);
	sym->strsize = ft_swap_uint32(sym->strsize);
}
