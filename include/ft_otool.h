/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/18 18:44:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "ft_utils.h"

# define PROGRAM "ft_otool"

int 		help_otool(void);
int 		otool(t_obj *obj);

int						handle_static_lyb(t_obj *obj);

int 		print_hex_32(t_obj *obj, void *start, struct section section);
int 		print_hex_64(t_obj *obj, void *start, struct section_64 section);

void		print_cpu_type(t_obj *obj);

int 		handle_32(t_obj *obj);
int			handle_64(t_obj *obj);


int			handle_fat_64(t_obj *obj);
int			handle_fat_32(t_obj *obj);

int 		parse_fat_arch_32(t_obj *obj, struct fat_header *ft);



// /*
// ** Utils Open function
// */


// int						parse_options_flags(int ac, const char **av,
						// t_option *option);

// /*
// ** NM function
// */

// int						nm(t_obj *obj);

// /*
// ** handle
// */

// int						handle_64(t_obj *obj);
// int						handle_32(t_obj *obj);
// int						handle_fat_32(t_obj *obj);
// int						handle_fat_64(t_obj *obj);
// int						handle_static_lyb(t_obj *obj);

// /*
// ** Parsing functions
// */

// int						parse_fat_arch_32(t_obj *obj, struct fat_header *ft);
// int						parse_fat_arch_64(t_obj *obj, struct fat_header *ft);
// int						parse_load_command_64(t_obj *obj,
// 						struct load_command *lc);
// int						parse_load_command_32(t_obj *obj,
// 						struct load_command *lc);

// /*
// **  Print Functions
// */

// void					print_option_m(t_seg_list seg, t_obj *obj);
// void					print_nstabs(t_seg_list seg, t_obj *obj);
// char					get_char_type_64(t_seg_list seg_list, t_obj *obj);
// char					get_char_type_32(t_seg_list seg_list, t_obj *obj);
// int						for_each_symtab_32(t_obj *obj, t_list *array);
// int						for_each_symtab_64(t_obj *obj, t_list *array);
// void					print_output(int nsyms, unsigned int symoff,
// 						unsigned int stroff, char *ptr);
// void					print_value_64(t_seg_list array, char c, t_obj *obj);
// void					print_value_32(t_seg_list array, char c, t_obj *obj);

// /*
// ** Sort list of array
// */

// t_list					*sort_64(t_obj *obj, struct symtab_command *sym,
// 						char *stringtable);
// t_list					*sort_32(t_obj *obj, struct symtab_command *sym,
// 						char *stringtable);
// void					sort_ascii(t_obj *obj, t_list **lst);
// void					sort_num(t_obj *obj, t_list **lst);

#endif