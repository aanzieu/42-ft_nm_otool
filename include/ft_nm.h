/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:32:18 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/04 11:57:13 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "ft_utils.h"

#define NM "ft_nm"

typedef struct s_seg_list
{
    char *name;
    // segment_command
    char sectname[16];
    char segname[16];
    // n_list
    uint8_t n_type;
    uint8_t n_sect;
    uint64_t n_value;

} t_seg_list;

/**
 * Utils Open function
 **/
int get_file_statut(int const fd, struct stat *buf);
int open_file(char const *arg);
int map_file_memory(int const fd, size_t const size, void **ptr);

/*
** NM function
*/
int nm(t_obj *obj);

/*
** swap Magic function
*/
void swap_magic(void);

/*
** handle
*/

int handle_64(t_obj *obj);
int handle_32(t_obj *obj);
int handle_fat_32(t_obj *obj);
int handle_fat_64(t_obj *obj);


int parse_load_command_64(t_obj *obj);
int parse_load_command_32(t_obj *obj);

/*
*  Print
*
*/
char get_char_type_64(t_seg_list seg_list, t_obj *obj);
char get_char_type_32(t_seg_list seg_list, t_obj *obj);

int for_each_symtab_32(t_obj *obj, struct symtab_command *sym, t_list *array, char *stringtable);
int for_each_symtab_64(t_obj *obj, struct symtab_command *sym, t_list *array, char *stringtable);

/*
**
*/
void print_output(int nsyms, unsigned int symoff, unsigned int stroff, char *ptr);

t_list *sort_64(t_obj *obj, struct symtab_command *sym, char *stringtable);
t_list *sort_32(t_obj *obj, struct symtab_command *sym, char *stringtable);
void	sort_ascii(t_obj *obj, t_list **lst);
void	sort_num(t_obj *obj, t_list **lst);

#endif