/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:12:03 by aanzieu           #+#    #+#             */
/*   Updated: 2019/01/29 12:01:54 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

struct symtab_command *get_symtab_command(t_obj *obj)
{
    uint32_t i;

    i = 0;
    while (i < obj->ncmds)
    {
        if (obj->lc->cmd == LC_SYMTAB)
        {
            return ((struct symtab_command *)obj->lc);
            // printf("nb symbole %d\n", sym->nsyms);
            // print_output(sym->nsyms, sym->symoff, sym->stroff, (char *)obj->data);
        }
        if (!(obj->lc = check_sizeoff_move(obj, obj->lc, obj->lc->cmdsize)))
            break;
        i++;
    }
    return NULL;
}

t_list *add_list_of_segment(t_obj *obj, char *stringtable, struct nlist_64 tab)
{


}
void for_each_symtab(t_obj *obj, struct symtab_command *sym, struct nlist_64 *array, char *stringtable)
{
    int     i;
    t_list *new;

    obj->list = NULL;
    i = 0;
    while (i < sym->nsyms)
    {
        if (!(new = add_list_of_segment(obj, stringtable, array[i])))
        {
            return;
        }
        ft_lstadd(&obj->list, new);
        i++;
    }
    return;
}

void add_symtab_to_list(t_obj *obj, struct symtab_command *sym)
{
    char *stringtable;
    struct nlist_64 *array;

    array = check_sizeoff_move(obj, obj->data, sym->symoff);
    stringtable = check_sizeoff_move(obj, obj->data, sym->stroff);

    for_each_symtab(obj, sym, array, stringtable);
}

void get_nlist_64(t_obj *obj)
{
    struct symtab_command *sym;

    if (!(sym = get_symtab_command(obj)))
    {
        puts("ERROR");
        exit(EXIT_FAILURE);
    }
    add_symtab_to_list(obj, sym);
}

void handle_64(t_obj *obj)
{
    // int ncmds;
    struct mach_header_64 *header;
    // struct load_command *lc;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header_64)))
    {
        puts("ERROR");
        exit(EXIT_FAILURE);
    }
    header = (struct mach_header_64 *)obj->data;
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;

    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header_64))))
    {
        puts("error");
        exit(EXIT_FAILURE);
    }
    get_nlist_64(obj);
    // obj->
    // origin_ptr + st_size (struct stat check) < ptr + sizeof (macheader) return error
    //
    // ncmds = header->ncmds;
}