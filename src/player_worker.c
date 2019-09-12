#include "main_head.h"

void 					load_gun(t_player *player)
{
	player->gun.state = 0;
	player->gun.frame[0] = load_jpg_png("textures/guns/pistol1.png");
	player->gun.frame[1] = load_jpg_png("textures/guns/pistol2.png");
	player->gun.frame[2] = load_jpg_png("textures/guns/pistol3.png");
	player->gun.frame[3] = load_jpg_png("textures/guns/pistol4.png");
}

t_player				*new_t_player(int pos_x, int pos_y, t_point win_size)
{
	t_player			*player;

	player  = (t_player*)malloc(sizeof(t_player));
	*player = (t_player){};
	player->pos = (t_vector){pos_x, pos_y, 0};
	player->half_win_size = (t_point) {win_size.x / 2, win_size.y / 2};
	player->yaw = 0;
	player->hfov = win_size.x / tan(400);
	player->vfov = win_size.y * (1.0 * .2f);
	player->fall = 0;
	player->jump = 0;
	player->speed = 0.7f;
	player->inventar = NULL;
	player->height = EyeHeight;
	load_gun(player);
	return (player);
}