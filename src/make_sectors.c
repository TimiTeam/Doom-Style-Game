#include "sectors.h"

int				get_num_from_str(char *str)
{
	int			i;
	
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (ft_atoi(&str[i]));
		i++;
	}
	return (0);
}

void			get_count_vectors_and_walls(int fd, int *co_vec, int *co_wall)
{
	char		*vec;
	char		*wall;

	vec = NULL;
	wall = NULL;
	get_next_line(fd, &vec);
	get_next_line(fd, &wall);

	*co_vec = get_num_from_str(vec);
	*co_wall = get_num_from_str(wall);

	ft_strdel(&vec);
	ft_strdel(&wall);
}

int 			get_data(float *x, float *y, float *z, char *data)
{
	int			i;
	char		*num;

	if (!data || !*data)
		return (0);
	i = 0;
	while (data[i] && data[i] != ' ')
		i++;
	if (++i < ft_strlen(data))
	{
		*x = (float)ft_atoi(&data[i]);
		num = ft_itoa((int)*x);
		i += ft_strlen(num);
		i++;
		ft_strdel(&num);
		if (i < ft_strlen(data))
			*y = (float)ft_atoi(&data[i]);
		num = ft_itoa((int)*y);
		i += ft_strlen(num);
		ft_strdel(&num);
		if (data[i] && ft_isdigit(data[i + 1]) && z)
		{
			*z = (float)ft_atoi(&data[i]);
			num = ft_itoa((int)*z);
			i += ft_strlen(num);
			ft_strdel(&num);
		}
	}
	return (i);
}

t_vector		*get_vectors(int fd, int vec_size)
{
	int			i;
	char		*line;
	t_vector	*vectors;
	t_vector	*ret;

	vectors = (t_vector*)malloc(sizeof(t_vector) * vec_size);
	ret = vectors;
	i = 0;
	while (get_next_line(fd, &line) > 0 && i < vec_size)
	{
		if (ft_strcmp(line, "Walls:") == 0)
			break ;
		if (ft_isdigit(line[0]))
		{
			get_data(&vectors[i].x, &vectors[i].y, &vectors[i].z, line);
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return	(ret);
}

void				list_vectors(t_vector *vec, unsigned size)
{
	int				i;

	i = 0;
	if (!vec)
		return ;
	while (i < size)
	{
		printf("vector # %d: x = %f, y = %f;\n", i, vec[i].x, vec[i].y);
		i++;
	}
}

void			list_and_dell_walls(t_wall **walls, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		printf("Wall # %d: type = %d;\n", i, walls[i]->type);
		list_vectors(&walls[i]->start, 1);
		list_vectors(&walls[i]->end, 1);
		ft_memdel((void**)&walls[i]);
		i++;
	}
	ft_memdel((void**)&walls);
}

t_wall			**get_walls(int fd, int wall_size, t_vector *vectors)
{
	char		*line;
	SDL_Surface	*texture;
	int			i;
	int			j;
	float		start;
	float		end;
	t_wall		**walls;

	i = 0;
	walls = (t_wall**)malloc(sizeof(t_wall*) * wall_size);
	texture = load_img("textures/image.jpeg");
	while (get_next_line(fd, &line) > 0 && i < wall_size)
	{
		if (ft_strcmp(line,"") == 0)
			break ;
		if (ft_isdigit(line[0]))
		{
			walls[i] = (t_wall*)malloc(sizeof(t_wall));
			*walls[i] = (t_wall){};
			j = get_data(&start, &end, NULL, line);
			walls[i]->start = vectors[(int)start - 1];
			walls[i]->end = vectors[(int)end - 1];
			walls[i]->type = ft_strcmp(&line[j], " filled") == 0 ? fieled_wall : empty_wall;
			walls[i]->texture = walls[i]->type != empty_wall ? texture : NULL;
			walls[i]->id = i;
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (walls);
}

int				get_wall_count(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = i;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			count++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
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
	dst->sectors[0] = src->sectors[0];
	dst->sectors[1] = src->sectors[1];
	dst->texture = src->texture;
	return (dst);
}

t_sector		*crate_and_fill_sector_by_data(t_wall **walls, char *data)
{
	t_sector	*sect;
	t_wall		*wall;
	char		*dec;
	int			count;
	int			port;
	int			i;
	float		f;
	float		c;

	port = 0;
	i = get_data(&f, &c, NULL, data);
	sect = crate_new_sector(f, c);
	sect->n_walls = get_wall_count(&data[i]);
	count = 0;
	sect->wall = (t_wall**)malloc(sizeof(t_wall*) * sect->n_walls);
	while (count < sect->n_walls && data[i])
	{
		if (ft_isdigit(data[i]) && ft_atoi(&data[i]) >= 0)
		{
			wall = walls[ft_atoi(&data[i]) - 1];
			mark_like_neighbors(sect, wall);
			sect->wall[count] = copy_t_wall_velue(wall);
			if (sect->wall[count]->type == empty_wall)
				sect->portals[port++] = count;
			dec = ft_itoa(ft_atoi(&data[i]));
			i += ft_strlen(dec);
			count++;
			ft_strdel(&dec);
		}
		else
			i++;
	}
	return (sect);
}

t_sector		*make_sectors_list(int fd, t_wall **walls)
{
	char		*line;
	t_sector	*head;
	t_sector	*new;

	get_next_line(fd, &line);
	if (ft_strcmp(line , "Sectors:") == 0)
	{
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	head = crate_and_fill_sector_by_data(walls, line);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		new = crate_and_fill_sector_by_data(walls, line);
		ft_strdel(&line);
		add_next_sector(&head, new);
	}
	ft_strdel(&line);
	return (head);
}


void			mark_all_neighbors(t_sector *sectors, t_wall **all)
{
	t_sector	*sec;
	t_wall		*wall;
	t_vector	tmp;
	SDL_Surface		*floor_tex;
	SDL_Surface		*ceil_tex;
	int			i;
	int			p;

	floor_tex = load_img("textures/floor2.jpg");
	ceil_tex = load_img("textures/ceil.jpeg");
	sec = sectors;
	while (sec)
	{
		i = 0;
		p = 0;
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
				sec->portals[p++] = i;
			i++;
		}
		sec->floor_tex = floor_tex;
		sec->ceil_tex = ceil_tex;
		sec = sec->next;
	}
}

t_sector		*read_map(char *pth)
{
	int			fd;
	int			vect_count;
	int			wall_count;
	t_sector	*sectors;
	t_vector	*vectors;
	t_wall		**walls;

	if (!(fd = open(pth, O_RDONLY)))
		return (NULL);
	get_count_vectors_and_walls(fd, &vect_count, &wall_count);
	vectors = get_vectors(fd, vect_count);
	walls = get_walls(fd, wall_count, vectors);
	ft_memdel((void**)&vectors);
	sectors = make_sectors_list(fd, walls);
	mark_all_neighbors(sectors, walls);
	delete_walls(walls, wall_count);
	return (sectors);
}
