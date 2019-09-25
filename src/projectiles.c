#include "sdl_head.h"
#include "main_head.h"

t_projectile			*create_projectile(t_player player)
{
	t_projectile 	*projectile;
	
	if(!(projectile = (t_projectile*)ft_memalloc(sizeof(t_projectile))))
		return (NULL);
	*projectile = (t_projectile){};
	projectile->pos.x = player.pos.x + 1 * player.cos_angl;
	projectile->pos.y = player.pos.y + 1 * player.sin_angl;
	projectile->pos.z = player.pos.z - player.yaw - 3;
	projectile->anglecos = player.cos_angl;
	projectile->anglesin = player.sin_angl;
	projectile->yaw = player.yaw;
	projectile->curr_sector = player.curr_sector;
	projectile->speed = 3.0f;
	projectile->damage = 20;
	projectile->sprite = load_jpg_png("textures/plasma_raw.png");
	return (projectile);
}

void 				add_projectile(t_projectile **head, t_projectile *new)
{
	t_projectile			*main;

	if (!*head)
	{
		*head = new;
		return ;
	}
	main = *head;
	while (main->next)
		main = main->next;
	main->next = new;
}


void 					swap_proj_sectors(t_projectile **current_list, t_projectile **next_list, t_projectile *elem)
{
	t_projectile		*curr;
	t_projectile		*prev;

	if (*current_list == elem)
	{
		*current_list = elem->next;
		elem->next = NULL;
		add_projectile(next_list, elem);
		return ;
	}
	curr = (*current_list)->next;
	prev = *current_list;
	while(curr)
	{
		if (curr == elem)
		{
			prev->next = elem->next;
			elem->next = NULL;
			add_projectile(next_list, elem);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void 				free_proj(t_projectile *proj)
{
	if (!proj)
		return ;
	SDL_FreeSurface(proj->sprite);	
	free(proj);
}


void				delete_projectiles(t_projectile *head)
{
	t_projectile *tmp;

	while (head)
	{
		tmp = head->next;
		free_proj(head);
		head = tmp;
	}
}

void				delete_projectile(t_projectile **head, t_projectile *proj)
{
	t_projectile	*curr;
	t_projectile	*prev;
	
	
	if (!(*head) || !proj || !head)
		return ;
	curr = (*head)->next;
	prev = *head;
	if (proj == *head)
	{
		*head = proj->next;
		free_proj(proj);
		return ;
	}
	while(curr)
	{
		if (proj == curr)
		{
			prev->next = curr->next;
			free_proj(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

Uint8						move_projectile(t_projectile *proj)
{		
	t_wall				**wall;
	int					i;
	t_sector			*sector;
	t_sector			*next;
	t_vector			step;

	//printf("Moved\n");
	if (!proj)
		return (0);
	step = (t_vector){proj->pos.x + proj->speed * proj->anglecos, proj->pos.y + proj->speed * proj->anglesin, proj->pos.z - proj->yaw * proj->speed};
	sector = proj->curr_sector;
	wall = sector->wall;
	i = 0;
	while (i < sector->n_walls)
	{
		if(IntersectBox(proj->pos.x, proj->pos.y, step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y)
        && PointSide(step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y) < 0)
        {
			if (wall[i]->type != empty_wall)
				return (0);
			if (wall[i]->sectors[0] && sector->sector != wall[i]->sectors[0]->sector)
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1] && sector->sector != wall[i]->sectors[1]->sector)
				next = wall[i]->sectors[1];
			swap_proj_sectors(&proj->curr_sector->projectiles, &next->projectiles, proj);
			proj->curr_sector = next;
			break;
        }
		i++;
	}
	proj->pos = step;
	return (1);
}