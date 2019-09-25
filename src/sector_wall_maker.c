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

	dst = (t_wall*)malloc(sizeof(t_wall));;
	if (!dst || !src)
		return (NULL);
	dst->id = src->id;
	dst->type = src->type;
	dst->start = src->start;
	dst->end = src->end;
	dst->close = src->close;
	dst->sectors[0] = src->sectors[0];
	dst->sectors[1] = src->sectors[1];
	dst->texture = src->texture;
	return (dst);
}

t_wall			**create_sector_walls(t_sector *sector, t_read_holder *holder, char *data, int wall_count)
{	t_wall		**walls;
	int			id;
	int			count;
	int			i;

	walls = (t_wall**)malloc(sizeof(t_wall*) * wall_count);
	count = 0;
	while (count < wall_count && data[i] &&  data[i] != '\'')
	{
		if (ft_isdigit(data[i]) && ft_atoi(&data[i]) >= 0)
		{
			id = ft_atoi(&data[i]);
			if (id >= 0 && id < holder->wall_count)
			{
				mark_like_neighbors(sector, holder->walls[id]);
				walls[count] = copy_t_wall_velue(holder->walls[id]);
			}
			while (data[i] && data[i] != ' ' && data[i] != '\'')
				i++;
			count++;
		}
		else
			i++;
	}
	return (walls);
}