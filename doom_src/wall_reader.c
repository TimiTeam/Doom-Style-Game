/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:30:14 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 06:42:24 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

t_vector				*get_vectors(int fd, int vec_size)
{
	int					i;
	char				*line;
	t_vector			*vectors;

	vectors = (t_vector*)malloc(sizeof(t_vector) * vec_size);
	i = 0;
	while (vectors && get_next_line(fd, &line) > 0 && i < vec_size
		&& ft_strcmp(line, ""))
	{
		if (ft_isdigit(line[0]))
		{
			if (!get_numbers(&vectors[i].x, &vectors[i].y, ',',
					skip_row_number(line)))
				break ;
			i++;
		}
		ft_strdel(&line);
	}
	if (i != vec_size)
	{
		ft_memdel((void**)&vectors);
		print_error_message("Some error in creating vectors: ", line);
	}
	ft_strdel(&line);
	return (vectors);
}

static enum e_wall_type	get_wall_type(char *line)
{
	if (ft_strncmp(line, "empty", ft_strlen("empty")) == 0)
		return (empty_wall);
	if (ft_strncmp(line, "filled", ft_strlen("filled")) == 0)
		return (filled_wall);
	if (ft_strncmp(line, "transparent", ft_strlen("transparent")) == 0)
		return (transparent);
	if (ft_strncmp(line, "window", ft_strlen("window")) == 0)
		return (window);
	return (0);
}

static t_wall			*make_wall(char *line, t_vector *vectors,
									t_read_holder *h)
{
	t_wall				*ret;
	int					i;
	int					text;
	float				start;
	float				end;

	if (!line || !*line)
		return (print_error_message_null("Reading map", "exit"));
	i = get_numbers(&start, &end, '-', line);
	if (start > h->vect_count || end > h->vect_count || (!start && !end))
		return (print_error_message_null("Vectors not exist at line:", line));
	ret = (t_wall*)malloc(sizeof(t_wall));
	ft_memset(ret, 0, sizeof(t_wall));
	ret->start = vectors[(int)start];
	ret->end = vectors[(int)end];
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	ret->type = get_wall_type(&line[i]);
	if ((text = get_num_from_str(&line[i])) > h->text_count || text < 0)
	{
		ft_memdel((void**)&ret);
		return (print_error_message_null("Wrong index of texture ", &line[i]));
	}
	ret->texture = h->textures[text];
	return (ret);
}

t_wall					**get_walls(int fd, t_read_holder *h, t_vector *vectors)
{
	char				*line;
	int					i;
	t_wall				**walls;

	i = 0;
	walls = (t_wall**)malloc(sizeof(t_wall*) * h->wall_count);
	while (get_next_line(fd, &line) > 0 && i < h->wall_count &&
			ft_strcmp(line, ""))
	{
		if (ft_isdigit(*line))
		{
			if (!(walls[i] = make_wall(skip_row_number(line), vectors, h)))
			{
				walls = delete_walls(walls, i);
				break ;
			}
			walls[i]->id = i;
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (i == h->wall_count ? walls : delete_walls(walls, i));
}
