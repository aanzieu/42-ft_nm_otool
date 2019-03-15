/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 15:55:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "ft_utils.h"

# define PROGRAM "ft_nm"

typedef struct			s_seg_list
{
	char				*name;
	char				*library;
	char				sectname[16];
	char				segname[16];
	uint8_t				n_type;
	uint8_t				n_sect;
	uint64_t			n_value;
	int16_t				n_desc;
}						t_seg_list;



/*
** NM function
*/

int						nm(t_obj *obj);

/*
** handle
*/

int						handle_64(t_obj *obj);
int						handle_32(t_obj *obj);
int						handle_fat_32(t_obj *obj);
int						handle_fat_64(t_obj *obj);
int						handle_static_lyb(t_obj *obj);

/*
** Parsing functions
*/

int						parse_fat_arch_32(t_obj *obj, struct fat_header *ft);
int						parse_fat_arch_64(t_obj *obj, struct fat_header *ft);
int						parse_load_command_64(t_obj *obj,
						struct load_command *lc);
int						parse_load_command_32(t_obj *obj,
						struct load_command *lc);

/*
**  Print Functions
*/

void					print_option_m(t_seg_list seg, t_obj *obj);
void					print_nstabs(t_seg_list seg, t_obj *obj);
char					get_char_type_64(t_seg_list seg_list, t_obj *obj);
char					get_char_type_32(t_seg_list seg_list, t_obj *obj);
int						for_each_symtab_32(t_obj *obj, t_list *array);
int						for_each_symtab_64(t_obj *obj, t_list *array);
void					print_output(int nsyms, unsigned int symoff,
						unsigned int stroff, char *ptr);
void					print_value_64(t_seg_list array, char c, t_obj *obj);
void					print_value_32(t_seg_list array, char c, t_obj *obj);

/*
** Sort list of array
*/

t_list					*sort_64(t_obj *obj, struct symtab_command *sym,
						char *stringtable);
t_list					*sort_32(t_obj *obj, struct symtab_command *sym,
						char *stringtable);
void					sort_ascii(t_obj *obj, t_list **lst);
void					sort_num(t_obj *obj, t_list **lst);

#endif
