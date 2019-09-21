#include "sectors.h"


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

static t_wall	*make_wall(char *line, t_vector *vectors, SDL_Surface **textures)
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
	ret->start = vectors[(int)start];
	ret->end =  vectors[(int)end];
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "empty", ft_strlen("empty")))
		ret->type = empty_wall;
	else if (!ft_strncmp(&line[i], "door", ft_strlen("door")))
  		ret->type = door;
	else
  		ret->type = filled_wall;
	ret->texture = textures[get_num_from_str(&line[i])];
	return (ret);
}

void			finde_close_doors(t_wall **walls, unsigned short size)
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
		if (i > 0 && walls[i - 1]->type == door)
			d = walls[i - 1];
		else if (i < size - 1 && walls[i + 1]->type == door)
			d = walls[i + 1];
		if (d)
		{
			d->opening = 0;
			d->close = 1;
			d->portal_ptr = w;
			w->close = 1;
		}
	}
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