/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:23:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/03 15:32:24 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"
#include <mach/mach.h>
// code source https://opensource.apple.com/source/cctools/cctools-573.1/libstuff/arch.c for type of CPU infos

static const t_arch_flag arch_tab[] = {
    {"error", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE},
    {"any", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE},
    {"little", CPU_TYPE_ANY, CPU_SUBTYPE_LITTLE_ENDIAN},
    {"big", CPU_TYPE_ANY, CPU_SUBTYPE_BIG_ENDIAN},

    /* 64-bit Mach-O architectures */

    /* architecture families */
    {"ppc64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL},
    /* specific architecture implementations */
    {"ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970},

    /* 32-bit Mach-O architectures */

    /* architecture families */
    {"ppc", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL},
    {"i386", CPU_TYPE_I386, CPU_SUBTYPE_I386_ALL},
    {"m68k", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL},
    {"hppa", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_ALL},
    {"sparc", CPU_TYPE_SPARC, CPU_SUBTYPE_SPARC_ALL},
    {"m88k", CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL},
    {"i860", CPU_TYPE_I860, CPU_SUBTYPE_I860_ALL},
    // { "veo",    CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_ALL },
    /* specific architecture implementations */
    {"ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601},
    {"ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603},
    {"ppc603e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e},
    {"ppc603ev", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603ev},
    {"ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604},
    {"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e},
    {"ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750},
    {"ppc7400", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7400},
    {"ppc7450", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450},
    {"ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970},
    {"i486", CPU_TYPE_I386, CPU_SUBTYPE_486},
    {"i486SX", CPU_TYPE_I386, CPU_SUBTYPE_486SX},
    {"pentium", CPU_TYPE_I386, CPU_SUBTYPE_PENT}, /* same as i586 */
    {"i586", CPU_TYPE_I386, CPU_SUBTYPE_586},
    {"pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO}, /* same as i686 */
    {"i686", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO},
    {"pentIIm3", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3},
    {"pentIIm5", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5},
    {"m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY},
    {"m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040},
    {"hppa7100LC", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_7100LC},
    // { "veo1",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_1 },
    // { "veo2",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_2 },
    {NULL, 0, 0}};

t_arch_flag get_arch_type(cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
    int index;

    index = -1;
    while (arch_tab[++index].name)
    {
        if (arch_tab[index].cputype == cputype &&
            arch_tab[index].cpusubtype == cpusubtype)
            break;
    }
    return (arch_tab[index]);
}