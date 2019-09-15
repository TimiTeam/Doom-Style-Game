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


char			*skip_row_number(char *line)
{
	unsigned	p;

	p = 0;
	while (line[p] && line[p + 1])
	{
		if (line[p] == ')' && line[p + 1] == ' ')
		{
			while(line[++p] && line[p] == ' ')
				;
			return (&line[p]);
		}
		p++;
	}
	return(NULL);
}

static void			get_count_struct_arrays(int fd, int *vect_count, int *wall_count, int *text_count)
{
	char			*vec;
	char			*wall;
	char			*tex;

	vec = NULL;
	wall = NULL;
	tex = NULL; 
	get_next_line(fd, &vec);
	get_next_line(fd, &wall);
	get_next_line(fd, &tex);
	*vect_count = get_num_from_str(vec);
	*wall_count = get_num_from_str(wall);
	*text_count = get_num_from_str(tex);
	ft_strdel(&vec);
	ft_strdel(&wall);
	ft_strdel(&tex);
}

static unsigned	get_numbers(float *one, float *two, char dilimeter, char *line)
{
	unsigned	i;
	int			nb;
	char		*num;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	nb = (float)ft_atoi(&line[i]);
	num = ft_itoa(nb);
	i += ft_strlen(num);
	*one = nb;
	if (line[i] && line[i] == dilimeter)
		i++;
	ft_strdel(&num);
	nb = (float)ft_atoi(&line[i]);
	num = ft_itoa(nb);
	i += ft_strlen(num);
	*two = nb;
	ft_strdel(&num);
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
			get_numbers(&vectors[i].x, &vectors[i].y, ',' , skip_row_number(line));
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

t_wall			*make_wall(char *line, t_vector *vectors, SDL_Surface **textures)
{
	t_wall		*ret;
	int			i;
	float		start;
	float		end;

	if (!line || !vectors || !textures)
		return (NULL);
	ret = (t_wall*)malloc(sizeof(t_wall));
	*ret = (t_wall){};
	i = get_numbers(&start, &end, '-', line);
	ret->start = vectors[(int)start - 1];
	ret->end =  vectors[(int)end - 1];
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "filled", 6))
		ret->type = filled_wall;
	else if (!ft_strncmp(&line[i], "door", 4))
  		ret->type = door;
	else
  		ret->type = empty_wall;
	ret->texture = textures[get_num_from_str(&line[i]) - 1];
	return (ret);
}

t_wall			**get_walls(int fd, int wall_size, t_vector *vectors, SDL_Surface **textures)
{
	char		*line;
	int			i;
	t_wall		**walls;

	i = 0;
	walls = (t_wall**)malloc(sizeof(t_wall*) * wall_size);
	while (get_next_line(fd, &line) > 0 && i < wall_size)
	{
		if (ft_strcmp(line,"") == 0)
			break ;
		if (ft_isdigit(line[0]))
		{
			walls[i] = make_wall(skip_row_number(line), vectors, textures);
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
	sector->floor_tex = textures[(int)text - 1];
	i += get_numbers(&height, &text, ' ', &line[i]);
	sector->ceil = height;
	sector->ceil_tex = textures[(int)text - 1];
	return (i);
}

char 			*clip_n_str(char *s1, char *s2, char *s3, int size_s2)
{
	int			i;
	int			size;
	char		*new;

	new = (char*)malloc(sizeof(char) * (size = ft_strlen(s1) + size_s2 + ft_strlen(s3) + 1));
	i = 0;
	ft_strcpy(new, s1);
	ft_strncpy(&new[ft_strlen(s1)], s2, size_s2);
	ft_strcpy(&new[ft_strlen(s1) + size_s2], s3);
	return (new);
}

void 			filed_t_animation(t_animation *anim, int fd)
{
	char		*line;
	int			i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "}") == 0)
			break ;
		anim->texture[i] = load_jpg_png(line);
		i++;
		ft_strdel(&line);
	}
	anim->current_text = 0;
	anim->max_textures = i;
	ft_strdel(&line);
}

void			create_animations(t_item *it, char *file_pth)
{
	int			fd;
	char		*line;

	fd = open(file_pth, O_RDONLY);
	if (fd < 1)
	{
		printf("ERROR reading file: %s", file_pth);
		exit(1);
	}
	while(get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "waiting{") == 0)
			filed_t_animation(&it->states[waiting], fd);
		else if (ft_strcmp(line, "walk{") == 0)
			filed_t_animation(&it->states[walk], fd);
		else if (ft_strcmp(line, "action{") == 0)
			filed_t_animation(&it->states[action], fd);
		else if (ft_strcmp(line, "taking_damage{") == 0)
			filed_t_animation(&it->states[taking_damage], fd);
		else if (ft_strcmp(line, "die{") == 0)
			filed_t_animation(&it->states[die], fd);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void 			load_animation(t_item *item, char *path_to_enemy)
{
	char		*new;
	int			i;
	int			j;
	int			size;

	i = 0;
	while (path_to_enemy[i] && path_to_enemy[i] == ' ')
		i++;
	j = i;
	size = 0;
	while (path_to_enemy[i] && ft_isalpha(path_to_enemy[i]) && size < 32)
	{
		size++;
		i++;
	}
	if (size)
	{
		new = clip_n_str("textures/", &path_to_enemy[j], "/info.txt", size);
		ft_putstr("'");
		ft_putstr(new);
		ft_putstr("'\n");
		create_animations(item, new);
		ft_memdel((void**)&new);
	}
}

t_item			*create_item(int *p, char *data, SDL_Surface **textures, enum item_type type)
{
	t_item 		*item;
	unsigned	i;
	float		x;
	float		y;

	i = get_numbers(&x, &y, ',', data);
	if(!(item = create_new_item((int)x, (int)y)))
		return (0);
	item->type = type;
	load_animation(item, &data[i]);
	item->size = item->type != enemy ? 900 : 2500;
	item->pos.z = item->type == enemy ? 5 : 2;
	item->dist_to_player = 10.f;
	while (data[i] && data[i] != ')')
	{
		if (ft_isalpha(data[i]))
			item->type = ft_strncmp(&data[i], "key", 3) == 0 ? key : item->type;
		i++;
	}
	if (item->type == enemy)
		printf("Enemy\n");
	*p = i;
	item->hp = 100;
	return (item);
}

enum item_type		get_item_type_from_str(char *data)
{
	int		i;
	const char	*enem;
	const char	*item;

	i = 0;
	enem = "enemies";
	item = "items";
	while (data[i])
	{
		if (ft_strncmp(&data[i], enem, ft_strlen(enem)) == 0)
			return (enemy);
		else if (ft_strncmp(&data[i], item, ft_strlen(item)) == 0)
			return (object);
		i++;
	}
	return (0);
}

t_item			*make_items(char *data, SDL_Surface **textures)
{
	t_item		*list;
	t_item		*next;
	enum item_type	type;
	int 		i;
	int			p;

	i = 0;
	list = NULL;
	type = get_item_type_from_str(data);
	while (data[i] && data[i] != '\'')
		i++;
	if (data[i] && data[++i] != '(')
		return (NULL);
	else if (data[i] == '(')
	{
		list = create_item(&p, &data[++i], textures, type);
		i += p;
	}
	while (list && data[i] && data[i] != 'e')
	{
		next = NULL;
		if (data[i] == '(')
		{
			next = create_item(&p, &data[i], textures, type);
			i += p;
			add_next_item(&list, next);
			continue ;
		}
		i++;
	}
	return (list);
}

t_sector		*crate_and_fill_sector_by_data(t_wall **walls, SDL_Surface	**textures, char *data)
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
	count = 0;
	sect->wall = (t_wall**)malloc(sizeof(t_wall*) * sect->n_walls);
	while (count < sect->n_walls && data[i] &&  data[i] != '\'')
	{
		if (ft_isdigit(data[i]) && ft_atoi(&data[i]) >= 0)
		{
			wall = walls[ft_atoi(&data[i]) - 1];
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
	printf("%s\n", &data[i]);
	if (!ft_strncmp(&data[i], "items", ft_strlen("items")))
		sect->items = make_items(&data[i], textures);

	while (data[i] && ft_strncmp(&data[i], "enemies", ft_strlen("enemies")))
		i++;
	sect->enemies = make_items(&data[i], textures);
	return (sect);
}

t_sector		*make_sectors_list(int fd, t_wall **walls, SDL_Surface **textures)
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
	head = crate_and_fill_sector_by_data(walls, textures, skip_row_number(line));
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		new = crate_and_fill_sector_by_data(walls, textures, skip_row_number(line));
		ft_strdel(&line);
		add_next_sector(&head, new);
	}
	ft_strdel(&line);
	return (head);
}

void 				finde_close_doors(t_wall **walls, unsigned short size)
{
	unsigned short	i;
	t_wall			*w;
	t_wall			*d;

	i = -1;
	while (++i < size)
	{
		w = walls[i];
		d = NULL;
		if (w->type != empty_wall)
			continue ;
		w->id_portal = NON;
		if (i > 0 && walls[i - 1]->type == door)
			d = walls[i - 1];
		else if (i < size - 1 && walls[i + 1]->type == door)
			d = walls[i + 1];
		if (d)
		{
			d->close = 1;
			d->id_portal = w->id;
			w->close = 1;
		}
	}
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
		finde_close_doors(sec->wall, sec->n_walls);
		set_sector_ptr_to_items(sec->enemies, sec);
		sec = sec->next;
	}
}


SDL_Surface		**load_img_array_from_file(int fd, unsigned size)
{
	SDL_Surface	**array;
	char		*pth;
	int			i;

	array = (SDL_Surface**)malloc(sizeof(SDL_Surface**) * size);
	i = 0;
	while (get_next_line(fd, &pth) > 0 && i < size)
	{
		if (!pth || !ft_isdigit(*pth))
		{
			ft_strdel(&pth);
			continue;
		}
		array[i] = load_jpg_png(skip_row_number(pth));
		ft_strdel(&pth);
		i++;
	}
	ft_strdel(&pth);
	return (array);
}

t_sector		*read_map(char *pth, t_read_holder *holder)
{
	t_sector	*sectors;
	t_vector	*vectors;

	if (!(holder->fd = open(pth, O_RDONLY)))
		return (NULL);
	get_count_struct_arrays(holder->fd, &holder->vect_count, &holder->wall_count, &holder->text_count);
	holder->textures = load_img_array_from_file(holder->fd, holder->text_count);
	vectors = get_vectors(holder->fd, holder->vect_count);
	holder->walls = get_walls(holder->fd, holder->wall_count, vectors, holder->textures);
	finde_close_doors(holder->walls, holder->wall_count);
	ft_memdel((void**)&vectors);
	sectors = make_sectors_list(holder->fd, holder->walls, holder->textures);
	mark_all_neighbors(sectors, holder->walls, holder->textures);
	close(holder->fd);
	return (sectors);
}
