/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:23:48 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 11:16:42 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"
#include <mach/mach.h>

/*
** code source :
** https://opensource.apple.com/source/cctools/cctools-573.1/libstuff/arch.c
** for type of CPU infos
** https://opensource.apple.com/source/cctools/cctools-809/libmacho/arch.c
** https://opensource.apple.com/source/cctools/cctools-809/libmacho/
*/

static const t_arch_flag g_arch_tab[] = {
	{"hppa", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_ALL,
		BigEndian, "HP-PA"},
	{"i386", CPU_TYPE_I386, CPU_SUBTYPE_I386_ALL,
		LittleEndian, "Intel 80x86"},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL,
		LittleEndian, "Intel x86-64"},
	{"i860", CPU_TYPE_I860, CPU_SUBTYPE_I860_ALL,
		BigEndian, "Intel 860"},
	{"m68k", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL,
		BigEndian, "Motorola 68K"},
	{"m88k", CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL,
		BigEndian, "Motorola 88K"},
	{"ppc", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL,
		BigEndian, "PowerPC"},
	{"ppc64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL,
		BigEndian, "PowerPC 64-bit"},
	{"sparc", CPU_TYPE_SPARC, CPU_SUBTYPE_SPARC_ALL,
		BigEndian, "SPARC"},
	{"arm", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_ALL,
		LittleEndian, "ARM"},
	{"any", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE,
		UnknownByteOrder, "Architecture Independent"},
	{"hppa7100LC", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_7100LC,
		BigEndian, "HP-PA 7100LC"},
	{"m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY,
		BigEndian, "Motorola 68030"},
	{"m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040,
		BigEndian, "Motorola 68040"},
	{"i486", CPU_TYPE_I386, CPU_SUBTYPE_486,
		LittleEndian, "Intel 80486"},
	{"i486SX", CPU_TYPE_I386, CPU_SUBTYPE_486SX,
		LittleEndian, "Intel 80486SX"},
	{"pentium", CPU_TYPE_I386, CPU_SUBTYPE_PENT,
		LittleEndian, "Intel Pentium"},
	{"i586", CPU_TYPE_I386, CPU_SUBTYPE_586,
		LittleEndian, "Intel 80586"},
	{"pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO,
		LittleEndian, "Intel Pentium Pro"},
	{"i686", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO,
		LittleEndian, "Intel Pentium Pro"},
	{"pentIIm3", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3,
		LittleEndian, "Intel Pentium II Model 3"},
	{"pentIIm5", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5,
		LittleEndian, "Intel Pentium II Model 5"},
	{"pentium4", CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4,
		LittleEndian, "Intel Pentium 4"},
	{"ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601,
		BigEndian, "PowerPC 601"},
	{"ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603,
		BigEndian, "PowerPC 603"},
	{"ppc603e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e,
		BigEndian, "PowerPC 603e"},
	{"ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604,
		BigEndian, "PowerPC 604"},
	{"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e,
		BigEndian, "PowerPC 604e"},
	{"ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750,
		BigEndian, "PowerPC 750"},
	{"ppc7400", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7400,
		BigEndian, "PowerPC 7400"},
	{"ppc7450", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450,
		BigEndian, "PowerPC 7450"},
	{"ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970,
		BigEndian, "PowerPC 970"},
	{"ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970,
		BigEndian, "PowerPC 970 64-bit"},
	{"armv4t", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V4T,
		LittleEndian, "arm v4t"},
	{"armv5", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V5TEJ,
		LittleEndian, "arm v5"},
	{"xscale", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_XSCALE,
		LittleEndian, "arm xscale"},
	{"armv6", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6,
		LittleEndian, "arm v6"},
	{"armv7", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7,
		LittleEndian, "arm v7"},
	{"armv7f", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7F,
		LittleEndian, "arm v7f"},
	{"armv7k", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7K,
		LittleEndian, "arm v7k"},
	{"little", CPU_TYPE_ANY, CPU_SUBTYPE_LITTLE_ENDIAN,
		LittleEndian, "Little Endian"},
	{"big", CPU_TYPE_ANY, CPU_SUBTYPE_BIG_ENDIAN,
		BigEndian, "Big Endian"},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_ALL,
		LittleEndian, "Arm64 all"},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_V8,
		LittleEndian, "Arm64 V8"},
	{"armv6m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6M,
		LittleEndian, "arm v6m"},
	{"armv7em", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7EM,
		LittleEndian, "arm v7em"},
	{"armv7m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7M,
		LittleEndian, "arm v7m"},
	{"armv7s", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7S,
		LittleEndian, "arm v7s"},
	{"armv8", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V8,
		LittleEndian, "arm v8"},
	{"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e,
		BigEndian, "PowerPC 604e"},
	{"x86_64", CPU_TYPE_X86_64, 0x80000003,
		LittleEndian, "Intel x86-64"},
	{"x86_64", CPU_TYPE_I386, CPU_SUBTYPE_X86_64_H,
		LittleEndian, "Intel x86-64"},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H,
		LittleEndian, "Intel x86-64"},
	{NULL, 0, 0, 0, NULL}
};

t_arch_flag		get_arch_type(cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
	int index;

	index = -1;
	while (g_arch_tab[++index].name)
	{
		if (g_arch_tab[index].cputype == cputype &&
				g_arch_tab[index].cpusubtype == cpusubtype)
			break ;
	}
	return (g_arch_tab[index]);
}
