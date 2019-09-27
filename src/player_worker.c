#include "main_head.h"

void				free_player(t_player *player)
{
	int				i;
	if (!player)
		return ;
	delete_items_list(player->inventar);
	i = 0;
	while(i < 3)
	{
		if (!player->gun[i])
		{
			i++;
			continue;
		}
		ft_memdel((void**)&player->gun[i]);
		i++;
	}
	if (player->sky)
		SDL_FreeSurface(player->sky);
	ft_memdel((void**)&player);
}



t_player				*new_t_player(int pos_x, int pos_y, t_point win_size)
{
	t_player			*player;

	player  = (t_player*)malloc(sizeof(t_player));
	*player = (t_player){};
	player->pos = (t_vector){pos_x, pos_y, 0};
	player->curr_map= -1;
	player->half_win_size = (t_point) {win_size.x / 2, win_size.y / 2};
	player->yaw = 0;
	player->hfov = win_size.x * m_hfov;
	player->vfov = win_size.y * m_vfov;
	player->fall = 0;
	player->jump = 0;
	player->speed = 0.5f;
	player->inventar = NULL;
	player->height = EyeHeight;
	player->health = 100;
	return (player);
}