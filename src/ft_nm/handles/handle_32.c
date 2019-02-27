/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:53:26 by aanzieu           #+#    #+#             */
/*   Updated: 2019/02/26 08:23:17 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_nm.h"

static int     parse_loads_commands_32(t_obj *obj)
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

        if (parse_load_command_32(obj))
        {
            return Err;
        }
        if (!(obj->lc = check_sizeoff_move(obj, obj->lc, obj->lc->cmdsize)))
            return Err;
        i++;
    }
    return (Ok);
}


int     handle_32(t_obj *obj)
{
    struct mach_header *header;

    if (!check_sizeoff(obj, obj->data, sizeof(struct mach_header)))
    {
        puts("ERROR SizeOff");
        return (Err);
    }
    if (!(obj->lc = check_sizeoff_move(obj, obj->data, sizeof(struct mach_header))))
    {
        puts("error  Handle_32 Load Command Ligne 138");
        return (Err);
    }
    header = (struct mach_header *)obj->data;
    if (!obj->swap)
    {
        swap_mach_header(header);
    }
    obj->cpusubtype = header->cpusubtype;
    obj->cputype = header->cputype;
    obj->ncmds = header->ncmds;
    obj->filetype = header->filetype;
    return (parse_loads_commands_32(obj));
}