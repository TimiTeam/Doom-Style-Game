/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_and_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:09:12 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 06:47:01 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int					print_error_message(char *mess, char *error_obj)
{
	ft_putstr("\x1b[31mError: \x1b[33m");
	ft_putstr(mess);
	ft_putstr(" \x1b[31m");
	ft_putstr(error_obj);
	ft_putendl("\x1b[0m");
	return (0);
}

void				*print_error_message_null(char *mess, char *error_obj)
{
	print_error_message(mess, error_obj);
	return (NULL);
}

void				*error_free_array_surf(SDL_Surface **array, unsigned size, char *message)
{
	unsigned		i;

	i = 0;
	if (!array)
		return (NULL);
	while (i < size && array[i])
	{
		SDL_FreeSurface(array[i]);
		i++;
	}
	ft_memdel((void**)&array);
	return (print_error_message_null(message, "exit"));
}
