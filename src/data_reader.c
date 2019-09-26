#include "sectors.h"

char			*get_path(int fd)
{
	char		*pth;
	char		*line;
	int			skip_len;

	pth = NULL;
	skip_len = ft_strlen("Path: ");
	if (get_next_line(fd, &line) > 0 && ft_strncmp(line, "Path: ", skip_len) == 0)
	{
		pth = ft_strsub(line, skip_len, ft_strlen(line) - skip_len);
		if (!*pth)
			ft_strdel(&pth);
	}
	ft_strdel(&line);
	return (pth);
}

void 			read_maps_path(int fd, char **array, int arr_size)
{
	char		*file_name;
	char		*path;
	char		*full_path;
	int			i;

	i = 0;
	file_name = NULL;
	if(!(path = get_path(fd)))
		return ;
	while (get_next_line(fd, &file_name) > 0 && i < arr_size)
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			array[i] = ft_strdup(full_path);
			ft_strdel(&full_path);
		}
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		ft_strdel(&file_name);
		i++;
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
}


SDL_Surface		**load_img_array_from_file(int fd, unsigned size)
{
	SDL_Surface	**array;
	char		*file_name;
	char		*full_path;
	char		*path;
	int			i;

	if (!(path = get_path(fd)))
		return (NULL);
	array = (SDL_Surface**)malloc(sizeof(SDL_Surface**) * size);
	i = 0;
	while (get_next_line(fd, &file_name) > 0 && i < size)
	{
		if (ft_isdigit(*file_name))
		{
			full_path = clip_n_str(path, skip_row_number(file_name), "");
			array[i] = load_jpg_png(full_path);
			ft_strdel(&full_path);
		}
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		ft_strdel(&file_name);
		i++;
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (array);
}


t_item			*read_all_items(int fd)
{
	char		*file_name;
	char		*path;
	t_item		*main;
	t_item		*new;

	file_name = NULL;
	main = NULL;
	if(!(path = get_path(fd)))
		return (NULL);
	while (get_next_line(fd, &file_name) > 0)
	{
		if (ft_isdigit(*file_name))
			new = make_item_ftom_str(skip_row_number(file_name), path);
		else if (ft_strcmp(file_name, "###") == 0)
			break ;
		add_next_item(&main, new);
		ft_strdel(&file_name);
	}
	ft_strdel(&path);
	ft_strdel(&file_name);
	return (main);
}

int 			read_game_config_file(t_read_holder *holder, char *info_file_path)
{
	char		*line;
	int			fd;

	line = NULL;
	if (holder && (fd = open(info_file_path, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strcmp(line, "#Levels") == 0)
				read_maps_path(fd, &holder->maps_path[0], 5);
			else if (ft_strncmp(line, "#Textures", ft_strlen("#Textures")) == 0)
				holder->textures = load_img_array_from_file(fd, (holder->text_count = get_num_from_str(line)));
			else if (ft_strcmp(line, "#Items") == 0)
				holder->all_items = read_all_items(fd);
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		return (1);
	}
	return (0);
}

void 			get_player_pos(int fd, t_vector *player_pos, int *player_sec_id)
{
	char 		*line;
	char		*skiped;
	int			i;
	unsigned	p;

	line = NULL;
	i = 0;
	while(get_next_line(fd, &line) > 0)
	{
		if (i == 1)
		{
			p = get_numbers(&player_pos->x, &player_pos->y, ',', (skiped = skip_row_number(line)));
			*player_sec_id = get_num_from_str(&skiped[p]);
			break ;
		}
		else if (ft_strcmp(line, "Player") == 0)
			i = 1;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

t_light			*new_t_light(t_vector pos, float max_dist, t_sector *cur_sec)
{
	t_light		*new;

	new = NULL;
	if((new = (t_light*)malloc(sizeof(t_light))))
	{
		*new = (t_light){};
		new->pos = pos;
		new->max_dist = max_dist;
		new->sector = cur_sec;
	}
	return (new);
}


t_light			**create_all_light_source(t_sector *sec, unsigned light_count)
{
	t_light		**light_source;
	t_item		*items;
	t_sector	*sectors;
	unsigned	i;

	sectors = sec;
	if(light_count < 1 || !sectors ||
		!(light_source = (t_light**)malloc(sizeof(t_light*) * light_count)))
		return (NULL);
	i = 0;
	while(sectors)
	{
		items = sectors->items;
		while(items)
		{
			if (items->type == light && i < light_count)
			{
				light_source[i] = new_t_light(items->pos, 8, items->sector);
				i++;
			}
			items = items->next;
		}
		sectors = sectors->next;
	}
	return (light_source);
}

int				light_catch_sector(t_wall **walls, unsigned arr_size, t_vector light_pos, float max_dist)
{
	int 		i;
	t_wall		*w;

	i = 0;
	while(i < arr_size && (w = walls[i]))
	{
		if (find_dot_radius_intersect(light_pos, max_dist, w->start, w->end))
			return (1);
		i++;
	}
	return (0);
}

void 			fill_sectors_light_source(t_sector *sec, t_light **light, unsigned array_size)
{
	unsigned	i;
	unsigned	j;
	t_light		*source;
	t_sector	*sectors;

	sectors = sec;
	while(sectors)
	{
		i = 0;
		j = 0;
		while(i < array_size && (source = light[i]))
		{
			if (j < MAX_LIGHT_SRC && (source->sector == sectors || light_catch_sector(sectors->portals, MAX_PORTALS, source->pos, source->max_dist / 2)))
			{/*
				if(IntersectBox(player->pos.x, player->pos.y, step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y)
       			&& PointSide(step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y) < 0)*/
				sectors->sector_light[j] = source;
				j++;
			}
			i++;
		}
		sectors = sectors->next;
	}
}

void 			delete_light_source(t_light **light, unsigned array_size)
{
	t_light		*l;
	unsigned	i;

	i = 0;
	while (i < array_size && (l = light[i]))
	{
		ft_memdel((void**)&l);
		i++;
	}
	ft_memdel((void**)&light);
}

t_sector		*read_map(char *pth, t_read_holder *holder, t_vector *player_pos)
{
	t_sector	*sectors;
	t_vector	*vectors;
	t_light		**light_source;
	int 		fd;

	if ((fd = open(pth, O_RDONLY)) < 0)
	{
		printf("Error opening file: %s\n", pth);
		return (NULL);
	}
	light_source = NULL;
	get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count);
	vectors = get_vectors(fd, holder->vect_count);
	holder->walls = get_walls(fd, holder->wall_count, vectors, holder->textures);
	ft_memdel((void**)&vectors);
	sectors = make_sectors_list(fd, holder);
	list_sectors(sectors);

	light_source = create_all_light_source(sectors, holder->light_count);

	holder->light_source = light_source;

	fill_sectors_light_source(sectors, holder->light_source, holder->light_count);

	get_player_pos(fd, &holder->player_pos, &holder->player_sector_id);

	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (sectors);
}