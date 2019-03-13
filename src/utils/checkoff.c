/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkoff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <aanzieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 09:15:01 by aanzieu           #+#    #+#             */
/*   Updated: 2019/03/13 10:11:18 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void			*check_sizeoff(t_obj *obj, const void *start, size_t size)
{
	uint8_t		s;
	int64_t		d;

	s = (uint8_t *)start - (uint8_t *)obj->data;
	d = (obj->data + obj->size_data) - (start + size);
	if (obj->size_data < s + size || d < 0)
		return (NULL);
	return ((void *)start);
}

void			*check_sizeoff_move(t_obj *obj, const void *start, size_t size)
{
	if (check_sizeoff(obj, start, size))
		return ((void *)start + size);
	return (NULL);
}

char			*checkoff_string(t_obj *obj, char *str, uint32_t off)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!(ret = check_sizeoff_move(obj, (void *)str, off)))
		return (NULL);
	while (ret && check_sizeoff(obj, (void *)ret, i))
	{
		if (!check_sizeoff(obj, (void *)ret, i))
			return (NULL);
		i++;
	}
	return (ret);
}

t_bool			checkoff_endofstring(t_obj *obj, char *str)
{
	int		ret;
	size_t	i;

	i = 0;
	ret = False;
	if (str)
	{
		while (check_sizeoff(obj, (void *)str, i + 1))
		{
			ret = False;
			if (str[i] == '\0')
			{
				ret = True;
				break ;
			}
			i++;
		}
	}
	return ((t_bool)ret);
}
