/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:33:51 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 04:52:44 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"


char			*get_data_from_line(char *line, char *fill_from, float *one, float *two)
{
	int				i;

	i = 0;
	while (*line && !ft_isalpha(*line))
		line++;
	if (ft_strncmp(line, fill_from, ft_strlen(fill_from)) ||
		!(line = skip_line_with_word(line, fill_from)))
		return (print_error_message_null("Can't create: '", fill_from));
	if(!(i = get_numbers(one, two, ' ', line)))
		return (print_error_message_null("Can't fill: '", fill_from));
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	return (&line[i]);
}

static char			*fill_floor_and_ceil(t_sector *sector,
		SDL_Surface **textures, char *line, int max_tex)
{
	float			text;
	char			*orig;

	if (!sector || !line || !textures)
		return (0);
	if (!(line = get_data_from_line((orig = line), "floor", &sector->floor, &text)) || text > max_tex)
		return (print_error_message_null("Wrong line: ", orig));
	sector->floor_tex = textures[(int)text];
	if (!(line = get_data_from_line((orig = line), "ceil", &sector->ceil, &text)) || text > max_tex)
		return (print_error_message_null("Wrong line: ", orig));
	sector->ceil_tex = textures[(int)text];
	if (sector->ceil < sector->floor)
		sector->ceil = sector->floor;
	if (sector->floor == sector->ceil)
		sector->ceil += 0.2;
	sector->ceil = sector->ceil < 1000 ? sector->ceil : 1000;
	sector->floor = sector->floor < 1000 ? sector->floor : 1000;
	return (line);
}

void				*error_free_t_sector(t_sector **sect, char *message, char *line)
{
	if (sect && *sect)
	{
		delete_sectors(*sect);
		*sect = NULL;
	}
	return (print_error_message_null(message, line));
}

char				*skip_line_with_word(char *line, char *word)
{
	int				j;

	if (!line || !word)
		return (NULL);
	j = 0;
	while (*line)
	{
		while (*line && *word && *line == *word)
		{
			line++;
			word++;
			if (j == (int)ft_strlen(word))
				return (line);
		}
		line++;
	}
	return (NULL);
}

static char 		*door_or_sky(char *line, t_sector *current)
{
	current->type = simple;
	current->state = calm;
	if (ft_strncmp(line, "door", ft_strlen("door")) == 0)
	{
		current->type = door;
		return (skip_line_with_word(line, "door"));
	}
	if (ft_strncmp(line, "uncovered", ft_strlen("uncovered")) == 0)
	{
		current->type = uncovered;
		return (skip_line_with_word(line, "uncovered"));
	}
	if (ft_strncmp(line, "lift", ft_strlen("lift")) == 0)
	{
		current->type = lift;
		return (skip_line_with_word(line, "lift"));
	}
	if (ft_strncmp(line, "murderous", ft_strlen("murderous")) == 0)
	{
		current->type = murderous;
		return (skip_line_with_word(line, "murderous"));
	}
	return (line);
}

static t_sector		*crate_and_fill_sector_by_data(
	t_read_holder *holder, char *data)
{
	t_sector		*sect;

	if (!data || !*data)
		return (print_error_message_null("", "Wrong line"));
	sect = new_sector();
	data = door_or_sky(data, sect);
	if (!(data = fill_floor_and_ceil(sect, holder->textures, data, holder->text_count)))
		return (error_free_t_sector(&sect, "Can't create sector!", "Error filling floor/ceil"));
	if ((data = skip_line_with_word(data, "walls")))
	{
		if ((sect->n_walls = get_wall_count(data)) < 3)
			return (error_free_t_sector(&sect, "Worng sector wall count : ", data));
		if (!(sect->wall = create_sector_walls(sect, holder, data, sect->n_walls)))
			return (error_free_t_sector(&sect, "Creating sector walls:", data));
	}
	else
		return (error_free_t_sector(&sect, "'walls'", "Didn't detected"));
	if ((data = skip_line_with_word(data, "items")))
		sect->items = make_items(data, holder->all_items, holder);
	else
		return (error_free_t_sector(&sect, "'items'", "Didn't detected"));
	return (sect);
}

t_sector			*make_sectors_list(int fd, t_read_holder *holder)
{
	char			*line;
	t_sector		*head;
	t_sector		*new;

	head = NULL;
	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, ""))
	{
		if (ft_isdigit(*line))
		{
			if ((new = crate_and_fill_sector_by_data(holder,
							skip_row_number(line))))
				add_next_sector(&head, new);
			else
			{
				ft_strdel(&line);
				return (error_free_t_sector(&head, "t_sector is ", "NULL"));
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	mark_all_neighbors(head, holder->walls);
	return (check_sectors(head) ? head : delete_sectors(head));
}
