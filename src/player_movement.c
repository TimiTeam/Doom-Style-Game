#include "main_head.h"

void			move_player_vertically(t_player *player)
{
	if (player->pos.z + player->velocity >= player->curr_sector->ceil)
		player->velocity = 0;
	player->pos.z += player->velocity;
	if (player->pos.z - player->height > player->curr_sector->floor)
		player->velocity -= 0.08;
	else
		player->velocity = 0;
}

int				change_player(t_sector *new, t_player *player,
								t_vector *step, t_sector *next)
{
	if (!new || (int)(new->ceil - new->floor) <=
					(int)(player->height + player->sit))
		return (0);
	if (next->floor - player->pos.z + player->height > 3)
		return (0);
	if (player->pos.z - player->height < next->floor)
		step->z += next->floor - player->curr_sector->floor;
	player->curr_sector = new;
	return (1);
}

int				check_next_sec(t_wall *wall, t_player *player, t_sector **next)
{
	if (wall->type == filled_wall)
		return (0);
	if (wall->sectors[0] && player->curr_sector != wall->sectors[0])
		*next = wall->sectors[0];
	else if (wall->sectors[1] && player->curr_sector != wall->sectors[1])
		*next = wall->sectors[1];
	if (!*next || (int)((*next)->ceil - (*next)->floor) <=
								(int)(player->height + player->sit))
		return (0);
	return (1);
}

void			move_player(t_player *player, float sin_angle, float cos_angle)
{
	int			i;
	t_vector	step;
	t_wall		**wall;
	t_sector	*next;
	t_sector	*new;

	i = -1;
	step = (t_vector){player->pos.x + cos_angle * player->speed,
					player->pos.y + sin_angle * player->speed, 0};
	wall = player->curr_sector->wall;
	while (++i < player->curr_sector->n_walls)
	{
		if (box_intersection(player->pos, step, wall[i]->start, wall[i]->end)
		&& side_of_a_point(step, wall[i]->start, wall[i]->end) < 0)
		{
			if (!check_next_sec(wall[i], player, &next))
				return ;
			new = get_new_player_sector(step, next);
			if (!change_player(new, player, &step, next))
				return ;
			break ;
		}
	}
	step.z += player->pos.z;
	player->pos = step;
}
