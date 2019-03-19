/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 08:58:27 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/19 08:39:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# ifdef __i386__
#  define ARCH_TYPE "i386"
# endif

# ifdef __x86_64__
#  define ARCH_TYPE "x86_64"
# endif

# ifdef __ppc__
#  define ARCH_TYPE "ppc"
# endif

# ifndef __i386__
#  ifndef __ppc__
#   ifndef __x86_64__
#    define ARCH_TYPE ""
#   endif
#  endif
# endif

# include <fcntl.h>
# include <ar.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define ERR_OPEN "No such file or directory : "
# define ERR_STAT "a problem was encountered with fstat"
# define ERR_MAP "The file was not recognized as a valid object file"
# define ERR_MUNMAP "a problem was encountered with munmap"
# define NOT_VALID "The file was not recognized as a valid object file"

# define MALFORMED "truncated or malformed "
# define ERR_LC "(offset field of load_command not past)"
# define ERR_MH64 "(offset field of mach-Header_64 not past)"
# define ERR_MH "(offset field of mach-Header not past)"
# define ERR_FH64 "(offset filed data from fat_arch_64 not past, and is empty)"
# define ERR_FH "(offset filed data from fat_arch not past, and is empty)"

# define ERR_SEG64 "(offset filed data from segment command 64 not past)"
# define ERR_SEG "(offset filed data from segment_command not past)"
# define ERR_SECT64 "(offset filed data from section_64 not past)"
# define ERR_SECT "(offset filed data from section not past)"
# define ERR_SYMTAB "(offset filed data from synmbat not past)"
# define ERR_STR "bad string index"

# define ERR_OPT_REQ 1
# define ERR_OPT_ILL 0
# define ERR_ARG_REQ ": option requires an argument --"
# define ERR_ARG_ILL ": illegal option -- "

# define C_NONE		"\033[0m"
# define C_BOLD		"\033[1m"
# define C_UNDER	"\033[4m"
# define C_FLASH	"\033[5m"
# define C_REVERS	"\033[7m"
# define C_BLACK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_BROWN	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_MAGENTA	"\033[35m"
# define C_CYAN		"\033[36m"
# define C_GREY		"\033[37m"
# define B_BLACK	"\033[40m"
# define B_RED		"\033[41m"
# define B_GREEN	"\033[42m"
# define B_ORANGE	"\033[43m"
# define B_BLUE		"\033[44m"
# define B_CYAN		"\033[46m"
# define B_GREY		"\033[47m"
# define CD_GREY	"\033[90m"
# define CL_RED		"\033[91m"
# define CL_GREEN	"\033[92m"
# define C_YELLOW	"\033[93m"
# define CL_BLUE	"\033[94m"
# define CL_TURQ	"\033[96m"
# define BD_GREY	"\033[100m"
# define BL_RED		"\033[101m"
# define BL_GREEN	"\033[102m"
# define B_YELLOW	"\033[103m"
# define BL_BLUE	"\033[104m"
# define BL_PURPLE	"\033[105m"
# define B_TURQ		"\033[106m"

typedef enum				e_byteorder {
	UnknownByteOrder,
	LittleEndian,
	BigEndian
}							t_byteorder;

typedef enum				e_endian
{
	BIG,
	LITTLE,
	UNKNOWN
}							t_endian;

typedef enum				e_return
{
	Ok,
	Err,
	Seg = -11
}							t_return;

typedef enum				e_bool
{
	True,
	False,
}							t_bool;

typedef struct				s_arch_flag
{
	const char				*name;
	cpu_type_t				cputype;
	cpu_subtype_t			cpusubtype;
	enum e_byteorder		byte_order;
	char					*type;
}							t_arch_flag;

typedef struct				s_option
{
	int						opt_ind;
	int						opt_err;
	char					*opt_arg;
	int						opt_opt;
	t_bool					a;
	t_bool					g;
	t_bool					a_upcase;
	t_bool					n;
	t_bool					p;
	t_bool					r;
	t_bool					u;
	t_bool					u_upcase;
	t_bool					m;
	t_bool					j;
	t_bool					print_arch;
	t_bool					print_lib;
}							t_option;

typedef struct				s_obj
{
	const char				*path;
	const void				*data;
	size_t					size_data;
	uint32_t				magic;
	cpu_type_t				cputype;
	cpu_subtype_t			cpusubtype;
	uint32_t				filetype;
	uint32_t				ncmds;
	uint32_t				sizeofcmds;
	struct load_command		*lc;
	struct symtab_command	*sym;
	t_list					*library;
	t_option				*flags;
	t_bool					swap;
	t_bool					is_fat;
	t_bool					already_print;
	int						index_sec;
	int						tss;
	int						bss;
	int						dss;
}							t_obj;

/*
** Swap Bitwise
*/

int							ft_swap_int(int val);
int16_t						ft_swap_int16(int16_t val);
int32_t						ft_swap_int32(int32_t val);
int64_t						ft_swap_int64(int64_t val);
uint16_t					ft_swap_uint16(uint16_t val);
uint32_t					ft_swap_uint32(uint32_t val);
uint64_t					ft_swap_uint64(uint64_t val);
uint16_t					ifswap16(t_obj *obj, uint16_t x);
uint32_t					ifswap32(t_obj *obj, uint32_t x);
uint64_t					ifswap64(t_obj *obj, uint64_t x);

/*
** Swap Function For Segment And Section And ogher Struct inside
*/

void						swap_nlist(struct nlist *array);
void						swap_nlist_64(struct nlist_64 *array);
void						swap_mach_header_64(struct mach_header_64 *h);
void						swap_mach_header(struct mach_header *h);
void						swap_fat_header(struct fat_header *fh);
void						swap_symtab_command(struct symtab_command *sym);
void						swap_load_commands(struct load_command *lc);
void						swap_fat_arch_64(struct fat_arch_64 *fh);
void						swap_fat_arch(struct fat_arch *fh);
void						swap_section(struct section *s, uint32_t nsects);
void						swap_section_64(struct section_64 *s,
							uint32_t nsects);

/*
** Errors
*/

int							errors_fd(const char *str, const char *line,
		int fd, t_return err);
void						*errors_fd_null(const char *str,
		const char *line, int fd);

/*
** check void pointer to parse data inside date
*/

char						*checkoff_string(t_obj *obj,
							char *str, uint32_t off);
void						*check_sizeoff(t_obj *obj,
							const void *start, size_t size);
void						*check_sizeoff_move(t_obj *obj,
							const void *start, size_t size);
t_bool						checkoff_endofstring(t_obj *obj, char *str);

/*
** Utils Open function
*/

int							get_file_statut(int const fd, struct stat *buf);
int							open_file(char const *arg);
int							map_file_memory(int const fd, size_t const size,
							void **ptr);
int							parse_options_flags(int ac, const char **av,
							t_option *option, char *flags);

/*
** check cputype
*/

void						print_cpu_type(t_obj *input);
void						print_stat_lyb(t_obj *obj, void *offset);
t_arch_flag					get_arch_type(cpu_type_t cputype,
							cpu_subtype_t cpusubtype);

char						ntype_if_upper(char c, uint8_t ntype);
int							get_options(int argc, char const *argv[],
							const char *optstring, t_option *opt);

#endif
