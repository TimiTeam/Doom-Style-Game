#include "sectors.h"


t_vector		*get_vectors(int fd, int vec_size)
{
	int			i;
	char		*line;
	t_vector	*vectors;

	vectors = (t_vector*)malloc(sizeof(t_vector) * vec_size);
	i = 0;
	while (get_next_line(fd, &line) > 0 && i < vec_size && ft_strcmp(line, ""))
	{
		if (ft_isdigit(line[0]))
		{
			get_numbers(&vectors[i].x, &vectors[i].y, ',' , skip_row_number(line));
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (i != vec_size)
	{
		ft_memdel((void**)&vectors);
		vectors = NULL;
		print_error_message("Wrong count of vectors","");
	}
	return (vectors);
}

static t_wall	*make_wall(char *line, t_vector *vectors,t_read_holder *holder)
{
	t_wall		*ret;
	int			i;
	int			text;
	float		start;
	float		end;

	if (!line || !vectors || !holder->textures)
		return (NULL);
	ret = (t_wall*)malloc(sizeof(t_wall));
	*ret = (t_wall){};
	i = get_numbers(&start, &end, '-', line);
	if (start > holder->vect_count || end > holder->vect_count)
	{
		ft_memdel((void**)&ret);
		return (print_error_message_null("Vectors not exist ", line));
	}
	ret->start = vectors[(int)start];
	ret->end =  vectors[(int)end];
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "empty", ft_strlen("empty")))
		ret->type = empty_wall;
	else
  		ret->type = filled_wall;
	if ((text = get_num_from_str(&line[i])) > holder->text_count || text < 0)
	{
		ft_memdel((void**)&ret);
		return (print_error_message_null("Wrong index of texture ", &line[i]));
	}
	ret->texture = holder->textures[text];
	return (ret);
}

t_wall			**get_walls(int fd, t_read_holder *hodle, t_vector *vectors)
{
	char		*line;
	int			i;
	t_wall		**walls;

	i = 0;
	walls = (t_wall**)malloc(sizeof(t_wall*) * hodle->wall_count);
	while (get_next_line(fd, &line) > 0 && i < hodle->wall_count && ft_strcmp(line,""))
	{
		if (ft_isdigit(*line))
		{
			if (!(walls[i] = make_wall(skip_row_number(line), vectors, hodle)))
			{
				walls = delete_walls(walls, i);;
				break ;
			}
			walls[i]->id = i;
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (i != hodle->wall_count)
	{
		walls = delete_walls(walls, i);
		print_error_message("Wrond count of the walls","");
	}
	return (walls);
}