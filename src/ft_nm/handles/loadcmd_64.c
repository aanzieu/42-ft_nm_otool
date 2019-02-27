/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadcmd_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:49:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/27 12:07:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

/**
 * Get index 64
 * */
static void get_index_segname_64(t_obj *obj, struct segment_command_64 *seg, struct section_64 *sect, uint32_t index)
{
    if (ft_strequ(seg->segname, "__TEXT") && ft_strequ(sect->sectname, "__text"))
        obj->tss = index;
    else if (ft_strequ(seg->segname, "__DATA") && ft_strequ(sect->sectname, "__data"))
        obj->dss = index;
    else if (ft_strequ(seg->segname, "__DATA") && ft_strequ(sect->sectname, "__bss"))
        obj->bss = index;
}

/**
 ** Parse Symbat and print after
 **/
static int read_symbat_command_64(t_obj *obj, struct symtab_command *sym)
{
    char *stringtable;
    struct nlist_64 *array;

    if (!(stringtable = check_sizeoff_move(obj, obj->data, sym->stroff)))
    {
        puts("Stringable Err");
        return Err;
    }
    
    if (!(array = sort_64(obj, sym, stringtable)))
    {
        puts("ARRAY ERRor Sizeoff");
        return Err;
    }

    return (for_each_symtab_64(obj, sym, array, stringtable));
}

/**
 ** For all section inside Seg cmooamnd search index for each symtab
 **/
static int read_segment_command_64(t_obj *obj, struct segment_command_64 *seg)
{
    struct section_64 *sect;
    int i;
    obj->dss = 1;
    obj->tss = 1;
    obj->bss = 1;

    if (!obj->swap)
    {
        seg->nsects = ft_swap_uint32(seg->nsects);
    }
    i = -1;
    while (++i < (int)seg->nsects)
    {
        if (!(sect = check_sizeoff_move(obj, seg, sizeof(struct segment_command_64))))
        {
            puts("error readsegment command\n");
            return Err;
        }
        if ((sect = check_sizeoff_move(obj, sect, i * sizeof(struct section_64))))
        {
            if (check_sizeoff(obj, sect->segname, 16) && check_sizeoff(obj, sect->sectname, 16))
            {
                get_index_segname_64(obj, seg, sect, obj->index_sec);
                obj->index_sec++;
            }
            else
            {
                puts("error sizeof segname command\n");
                // return Err;
            }
        }
    }
    return Ok;
}

/**
 * Check all load command 
 * if Segment or Symtab for struct 64
 **/
int parse_load_command_64(t_obj *obj)
{
    struct segment_command_64 *seg;

    if (obj->lc->cmd == LC_SEGMENT_64)
    {
        if (!(seg = check_sizeoff_move(obj, obj->lc, sizeof(struct segment_command_64))))
        {
            puts("error Segment Command \n");
            return Err;
        }
        return (read_segment_command_64(obj, seg));
    }
    if (obj->lc->cmd == LC_SYMTAB)
    {
        if (!(obj->sym = (struct symtab_command *)obj->lc))
        {
            puts("ERROR Load Commands");
            return (Err);
        }
        return (read_symbat_command_64(obj, obj->sym));
    } //
    return Ok;
}