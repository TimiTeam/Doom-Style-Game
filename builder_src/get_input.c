/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:04:19 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/15 13:58:44 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					*del_char(char *input)
{
	size_t				i;
	char				*new;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
		i++;
	if (!i || !(new = ft_strnew(sizeof(char) * (i - 1))))
	{
		free(input);
		return (NULL);
	}
	new = ft_strncpy(new, input, sizeof(char) * (i - 1));
	free(input);
	return (new);
}

char					*add_char(char *input, char to_add)
{
	size_t				i;
	size_t				j;
	char				*new;

	if (!input)
		i = 0;
	else
		i = ft_strlen(input);
	if (!(new = ft_strnew(sizeof(char) * (i + 1))))
		return (NULL);
	j = 0;
	while (j < i && input[j])
	{
		new[j] = input[j];
		j++;
	}
	new[j++] = to_add;
	new[j] = '\0';
	return (new);
}

char					*get_input(char *init, char change)
{
	static char			*input = NULL;
	char				*tmp;

	if (init)
	{
		if (input)
			free(input);
		return ((input = ft_strdup(init)));
	}
	if (ft_isalnum(change))
	{
		tmp = input ? ft_strdup(input) : NULL;
		if (input)
			free(input);
		input = add_char(tmp, change);
		if (tmp)
			free(tmp);
	}
	else if (change == 8 && !input)
		return (NULL);
	else if (change == 8)
		input = del_char(input);
	return (input);
}

t_vec					get_arrow_input(SDL_Keycode key, t_vec old)
{
	if (key == SDLK_UP)
		old.y -= 7;
	else if (key == SDLK_DOWN)
		old.y += 7;
	else if (key == SDLK_LEFT)
		old.x -= 7;
	else if (key == SDLK_RIGHT)
		old.x += 7;
	return (old);
}
