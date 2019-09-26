#include "sectors.h"

static unsigned	fill_floor_and_ceil(t_sector *sector, SDL_Surface **textures, char *line)
{
	unsigned	i;
	float		height;
	float		text;

	if (!sector || !line || !textures)
		return (0);
	i = get_numbers(&height, &text, ' ', line);
	sector->floor = height;
	sector->floor_tex = textures[(int)text];
	i += get_numbers(&height, &text, ' ', &line[i]);
	sector->ceil = height;
	sector->ceil_tex = textures[(int)text];
	return (i);
}

t_sector		*crate_and_fill_sector_by_data(t_read_holder *holder, char *data)
{
	t_sector	*sect;
	t_wall		*wall;
	int			i;

	sect = new_sector();
	sect->door = ft_strncmp(data, "Door", ft_strlen("Door")) == 0 ? 1 : 0;
	i = fill_floor_and_ceil(sect, holder->textures, data);
	while (data[i] && data[i] != '\'' && data[i + 1])
		i++;
	sect->n_walls = get_wall_count(&data[++i]);
	sect->wall = create_sector_walls(sect, holder, &data[i], sect->n_walls);
	while (data[i] && !ft_isalpha(data[i]))
		i++;
	if (ft_strncmp(&data[i], "items", ft_strlen("items")) == 0)
		sect->items = make_items(&data[i], holder->all_items, holder);
	return (sect);
}

void 			set_sector_ptr_to_items(t_item *items, t_sector *sector)
{
	t_item		*all;

	all = items;
	while (all)
	{
		all->sector = sector;
		all = all->next;
	}
}

void			mark_all_neighbors(t_sector *sec, t_wall **all)
{
	t_wall		*wall;
	t_vector	tmp;
	int			i;
	int			p;
	int 		w;

	while (sec)
	{
		i = 0;
		p = 0;
		w = 0;
		while (i < sec->n_walls)
		{
			wall = all[sec->wall[i]->id];
			if (wall->sectors[0]->sector != sec->sector)
			{
				tmp = sec->wall[i]->start;
				sec->wall[i]->start = sec->wall[i]->end;
				sec->wall[i]->end = tmp;
			}
			sec->wall[i]->sectors[0] = wall->sectors[0];
			sec->wall[i]->sectors[1] = wall->sectors[1];
			if (sec->wall[i]->type == empty_wall && p < MAX_PORTALS)
				sec->portals[p++] = sec->wall[i];
			else if (sec->wall[i]->type == filled_wall && w < MAX_PORTALS)
				sec->only_walls[w++] = sec->wall[i];
			i++;
		}
		set_sector_ptr_to_items(sec->items, sec);
		sec = sec->next;
	}
}

t_sector			*make_sectors_list(int fd, t_read_holder *holder)
{
	char		*line;
	t_sector	*head;
	t_sector	*new;

	head = NULL;
	while (get_next_line(fd, &line) > 0 && *line != '\0' && *line != '\n')
	{
		if (ft_isdigit(line[0]))
		{
			new = crate_and_fill_sector_by_data(holder, skip_row_number(line));
			add_next_sector(&head, new);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	mark_all_neighbors(head, holder->walls);
	return (head);
}