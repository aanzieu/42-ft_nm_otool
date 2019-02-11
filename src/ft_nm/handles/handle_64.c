/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:12:03 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/11 11:48:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

// t_list *add_list_of_segment_64(t_obj *obj, char *stringtable, struct nlist_64 tab)
// {
//     t_list *segment;
//     t_seg_cmd *seg_cmd;

//     seg_cmd = ft_memalloc(sizeof(t_seg_cmd) + 1);
//     // seg_cmd->segname = tab.n_value;

//     return segment;
// }

char get_symbol_type_64(struct nlist_64 array)
{

    char c = '!';

    uint8_t type;
    type = array.n_type & N_TYPE;
    if (type == N_UNDF)
        c = 'u';
    else if (type == N_ABS)
        c = 'a';
    else if (type == N_SECT)
        // printf("%d\n", array.n_sect);
        if (array.n_type & N_EXT)
            c -= 32;
    return c;
}
int for_each_symtab(t_obj *obj, struct symtab_command *sym, struct nlist_64 *array, char *stringtable)
{
    uint32_t i;
    // char *s1;
    // char *s2;
    // t_list *new;
    (void)obj;
    // obj->list = NULL;
    i = 0;
    while (i < sym->nsyms) //
    {
    puts("get Syntab");
        // s1 = stringtable + array[i].n_un.n_strx;
        // s2 = stringtable + array[i + 1].n_un.n_strx;
        // if (ft_strcmp(s1, s2) > 0) {
        //     ft_swap_str(array[i], array[i + 1]);
        //     i = 0;
        // }
        dprintf(1, "%016llx %c %s\n", array[i].n_value, get_symbol_type_64(array[i]), stringtable + array[i].n_un.n_strx);

        // array[i].n_type, stringtable + array[i].n_un.n_strx;
        // if (!(new = add_list_of_segment_64(obj, stringtable, array[i])))
        // {
        // return;
        // }
        // ft_lstadd(&obj->list, new);
        i++;
    }
    return True;
}

int add_symtab_to_list(t_obj *obj, struct symtab_command *sym)
{
    char *stringtable;
    struct nlist_64 *array;

    if (!(array = check_sizeoff_move(obj, obj->data, sym->symoff)))
    {
        puts("ARRAY ERRor Sizeoff");
        return False;
    }
    if (!(stringtable = check_sizeoff_move(obj, obj->data, sym->stroff)))
    {
        puts("Stringable False");
        return False;
    }
    return (for_each_symtab(obj, sym, array, stringtable));
}

struct symtab_command *get_symtab_command(t_obj *obj)
{
    uint32_t i;

    i = 0;
    while (i < obj->ncmds)
    {

        // if (obj->lc->cmd == LC_SEGMENT_64)
        //     // parse_segment(obj);
        //     return ((struct symtab_command *)obj->lc);
        if (obj->lc->cmd == LC_SYMTAB)
            return ((struct symtab_command *)obj->lc);
        if (!(obj->lc = check_sizeoff_move(obj, obj->lc, obj->lc->cmdsize)))
            break;
        i++;
    }
    return NULL;
}

int parse_loads_commands(t_obj *obj)
{
    struct symtab_command *sym;

    if (!(sym = get_symtab_command(obj)))
    {
        puts("ERROR Load Commands");
        return (False);
    }
    return (add_symtab_to_list(obj, sym));
}

void swap_mach_header_64(struct mach_header_64 *h)
{
    h->magic = ft_swap_uint32(h->magic);           /* mach magic number identifier uint32 */
    h->cputype = ft_swap_int32(h->cputype);       /* cpu specifier int */
    h->cpusubtype = ft_swap_int32(h->cpusubtype); /* machine specifier int */
    h->filetype = ft_swap_uint32(h->filetype);     /* type of file uint32 */
    h->ncmds = ft_swap_uint32(h->ncmds);           /* number of load commands uint32 */
    h->sizeofcmds = ft_swap_uint32(h->sizeofcmds); /* the size of all the load commands uint32 */
    h->flags = ft_swap_uint32(h->flags);           /* flags uint32 */
    h->reserved = ft_swap_uint32(h->reserved);     /* reserved uint32 */
}

int handle_64(t_obj *obj)
{
    struct mach_header_64 *header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header_64)))
    {
        puts("ERROR SizeOff");
        return (False);
    }

    header = (struct mach_header_64 *)obj->data;
    if (!obj->swap)
    {
        puts("swap header");
        swap_mach_header_64(header);
    }
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header_64))))
    {
        puts("error  Handle_64 Load Command Ligne 138");
        return (False);
    }

    /// LC COMMANDS
    return (parse_loads_commands(obj));
}