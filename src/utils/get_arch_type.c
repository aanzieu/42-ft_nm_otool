// #include "../../include/ft_nm.h"
#include <mach/mach.h>
// code source https://opensource.apple.com/source/cctools/cctools-573.1/libstuff/arch.c for type of CPU infos

struct arch_flag
{
    char *name;
    cpu_type_t cputype;
    cpu_subtype_t cpusubtype;
};

static const struct arch_flag arch_flags[] = {
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



int get_arch_from_flag(char *name, struct arch_flag *arch_flag)
{
    unsigned long i;

    for (i = 0; arch_flags[i].name != NULL; i++)
    {
        if (strcmp(arch_flags[i].name, name) == 0)
        {
            if (arch_flag != NULL)
                *arch_flag = arch_flags[i];
            return (1);
        }
    }
    if (arch_flag != NULL)
        memset(arch_flag, '\0', sizeof(struct arch_flag));
    return (0);
}