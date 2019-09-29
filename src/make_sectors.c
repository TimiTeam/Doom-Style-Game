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

static unsigned		fill_floor_and_ceil(t_sector *sector,
		SDL_Surface **textures, char *line, int max_tex)
{
	unsigned		i;
	float			height;
	float			text;

	if (!sector || !line || !textures)
		return (0);
	i = get_numbers(&height, &text, ' ', line);
	sector->floor = height;
	if (text > max_tex)
		text = print_error_message("Use default val 0! Wrong item:", &line[i]);
	sector->floor_tex = textures[(int)text];
	i += get_numbers(&height, &text, ' ', &line[i]);
	sector->ceil = height;
	if (sector->ceil < sector->floor)
		sector->ceil = sector->floor;
	if (sector->floor == sector->ceil)
		sector->ceil += 0.2;
	if (text > max_tex)
		text = print_error_message("Use default val 0! Wrong item:", &line[i]);
	sector->ceil = sector->ceil < 1000 ? sector->ceil : 1000;
	sector->floor = sector->floor < 1000 ? sector->floor : 1000;
	sector->ceil_tex = textures[(int)text];
	return (i);
}

static t_sector		*crate_and_fill_sector_by_data(
	t_read_holder *holder, char *data)
{
	t_sector		*sect;
	t_wall			*wall;
	int				i;

	sect = new_sector();
	sect->door = ft_strncmp(data, "door", ft_strlen("door")) == 0 ? 1 : 0;
	i = fill_floor_and_ceil(sect, holder->textures, data, holder->text_count);
	while (data[i] && ft_strncmp(&data[i], "items",
				ft_strlen("items")) && data[i + 1])
	{
		if (ft_strncmp(&data[i], "walls", ft_strlen("walls")) == 0)
		{
			sect->n_walls = get_wall_count(&data[++i]);
			sect->wall = create_sector_walls(sect, holder,
					&data[i], sect->n_walls);
		}
		i++;
	}
	while (data[i] && ft_strncmp(&data[i], "items", ft_strlen("items")))
		i++;
	if (ft_strncmp(&data[i], "items", ft_strlen("items")) == 0)
		sect->items = make_items(&data[i], holder->all_items, holder);
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
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	mark_all_neighbors(head, holder->walls);
	return (check_sectors(head) ? head : delete_sectors(head));
}
