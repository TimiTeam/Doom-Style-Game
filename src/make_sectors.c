#include "sectors.h"

int				get_wall_count(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = i;
	while (str[i] && str[i] != '\'')
	{
		if (ft_isdigit(str[i]))
		{
			count++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

void			mark_like_neighbors(t_sector *who, t_wall *where)
{
	if (!where)
	{
		ft_putendl("Wall is not exist");
		return ;
	}
	if (!where->sectors[0])
		where->sectors[0] = who;
	else if (!where->sectors[1])
		where->sectors[1] = who;
}

t_wall			*copy_t_wall_velue(t_wall *src)
{
	t_wall		*dst;

	dst = (t_wall*)malloc(sizeof(t_wall));;
	if (!dst || !src)
		return (NULL);
	dst->id = src->id;
	dst->type = src->type;
	dst->start = src->start;
	dst->end = src->end;
	dst->close = src->close;
	dst->id_portal = src->id_portal;
	dst->sectors[0] = src->sectors[0];
	dst->sectors[1] = src->sectors[1];
	dst->texture = src->texture;
	return (dst);
}

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


t_sector		*crate_and_fill_sector_by_data(t_wall **walls, SDL_Surface	**textures, char *data, t_item *all_items)
{
	t_sector	*sect;
	t_wall		*wall;
	char		*dec;
	int			count;
	int			i;

	sect = new_sector();
	i = fill_floor_and_ceil(sect, textures, data);
	while (data[i] && data[i] != '\'' && data[i + 1])
		i++;
	sect->n_walls = get_wall_count(&data[++i]);
	sect->wall = (t_wall**)malloc(sizeof(t_wall*) * sect->n_walls);
	count = 0;
	while (count < sect->n_walls && data[i] &&  data[i] != '\'')
	{
		if (ft_isdigit(data[i]) && ft_atoi(&data[i]) >= 0)
		{
			wall = walls[ft_atoi(&data[i])];
			mark_like_neighbors(sect, wall);
			sect->wall[count] = copy_t_wall_velue(wall);		
			dec = ft_itoa(ft_atoi(&data[i]));
			i += ft_strlen(dec);
			count++;
			ft_strdel(&dec);
		}
		else
			i++;
	}
	while (data[i] && (data[i] == ' ' || data[i] =='\''))
		i++;
	if (ft_strncmp(&data[i], "items", ft_strlen("items")) == 0)
		sect->items = make_items(&data[i], all_items);
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

void			mark_all_neighbors(t_sector *sectors, t_wall **all, SDL_Surface **textures)
{
	t_sector	*sec;
	t_wall		*wall;
	t_vector	tmp;
	int			i;
	int			p;
	int			d;
	
	sec = sectors;
	while (sec)
	{
		i = 0;
		p = 0;
		d = 0;
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
			else if (sec->wall[i]->type == door && d < MAX_PORTALS)
				sec->doors[d++] = sec->wall[i];
			i++;
		}
		set_sector_ptr_to_items(sec->items, sec);
		sec = sec->next;
	}
}

t_sector		*make_sectors_list(int fd, t_wall **walls, SDL_Surface **textures, t_item *all_items)
{
	char		*line;
	t_sector	*head;
	t_sector	*new;

	head = NULL;
	while (get_next_line(fd, &line) > 0 && *line != '\0' && *line != '\n')
	{
		if (ft_isdigit(line[0]))
		{
			new = crate_and_fill_sector_by_data(walls, textures, skip_row_number(line), all_items);
			add_next_sector(&head, new);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	mark_all_neighbors(head, walls, textures);
	return (head);
}