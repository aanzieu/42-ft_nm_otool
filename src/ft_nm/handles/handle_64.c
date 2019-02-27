/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:12:03 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/26 15:59:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"



static int     parse_loads_commands_64(t_obj *obj)
{
    uint32_t i;

    i = 0;
    obj->index_sec = 1;
    while (i < obj->ncmds)
    {
        if (!obj->swap)
        {
            swap_load_commands(obj->lc);
        }

        if (parse_load_command_64(obj))
        {
            return Err;
        }
        if (!(obj->lc = check_sizeoff_move(obj, obj->lc, obj->lc->cmdsize)))
            return Err;
        i++;
    }
    return (Ok);
}


int     handle_64(t_obj *obj)
{
    struct mach_header_64 *header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header_64)))
    {
        puts("ERROR SizeOff");
        return (Err);
    }
    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header_64))))
    {
        puts("error  Handle_64 Load Command Ligne 138");
        return (Err);
    }
    header = (struct mach_header_64 *)obj->data;
    if (!obj->swap)
    {
        swap_mach_header_64(header);
    }
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    obj->filetype = header->filetype;
    return (parse_loads_commands_64(obj));
}