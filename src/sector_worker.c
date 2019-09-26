#include "main_head.h"

t_sector			*new_sector()
{
	t_sector		*sec;
	int				i;

	i = 0;
	sec = (t_sector*)malloc(sizeof(t_sector));
	*sec = (t_sector){};
	printf("Created\n");
	return (sec);
}

t_sector			*crate_new_sector(float	floor, float ceil)
{
	t_sector		*sec;

	sec = new_sector();
	sec->floor = floor;
	sec->ceil = ceil;
	return (sec);
}

int					size_sector(t_sector *sec)
{
	int				i;
	t_sector		*s;

	s = sec;
	i = 0;
	while(s)
	{
		s = s->next;
		i++;
	}
	return (i);
}

void				add_next_sector(t_sector **main, t_sector *next)
{
	t_sector		*head;
	int				i;

	if (!*main)
	{
		*main = next;
		return ;
	}
	head = *main;
	i = 1;
	while (head->next)
	{
		head = head->next;
		i++;
	}
	next->sector = i;
	head->next = next;
}

void				delete_walls(t_wall **wall, unsigned size)
{
	int				i;
	t_wall			*ptr;
	
	if (!wall)
		return ;
	i = 0;
	while (i < size)
	{
		if (wall[i])
		{
			ptr = wall[i];
			ft_memdel((void**)&ptr);
			wall[i] = NULL;
		}
		i++;
	}
	ft_memdel((void**)&wall);
}

void				delete_sectors(t_sector *sectors)
{
	t_sector		*next;
	unsigned		i;
	t_light			*light;

	if (!sectors)
		return ;
	next = sectors;
	while(sectors)
	{
		next = sectors;
		sectors = next->next;
		delete_walls(next->wall, next->n_walls);
		delete_items_list(next->items);
		delete_projectiles(next->projectiles);
		ft_memdel((void**)&next);
		printf("Destroyed\n");
	}
}

void				list_walls(t_wall **walls, int size)
{
	t_wall			*w;
	t_vector		line;
	int				i;

	i = 0;
	while (i < size)
	{
		w = walls[i];
		ft_putstr("\twall id ");
		ft_putnbr(walls[i]->id);
		ft_putstr(", type: ");
		ft_putstr(walls[i]->type == 0 ? "Wall" : walls[i]->type == 1 ? "Portal" : "Door");
		ft_putstr(". Neighbors:");
		if (walls[i]->sectors[0])
		{
			ft_putstr(" sect# ");
			ft_putnbr(walls[i]->sectors[0]->sector);
		}
		if (walls[i]->sectors[1])
		{
			ft_putstr(", and  ");
			ft_putnbr(walls[i]->sectors[1]->sector);
		}
		line = w->start;
		ft_putstr("texture size ");
		ft_putnbr(w->texture->w);
		ft_putstr(" x ");
		ft_putnbr(w->texture->h);
		ft_putstr("\n\t start: x = ");
		ft_putnbr(line.x);
		ft_putstr(", y = ");
		ft_putnbr(line.y);
		line = w->end;
		ft_putstr(";\n\t end:   x = ");
		ft_putnbr(line.x);
		ft_putstr(", y = ");
		ft_putnbr(line.y);
		write(1, ".\n", 2);
		
		i++;
	}
}

void 				list_light(t_light	**arr, unsigned arr_size)
{
	int				i;

	i = 0;
	while (i < arr_size && arr[i])
	{
		printf("%d pos %f x %f, radius %f\n", i, arr[i]->pos.x, arr[i]->pos.y, arr[i]->max_dist);
		i++;
	}
}

void				list_sectors(t_sector *head)
{
	t_sector		*s;
	int				i;

	if (!head)
		return ;
	i = 0;
	s = head;
	while (s)
	{
		ft_putstr("Sector # ");
		ft_putnbr(i);
		ft_putstr("\ncount walls: ");
		ft_putnbr(s->n_walls);
		ft_putstr("\nfloor height: ");
		ft_putnbr(s->floor);
		ft_putstr(", text ");
		ft_putnbr(s->floor_tex->w);
		ft_putstr(" x ");
		ft_putnbr(s->floor_tex->h);
		ft_putstr("; ceil height: ");
		ft_putnbr(s->ceil);ft_putstr(", text ");
		ft_putnbr(s->ceil_tex->w);
		ft_putstr(" x ");
		ft_putnbr(s->ceil_tex->h);
		write(1, "\n", 1);
		list_walls(s->wall, s->n_walls);
		list_items(s->items);
		write(1,"\n", 1);
		list_light(s->sector_light, MAX_LIGHT_SRC);
		write(1, "\n", 1);
		i++;
		s = s->next;
	}
}
