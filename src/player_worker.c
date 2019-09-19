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
		int j = 0;
		while (j < player->gun[i].max_frames && player->gun[i].frame[j])
		{
			SDL_FreeSurface(player->gun[i].frame[j]);
			j++;
		}
		i++;
	}
	ft_memdel((void**)&player);
}

void 					load_gun(t_player *player)
{
	player->gun[pistol].damage = 10;
	player->gun[pistol].max_frames = 4;
	player->gun[pistol].type = pistol;
	player->gun[pistol].frame[0] = load_jpg_png("textures/guns/pistol/pistol1.png");
	player->gun[pistol].frame[1] = load_jpg_png("textures/guns/pistol/pistol2.png");
	player->gun[pistol].frame[2] = load_jpg_png("textures/guns/pistol/pistol3.png");
	player->gun[pistol].frame[3] = load_jpg_png("textures/guns/pistol/pistol4.png");
	player->gun[shotgun].damage = 20;
	player->gun[shotgun].max_frames = 6;
	player->gun[shotgun].type = shotgun;
	player->gun[shotgun].frame[0] = load_jpg_png("textures/guns/shotgun/shotgun_frame_1.png");
	player->gun[shotgun].frame[1] = load_jpg_png("textures/guns/shotgun/shotgun_frame_2.png");
	player->gun[shotgun].frame[2] = load_jpg_png("textures/guns/shotgun/shotgun_frame_3.png");
	player->gun[shotgun].frame[3] = load_jpg_png("textures/guns/shotgun/shotgun_frame_4.png");
	player->gun[shotgun].frame[4] = load_jpg_png("textures/guns/shotgun/shotgun_frame_3.png");
	player->gun[shotgun].frame[5] = load_jpg_png("textures/guns/shotgun/shotgun_frame_2.png");
	player->gun[plasmagun].type = plasmagun;
	player->gun[plasmagun].damage = 35;
	player->gun[plasmagun].max_frames = 3;
	player->gun[plasmagun].frame[0] = load_jpg_png("textures/guns/plasmagun/plasmagun_1.png");
	player->gun[plasmagun].frame[1] = load_jpg_png("textures/guns/plasmagun/plasmagun_2.png");
	player->gun[plasmagun].frame[2] = load_jpg_png("textures/guns/plasmagun/plasmagun_3.png");
}

t_player				*new_t_player(int pos_x, int pos_y, t_point win_size)
{
	t_player			*player;

	player  = (t_player*)malloc(sizeof(t_player));
	*player = (t_player){};
	player->pos = (t_vector){pos_x, pos_y, 0};
	player->half_win_size = (t_point) {win_size.x / 2, win_size.y / 2};
	player->yaw = 0;
	player->hfov = win_size.x * m_hfov;
	player->vfov = win_size.y * m_vfov;
	player->fall = 0;
	player->jump = 0;
	player->speed = 0.7f;
	player->inventar = NULL;
	player->height = EyeHeight;
	load_gun(player);
	player->current_gun = &player->gun[plasmagun];
	return (player);
}