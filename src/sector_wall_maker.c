/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_maker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:01:55 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 05:05:14 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

int				get_wall_count(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = i;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (0);
	i++;
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

static void		mark_like_neighbors(t_sector *who, t_wall *where)
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

int				skip_to_word(char *data, char *to_word)
{
	int			i;

	i = 0;
	while (data[i] && ft_strncmp(&data[i], to_word,
				ft_strlen(to_word)) && !ft_isdigit(data[i]))
		i++;
	return (i);
}

t_wall			**create_sector_walls(t_sector *sector,
		t_read_holder *holder, char *data, int wall_count)
{
	t_wall		**walls;
	int			id;
	int			count;
	int			i;

	if (wall_count < 1 || !(walls = malloc(sizeof(t_wall*) * wall_count)))
		return (NULL);
	count = 0;
	i = skip_to_word(data, "items");
	while (count < wall_count && data[i] &&
				ft_strncmp(&data[i], "items", ft_strlen("items")))
	{
		if (ft_isdigit(data[i]) && (id = ft_atoi(&data[i])) >= 0
				&& id < holder->wall_count)
		{
			mark_like_neighbors(sector, holder->walls[id]);
			walls[count] = copy_t_wall_velue(holder->walls[id]);
			count++;
			while (data[i] && ft_isdigit(data[i]))
				i++;
		}
		else
			i++;
	}
	return (walls);
}
