/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_maker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:01:55 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/30 14:33:20 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

static int		mark_like_neighbors(t_sector *who, t_wall *where)
{
	if (!where)
	{
		print_error_message("Wall is not exist", "");
		return (0);
	}
	if (!where->sectors[0])
		where->sectors[0] = who;
	else if (!where->sectors[1])
		where->sectors[1] = who;
	return (1);
}

static t_wall	*copy_t_wall_velue(t_wall *src)
{
	t_wall		*dst;

	dst = (t_wall*)malloc(sizeof(t_wall));
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

static void		*error_free_t_wall(t_wall **array, int count, char *line)
{
	if (array && *array)
		delete_walls(array, count);
	return (print_error_message_null("Creating wall at line: ", line));
}

t_wall			**create_sector_walls(t_sector *sector,
		t_read_holder *holder, char *data, int wall_c)
{
	t_wall		**walls;
	int			id;
	int			count;

	if (wall_c < 1 || !(walls = malloc(sizeof(t_wall*) * wall_c)))
		return (NULL);
	count = 0;
	while (*data && *data != '\'')
		data++;
	while (count < wall_c && *data && data++ && *data != '\'' &&
				ft_strncmp(data, "items", ft_strlen("items")))
	{
		if (ft_isdigit(*data) && (id = ft_atoi(data)) >= 0)
		{
			if (id > holder->wall_count ||
				!mark_like_neighbors(sector, holder->walls[id]))
				return (error_free_t_wall(walls, count, data));
			walls[count++] = copy_t_wall_velue(holder->walls[id]);
			while (*data && ft_isdigit(*data))
				data++;
		}
	}
	return (count == wall_c ? walls : delete_walls(walls, count));
}
