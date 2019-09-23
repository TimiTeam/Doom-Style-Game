#include "main_head.h"

float scaleH = 16;

Uint8 menu = 1;

void 					load_gun(t_gun **gun)
{
	gun[pistol] = (t_gun*)malloc(sizeof(t_gun));
	*gun[pistol]= (t_gun){};
	gun[pistol]->ammo = 35;
	gun[pistol]->damage = 10;
	gun[pistol]->max_frames = 4;
	gun[pistol]->type = pistol;
	gun[pistol]->frame[0] = load_jpg_png("textures/guns/pistol/pistol1.png");
	gun[pistol]->frame[1] = load_jpg_png("textures/guns/pistol/pistol2.png");
	gun[pistol]->frame[2] = load_jpg_png("textures/guns/pistol/pistol3.png");
	gun[pistol]->frame[3] = load_jpg_png("textures/guns/pistol/pistol4.png");
	gun[shotgun] = (t_gun*)malloc(sizeof(t_gun));
	*gun[shotgun]= (t_gun){};
	gun[shotgun]->ammo = 12;
	gun[shotgun]->damage = 20;
	gun[shotgun]->max_frames = 6;
	gun[shotgun]->type = shotgun;
	gun[shotgun]->frame[0] = load_jpg_png("textures/guns/shotgun/shotgun_frame_1.png");
	gun[shotgun]->frame[1] = load_jpg_png("textures/guns/shotgun/shotgun_frame_2.png");
	gun[shotgun]->frame[2] = load_jpg_png("textures/guns/shotgun/shotgun_frame_3.png");
	gun[shotgun]->frame[3] = load_jpg_png("textures/guns/shotgun/shotgun_frame_4.png");
	gun[shotgun]->frame[4] = load_jpg_png("textures/guns/shotgun/shotgun_frame_3.png");
	gun[shotgun]->frame[5] = load_jpg_png("textures/guns/shotgun/shotgun_frame_2.png");
	gun[plasmagun] = (t_gun*)malloc(sizeof(t_gun));
	*gun[plasmagun]= (t_gun){};
	gun[plasmagun]->ammo = 20;
	gun[plasmagun]->type = plasmagun;
	gun[plasmagun]->damage = 35;
	gun[plasmagun]->max_frames = 3;
	gun[plasmagun]->frame[0] = load_jpg_png("textures/guns/plasmagun/plasmagun_1.png");
	gun[plasmagun]->frame[1] = load_jpg_png("textures/guns/plasmagun/plasmagun_2.png");
	gun[plasmagun]->frame[2] = load_jpg_png("textures/guns/plasmagun/plasmagun_3.png");
}

t_gun			**all_guns;

static float		len_between_points(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

int 				has_key(t_item *items)
{
	t_item			*all;

	all = items;
	while (all)
	{
		if (all->type == key)
			return (1);
		all = all->next;
	}
	return (0);
}

static void 			make_intersect(t_wall *wall)
{
	t_vector 	i1;
	t_vector 	i2;
	float 		nearz = 1e-4f, nearside = 1e-5f, farside = 1000.f;

	i1 = Intersect(wall->start.x, wall->start.y, wall->end.x, wall->end.y, -nearside,nearz, -farside,farz);
    i2 = Intersect(wall->start.x, wall->start.y, wall->end.x, wall->end.y,  nearside,nearz,  farside,farz);
	if(wall->start.y < nearz) 
	{
		if(i1.y > 0)
		{
			wall->start.x = i1.x;
			wall->start.y = i1.y;
		}
		else
		{
			wall->start.x = i2.x;
			wall->start.y = i2.y;
		}
	}
    if(wall->end.y < nearz)
	{
		if(i1.y > 0)
		{
			wall->end.x = i1.x;
			wall->end.y = i1.y;
		}
		else
		{
			wall->end.x = i2.x;
			wall->end.y = i2.y;
		}
	}
}

void			draw_sectors(t_sector *sectors, t_player *player, t_sdl *sdl, t_draw_data data);

int t = 1;


static int			calc_floor_ceil(unsigned half_win_size_y, float floor_or_ceil_diff, float scale_y)
{
	return (half_win_size_y - floor_or_ceil_diff * scale_y);
}

static void			maping_wall_texture(int *u0, int *u1, float diff_start, float diff_end, float scaled_tex)
{
	*u0 = diff_start * scaled_tex;
	*u1 = diff_end * scaled_tex;
}

void 				*thread_ceil_drawing(void *param)
{
	t_super_data	*super;
	int				x;
	int				end;
	float			ya;
	float			cya;
	SDL_Surface		*main_screen;
	SDL_Surface		*ceil_texture;

	super = (t_super_data*)param;
	x = super->data.start;
	end = super->data.end;
	ceil_texture = super->ceil_texture;
	main_screen = super->main_screen;
	while (x < end)
	{
		ya = (x - super->wall.start.x) * (super->data.ceil_y_e - super->data.ceil_y_s) / (super->wall.end.x - super->wall.start.x) + super->data.ceil_y_s;
		cya = clamp(ya, super->data.ytop[x], super->data.ybottom[x]);
		draw_floor_or_ceil(main_screen, ceil_texture, x, super->data.ytop[x], cya, super->data.diff_ceil, super->player, (t_vector){5,5,10}, super->sect);
		x++;
	}
	return (NULL);
}

void 			*thread_floor_drawing(void *param)
{
	t_super_data	*super;
	int				x;
	int				end;
	float			yb;
	float			cyb;
	SDL_Surface		*main_screen;
	SDL_Surface		*floor_texture;

	super = (t_super_data*)param;
	x = super->data.start;
	end = super->data.end;
	floor_texture = super->floor_texture;
	main_screen = super->main_screen;
	while (x < end)
	{
        yb = (x - super->wall.start.x) * (super->data.floor_y_e - super->data.floor_y_s) / (super->wall.end.x - super->wall.start.x) + super->data.floor_y_s;
		cyb = clamp(yb, super->data.ytop[x], super->data.ybottom[x]);
		draw_floor_or_ceil(main_screen, floor_texture, x, cyb, super->data.ybottom[x], super->data.diff_floor, super->player, (t_vector){5,5,10}, super->sect);
		x++;
	}
	return (NULL);
}

void 			fill_super_data(t_super_data *super, t_sector *sec, t_draw_data data, t_wall wall)
{
	super->data = data;
	super->wall = wall;
	super->floor_texture = sec->floor_tex;
	super->ceil_texture = sec->ceil_tex;
}
void 			draw_world(t_sector *sec, t_wall wall, t_player player, t_sdl *sdl, t_draw_data data)
{
	t_vector 	scale1;
	t_vector 	scale2;
	t_wall		cp;
	int 		cya;
	int 		cyb;
	int 		ya;
	int 		yb;
	int			nya;
	int			nyb;
	int 		n_cya;
	int 		n_cyb;
	int			x;
	int 		end;
	int 		u0, u1;
	float 		scaleL;
	int 		txtx;

	cp = wall;

	wall.start = (t_vector){wall.start.x - player.pos.x, wall.start.y - player.pos.y, wall.start.z - player.pos.z};
	wall.end = (t_vector){wall.end.x - player.pos.x, wall.end.y - player.pos.y, wall.end.z - player.pos.z};

	wall.start = (t_vector){wall.start.x * player.sin_angl - wall.start.y * player.cos_angl,
				wall.start.x * player.cos_angl + wall.start.y * player.sin_angl, .z = wall.start.y};
	wall.end = (t_vector){wall.end.x * player.sin_angl - wall.end.y * player.cos_angl,
			wall.end.x * player.cos_angl + wall.end.y * player.sin_angl, .z = wall.end.y};

	if (wall.start.y <= 0 && wall.end.y <= 0)
		return ;

	t_vector org1 = {wall.start.x, wall.start.y}, org2 = {wall.end.x, wall.end.y};

	if (wall.start.y <= 0 || wall.end.y <= 0)
		make_intersect(&wall);
	if(fabsf(cp.start.x - cp.end.x) > fabsf(cp.start.y - cp.end.y))
    	scaleL = fabsf(cp.start.x - cp.end.x) / 10;
    else
    	scaleL = fabsf(cp.start.y - cp.end.y) / 10;
	if(fabs(wall.end.x - wall.start.x) > fabs(wall.end.y - wall.start.y))
		maping_wall_texture(&u0, &u1, wall.start.x - org1.x, wall.end.x - org1.x, (wall.texture->w * scaleL - 1) / (org2.x - org1.x));
	else
		maping_wall_texture(&u0, &u1, wall.start.y - org1.y, wall.end.y - org1.y, (wall.texture->w * scaleL - 1) / (org2.y - org1.y));
	
	scale1 =(t_vector) {player.hfov / wall.start.y, player.vfov / wall.start.y};
    scale2 =(t_vector) {player.hfov / wall.end.y, player.vfov / wall.end.y};

	wall.start.x = player.half_win_size.x - (int)(wall.start.x * scale1.x);
	wall.end.x = player.half_win_size.x - (int)(wall.end.x * scale2.x);

	if(wall.start.x >= wall.end.x || wall.end.x < data.start || wall.start.x > data.end)
		return ;
	data.ceil_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_ceil, wall.start.y), scale1.y);
	data.ceil_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_ceil, wall.end.y), scale2.y);
	data.floor_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_floor, wall.start.y), scale1.y);
	data.floor_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_floor, wall.end.y), scale2.y);
	data.floor_height = data.floor_y_e - data.floor_y_s;
	data.ceil_height = data.ceil_y_e - data.ceil_y_s;
	if(wall.type == empty_wall)
	{
		data.n_ceil_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(min(wall.sectors[0]->ceil, wall.sectors[1]->ceil) - data.player_current_height, wall.start.y), scale1.y);
		data.n_ceil_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(min(wall.sectors[0]->ceil, wall.sectors[1]->ceil) - data.player_current_height, wall.end.y),scale2.y);
    	data.n_floor_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(max(wall.sectors[0]->floor, wall.sectors[1]->floor) - data.player_current_height,wall.start.y), scale1.y);
		data.n_floor_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(max(wall.sectors[0]->floor, wall.sectors[1]->floor) - data.player_current_height,wall.end.y), scale2.y);
		data.n_floor_height = data.n_floor_y_e - data.n_floor_y_s;
		data.n_ceil_height = data.n_ceil_y_e - data.n_ceil_y_s;

	}
	pthread_t	thread[2];
	t_super_data super[2];

	x = max(wall.start.x, data.start);
	end = min(wall.end.x, data.end);
	data.start = x;
	data.end = end;
	for(int i = 0; i < 2; i++)
	{
		fill_super_data(&super[i], sec, data, wall);
		super[i].main_screen = sdl->surf;
		super[i].player = player;
		super[i].sect = sec;
	}

	pthread_create(&thread[0], NULL, thread_ceil_drawing, &super[0]);
	pthread_create(&thread[1], NULL, thread_floor_drawing, &super[1]);
	float maxDist = 15;	
	int z;
	t_vector vec = {cp.start.x - cp.end.x, cp.start.y - cp.end.y};	
	float dist = sqrtf(vec.x * vec.x + vec.y * vec.y);	
	//float mapped = (x - x1) / (float)(x2-x1) * (dist - 0) + 0;
	float mapped;
	float dx;
	float  scale_width_texture = wall.texture->w * scaleL;
	while (x < end)
	{
		ya = (x - wall.start.x) * (data.ceil_height) / (wall.end.x - wall.start.x) + data.ceil_y_s;

		cya = clamp(ya, data.ytop[x], data.ybottom[x]);

        yb = (x - wall.start.x) * (data.floor_height) / (wall.end.x - wall.start.x) + data.floor_y_s;

		cyb = clamp(yb, data.ytop[x], data.ybottom[x]);

		txtx = (u0 * ((wall.end.x - x) * wall.end.y) + u1 * ((x - wall.start.x) * wall.start.y)) / ((wall.end.x - x) * wall.end.y + (x - wall.start.x) * wall.start.y);
		
	//	int z = ((x - wall.start.x) * (wall.end.y - wall.start.y) / (wall.end.x  - wall.start.x) + wall.start.y);	
		mapped = txtx / (scale_width_texture) * dist;
		dx = (dist - mapped) / dist;
		t_vector tex_pos = {vec.x * dx + cp.end.x, vec.y * dx + cp.end.y};
		if (wall.type != empty_wall)
//			textLine(x, cya, cyb, (struct Scaler)Scaler_Init(ya, cya, yb, 0, fabsf(sec->floor - sec->ceil) * scaleH), txtx, sdl->surf, wall.texture);
			textLine(x, cya, cyb, (struct Scaler)Scaler_Init(ya, cya, yb, 0, fabsf(sec->floor - sec->ceil) * scaleH), txtx, sec, sdl->surf, wall.texture, tex_pos, scaleL, scaleH, maxDist, (t_vector){5,5,10});
		else
		{
			nya = (x - wall.start.x) * (data.n_ceil_height) / (wall.end.x - wall.start.x) + data.n_ceil_y_s;
			nyb = (x - wall.start.x) * (data.n_floor_height) / (wall.end.x - wall.start.x) + data.n_floor_y_s;
			n_cya = clamp((x - wall.start.x) * (data.n_ceil_height) / (wall.end.x - wall.start.x) + data.n_ceil_y_s, data.ytop[x], data.ybottom[x]);
			n_cyb = clamp((x - wall.start.x) * (data.n_floor_height) / (wall.end.x - wall.start.x) + data.n_floor_y_s, data.ytop[x], data.ybottom[x]);
			if (nya - 1 != ya)
     	//		textLine(x, cya, n_cya - 1, (struct Scaler)Scaler_Init(ya, cya, nya - 1, 0, (float)sec->floor_tex->h), txtx, sdl->surf, wall.texture);
		 		textLine(x, cya, n_cya - 1, (struct Scaler)Scaler_Init(ya, cya, yb, 0, fabsf(sec->floor - sec->ceil) * scaleH), txtx, sec, sdl->surf, wall.texture, tex_pos, scaleL, scaleH, maxDist, (t_vector){5,5,10});
	
        	if (yb - 1 !=  nyb)
        	    //textLine(x, n_cyb + 1, cyb, (struct Scaler)Scaler_Init(nyb, n_cyb, yb - 1, 0, (float)sec->floor_tex->h), txtx, sdl->surf, wall.texture);
				textLine(x, n_cyb + 1, cyb, (struct Scaler)Scaler_Init(ya, cya, yb, 0, fabsf(sec->floor - sec->ceil) * scaleH), txtx, sec, sdl->surf, wall.texture, tex_pos, scaleL, scaleH, maxDist, (t_vector){5,5,10});
	
			data.ytop[x] = n_cya;
			data.ybottom[x] = n_cyb;

		}
		x++;
	}
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	if (wall.type == empty_wall)
	{
		if (wall.sectors[0]->sector != player.curr_sector->sector && wall.sectors[0]->sector != sec->sector)
			draw_sectors(wall.sectors[0], &player, sdl, data);
		else if (wall.sectors[1]->sector != player.curr_sector->sector && wall.sectors[1]->sector != sec->sector)
			draw_sectors(wall.sectors[1], &player, sdl, data);
	}
}


void 			open_door(t_wall *door, t_player *player, t_sector *current_sector)
{
	float 		vx;
	float 		vy;
	float 		dist;
	float 		dx;
	
	if (door->sectors[0] == current_sector && door->end.y > door->start.y)
	{ 
		vx = door->end.x - door->start.x;
		vy = door->end.y - door->start.y;
		dist = len_between_points(door->end, door->start);
		dx = (dist - 0.1) / dist;
		door->end.x = vx * dx + door->start.x;
		door->end.y = vy * dx + door->start.y;
		if (door->end.y <= door->start.y)
		{
			door->close = 0;
			door->opening = 0;
		}
	}
	if (door->sectors[1] == current_sector && door->end.y < door->start.y)
	{
		vx = door->start.x - door->end.x;
		vy = door->start.y - door->end.y;
		dist = len_between_points(door->end, door->start);
		dx = (dist - 0.1) / dist;
		door->start.x = vx * dx + door->end.x;
		door->start.y = vy * dx + door->end.y;
		if(door->end.y >= door->start.y)
		{
			door->close = 0;
			door->opening = 0;
		}
	}
}

void   draw_projectiles(t_projectile **projectiles, t_player player, t_draw_data data, SDL_Surface *screen, t_item *items)
{
	t_projectile	*tmp;
	t_projectile	*curr;
	t_item			*curr_enemy;
	Uint8			is_hit;

	curr_enemy = items;
	curr = *projectiles;

	while (curr)
	{
		is_hit = 0;
		draw_projectile(curr, data, player, screen);
		while (curr_enemy)
		{
			if (curr_enemy->type == enemy && len_between_points(curr->pos, curr_enemy->pos) <= 2 && curr_enemy->curr_state != die &&
			curr->pos.z > curr_enemy->pos.z + curr_enemy->sector->floor && curr->pos.z < curr_enemy->pos.z + curr_enemy->size.x + curr_enemy->sector->floor)
			{
				curr_enemy->health -= curr->damage;
				is_hit = 1;
				curr_enemy->players_hit = 1;
				break ;
			}
			curr_enemy = curr_enemy->next;
		}
		if (is_hit || !move_projectile(curr) || curr->pos.z < curr->curr_sector->floor - 2 || curr->pos.z > curr->curr_sector->ceil + 2)
		{
			tmp = curr->next;
			delete_projectile(projectiles, curr);
			curr = tmp;
			continue ;
		}
		curr = curr->next;
	}
}

void 			check_enemy_state(t_item *enemy, t_vector player_pos)
{
	if (enemy->health > 0)
	{
		if (enemy->is_dying)
			enemy->is_dying--;
		else if (enemy->dist_to_player < 30 && enemy->dist_to_player > 5)
		{
			enemy->curr_state = walk;
			move_enemy_to_player(enemy, player_pos);
		}
		else if (enemy->dist_to_player <= 5)
			enemy->curr_state = action;
		else
			enemy->curr_state = waiting;
	}
	else if (enemy->curr_state != die)
	{
		enemy->curr_state = die;
		enemy->curr_frame = 0;
	}
}


void 			get_gun_to_player(t_player *player, t_gun **guns, enum gun_type gun_type)
{
	t_gun		*src;
	t_gun		*dst;
	int			i;
	if (gun_type > 3)
	{
		printf("gun_type error %d\n", gun_type);
		return ;
	}
	printf("gun_type %d\n", gun_type);
	src = guns[gun_type];
	if (player->gun[gun_type] == NULL)
	{
		player->gun[gun_type] = (t_gun*)malloc(sizeof(t_gun));
		*player->gun[gun_type] = (t_gun){};
		i = 0;
		while (i < 10)
		{
			player->gun[gun_type]->frame[i] = src->frame[i];
			i++;
		}
		player->gun[gun_type]->damage = src->damage;
		player->gun[gun_type]->icon = src->icon;
		player->gun[gun_type]->type = src->type;
	}
	dst = player->gun[gun_type];
	dst->ammo += src->ammo;
	player->current_gun = dst;
}

void 			draw_sector_items(t_item **items, t_player *player, t_draw_data data, SDL_Surface *screen)
{
	t_item 	*tmp;
	t_item	*get_damege;
	float	closer;
	t_item	*it;

	closer = 1000.f;
	it = *items;
	get_damege = NULL;
	while (it)
	{
		if (it->type == enemy)
			check_enemy_state(it, player->pos);
		if ((it->curr_frame += 0.22) >= it->states[it->curr_state].max_textures)
		{
			if (it->curr_state == action)
			{
				player->health -= it->damage;
				printf("\tYour hp: %d\n", player->health);
			}
			if (player->health <= 0)
				printf("\tHey, You die!!\n");
			it->curr_frame = 0;
			if (it->type == enemy && it->curr_state == die)
			{
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
		}
		if (it->dist_to_player <= 1.5f && it->type != object && it->type != enemy)
		{
			if (it->type == gun )
			{
				get_gun_to_player(player, all_guns, it->gun_type);
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
			else if (it->type == health)
			{
				player->health += it->health;
				printf("Your Health %d\n", player->health);
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
			else if (it->type == ammo)
			{
				if (player->gun[it->gun_type])
				{
					player->gun[it->gun_type]->ammo += it->ammo;
					printf("player->gun[it->gun_type]->ammo %d\n", player->gun[it->gun_type]->ammo);
					tmp = it->next;
					delete_item_by_ptr(items, it);
					it = tmp;
					continue ;
				}
			}
			else
				from_list_to_another_list(items, &player->inventar, it);
		}
		else
		{
			draw_enemy_sprite(it, data, *player, screen);
			if (it->players_hit && closer > it->dist_to_player)
			{
				it->players_hit = 0;
				closer = it->dist_to_player;
				get_damege = it;
			}
		}
		it = it->next;
	}
	if (get_damege && get_damege->type == enemy)
	{
		get_damege->health -= player->current_gun->damage;
		get_damege->curr_state = taking_damage;
		get_damege->is_dying = 5;
	}
}

void			draw_sectors(t_sector *sec, t_player *player, t_sdl *sdl, t_draw_data data)
{
	int			i;
	int			d;
	int			p;
	t_wall		*w;
	t_draw_data		spr;

	d = 0;
	i = 0;
	p = -1;
	data.diff_ceil = sec->ceil - data.player_current_height;
	data.diff_floor = sec->floor - data.player_current_height;
	if (data.diff_ceil < 0)
		player->fall = 1;
	while (i < MAX_PORTALS && (w = sec->only_walls[i]))
	{
//		w = sec->wall[i];
//		if(w->type == filled_wall)
			draw_world(sec, *w, *player, sdl, data);
		i++;
	}
	while (++p < MAX_PORTALS && (w = sec->portals[p]))
	{
		if (!w->close)
			draw_world(sec, *w, *player, sdl, data);
	}
	i = -1;
	while (++i < MAX_PORTALS && (w = sec->doors[i]))
	{
		if (w->opening)
			open_door(w, player, sec);
		if (w->close)
			draw_world(sec, *w, *player, sdl, data);
	}
	quickSort(&sec->items, player);
	draw_sector_items(&sec->items, player, data, sdl->surf);
	draw_projectiles(&sec->projectiles, *player, data, sdl->surf, sec->items);
}

void				run_with_buff(t_player *player, t_sdl *sdl, unsigned int win_x)
{ 
	unsigned 		x;
	int 			ytop[win_x];
	int				ybottom[win_x];
	t_draw_data		draw_data;

	x = 0;
    while(x < win_x)
	{
		draw_data.ybottom[x] = sdl->win_size.y - 1;
		draw_data.ytop[x] = 0;
		x++;
	}
	draw_data.start = 0;
	draw_data.end = win_x;
	draw_data.player_current_height = (player->pos.z + player->jump + (player->curr_sector->ceil - player->curr_sector->floor <= player->height + player->jump + player->sit ? -3 : player->sit));
	draw_sectors(player->curr_sector, player, sdl, draw_data);
}

void			move_player(t_player *player, float sin_angle, float cos_angle)
{
	int			i;
	t_vector	step;
	t_wall		**wall;
	t_sector	*next;

	i = 0;
	step = (t_vector){player->pos.x + cos_angle * player->speed, player->pos.y + sin_angle * player->speed};

	wall = player->curr_sector->wall;
	while (i < player->curr_sector->n_walls)
	{
		if(IntersectBox(player->pos.x, player->pos.y, step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y)
        && PointSide(step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y) < 0)
        {
			if (wall[i]->type != empty_wall)
				return;
			if (wall[i]->sectors[0] && player->curr_sector->sector != wall[i]->sectors[0]->sector)
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1] && player->curr_sector->sector != wall[i]->sectors[1]->sector)
				next = wall[i]->sectors[1];
			if ((int)(next->ceil - next->floor) <= (int)(player->height + player->jump + player->sit))
				return ;
			player->curr_sector = next;
			step.z = player->height + player->curr_sector->floor;
			break;
        }
		i++;
	}
	step.z = player->height + player->curr_sector->floor;
	player->pos = step;
}

t_wall				*find_door_in_next_sector(t_sector *all, t_wall *door)
{
	t_sector		*sectors;
	t_wall			**walls;
	int				i;

	sectors = all;
	while (sectors)
	{
		walls = sectors->doors;
		i = 0;
		while (walls[i] && walls[i] != door)
		{
			if (walls[i]->id == door->id)
				return(walls[i]);
			i++;
		}
		sectors = sectors->next;
	}
	return (NULL);
}

void 				use_key(t_player *player)
{
	t_item			*all;
	t_item			*tmp;

	all = player->inventar;
	if (all->type == key)
	{
		player->inventar = all->next;
		ft_memdel((void**)&all);
		return ;
	}
	while ((all = all->next))
	{
		if (all->type == key)
		{
			tmp = player->inventar;
			while (tmp)
			{
				if (tmp->next == all)
				{
					tmp->next = all->next;
					ft_memdel((void**)&all);
					return ;
				}
				tmp = tmp->next;
			}
		}
	}
}

void 				check_door(t_player *player, t_sector *sectors)
{
	int			i;
	int			j;
	t_vector	step;
	t_wall		**walls;
	t_wall		*door_two;

	i = -1;
	if (!player->has_key)
	{
		printf("You dont have a key\n");
		return ;
	}
	walls = player->curr_sector->doors;
	step = (t_vector){player->pos.x + player->cos_angl * player->speed, player->pos.y + player->sin_angl * player->speed};
	while (++i < MAX_PORTALS && walls[i])
	{
		if(player->has_key && IntersectBox(player->pos.x, player->pos.y, step.x, step.y, walls[i]->start.x, walls[i]->start.y,
			walls[i]->end.x, walls[i]->end.y)
        && PointSide(step.x, step.y, walls[i]->start.x, walls[i]->start.y, walls[i]->end.x, walls[i]->end.y) < 0)
        {
			printf("Opening door...\n");
			use_key(player);
			player->has_key = has_key(player->inventar);
			j = 0;
			walls[i]->opening = 1;
			walls[i]->portal_ptr->close = 0;
			door_two = find_door_in_next_sector(sectors, walls[i]);
			door_two->opening = 1;
			door_two->portal_ptr->close = 0;
			return ;
        }
	}
	printf("There is no door\n");
}

int 				is_it_wall(t_vector pos, t_wall wall)
{
	t_point			n;
	int 			p;

	n = (t_point){wall.start.y - wall.end.y, wall.end.x - wall.start.x};
	p = (n.x * (pos.x - wall.start.x) + n.y * (pos.y - wall.start.y)) / sqrtf(n.x * n.x + n.y * n.y);
	return (p);
}
int					hook_event(t_player *player, unsigned char move[4], t_sector *sectors)
{
	SDL_Event		e;
	int				x;
	int				y;
	float			yaw;

	if (player->jump > 0 && player->jump < 10 && !player->fall)
		player->jump += 2;
	else if (player->jump >= 10)
		player->fall = 1;
	if (player->jump > 0 && player->fall)
		player->jump--;
	else if (player->jump == 0 && player->fall)
		player->fall = 0;
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return (0);
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP)
				move[0] = e.type == SDL_KEYDOWN;
			else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
				move[1] = e.type == SDL_KEYDOWN;
			else if (e.key.keysym.sym == 'p')
				scaleH++;
			else if (e.key.keysym.sym == 'm')
				scaleH--;
			else if (e.key.keysym.sym == SDLK_a)
				move[2] = e.type == SDL_KEYDOWN;
			else if (e.key.keysym.sym == SDLK_d)
				move[3] = e.type == SDL_KEYDOWN;
			else if (e.key.keysym.sym == SDLK_ESCAPE)
				return (0);
			else if (e.key.keysym.sym == SDLK_LSHIFT && e.type == SDL_KEYDOWN)
				player->speed = 1.5f;
			else if (e.key.keysym.sym == SDLK_LSHIFT && e.type == SDL_KEYUP)
				player->speed = 0.6;
			else if (e.key.keysym.sym == SDLK_SPACE && !player->jump)
				player->jump = 1;
			else if (e.key.keysym.sym == SDLK_1 && player->gun[pistol])
				player->current_gun = player->gun[pistol];
			else if (e.key.keysym.sym == SDLK_2 && player->gun[shotgun])
				player->current_gun = player->gun[shotgun];
			else if (e.key.keysym.sym == SDLK_3 && player->gun[plasmagun])
				player->current_gun = player->gun[plasmagun];
			
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e)
				check_door(player, player->curr_sector);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LCTRL)
			player->sit = -3;
		if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LCTRL)
			player->sit = 0;
		if (e.type == SDL_MOUSEBUTTONDOWN && player->current_gun)
		{
			if (e.button.button == SDL_BUTTON_LEFT && player->current_gun->ammo > 0){
				player->shooting = 1;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT){
				player->shooting = 0;
			}
		}
	}
	if (move[0])
		move_player(player, player->sin_angl, player->cos_angl);
	if (move[1])
		move_player(player, -player->sin_angl, -player->cos_angl);
	if (move[2])
		move_player(player, -player->cos_angl, player->sin_angl);
	if (move[3])
		move_player(player, player->cos_angl, -player->sin_angl);
	SDL_GetRelativeMouseState(&x, &y);
	y = -y;
    player->angle += x * 0.01;
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
    yaw = clamp(player->yaw - y * 0.05f, -5, 5);
	player->yaw = yaw;
	if (player->current_gun && player->current_gun->state == 0.33f && player->current_gun->type == plasmagun)
		add_projectile(&player->curr_sector->projectiles, create_projectile(*player));
	return (1);
}

int				render_menu(t_pr *m, t_sdl *sdl, t_sector *sectors)
{
		printf("Drawing background\n");
		draw_image(sdl->surf, m->background, 0, 0, sdl->win_size.x, sdl->win_size.y);
		printf("Background has been drawn\n");
		printf("Drawing logo\n");
		draw_image(sdl->surf, m->logo, m->logo_rect.x, m->logo_rect.y, m->logo_rect.w, m->logo_rect.h);
		printf("Logo has been drawn\n");
		printf("Drawing play_button\n");
		draw_image(sdl->surf, m->play_button, m->play_rect.x, m->play_rect.y, m->play_rect.w, m->play_rect.h);
		printf("play_button has been drawn\n");
		printf("Drawing choose_level_button\n");
		draw_image(sdl->surf, m->choose_level_button, m->choose_level_rect.x,
			m->choose_level_rect.y, m->choose_level_rect.w, m->choose_level_rect.h);
		printf("choose_level_button has been drawn\n");
		printf("Drawing font_texture\n");
		draw_image(sdl->surf, m->font_texture, m->font_rect.x, m->font_rect.y, m->font_rect.w, m->font_rect.h);
		printf("font_texture has been drawn\n");
		printf("Drawing exit_button\n");
		draw_image(sdl->surf, m->exit_button, m->exit_rect.x, m->exit_rect.y, m->exit_rect.w, m->exit_rect.h);
		printf("exit_button has been drawn\n");
		// SDL_RenderClear(sdl->ren);
		// SDL_RenderCopy(sdl->ren, m->background, NULL, NULL);
		// SDL_RenderCopy(sdl->ren, m->logo, NULL, &m->logo_rect);
		// SDL_RenderCopy(sdl->ren, m->play_button, NULL, &m->play_rect);
		// SDL_RenderCopy(sdl->ren, m->choose_level_button, NULL,
		// 	&m->choose_level_rect);
		// SDL_RenderCopy(sdl->ren, m->font_texture, NULL, &m->font_rect);
		// SDL_RenderCopy(sdl->ren, m->exit_button, NULL, &m->exit_rect);
		// SDL_RenderPresent(sdl->ren);
		while (SDL_PollEvent(&m->event))
		{
			if (m->event.type == SDL_QUIT)
				return (0);
			if (m->event.type == SDL_KEYDOWN)
			{
				printf("Event\n");
				down_action(m);
				up_action(m);
				rest_of_the_action_shit(m, &menu, sdl);
				if (m->event.key.keysym.sym == SDLK_ESCAPE)
					return (0);
			}
		}
		return (1);
}

void 				print_player_gun(t_sdl *sdl, t_player *pla)
{
	t_point			pos;
	t_point			size;
	SDL_Surface		*surf;

	if (!pla->current_gun->frame[(int)pla->current_gun->state])
	{
		pla->current_gun->state = 0;
		pla->current_gun->ammo--;
		printf("current_gun->ammo : %d\n", pla->current_gun->ammo);
	}
	surf = pla->current_gun->frame[(int)pla->current_gun->state];
	if ((pla->shooting || pla->current_gun->state) && pla->current_gun->ammo > 0)
		pla->current_gun->state += 0.33;
	pos.x = pla->half_win_size.x - surf->w / 2;
	pos.y = sdl->win_size.y - surf->h;
	draw_image(sdl->surf, surf, pos.x, pos.y, surf->w, surf->h);
}

void                game_loop(t_sdl *sdl, t_player *player, t_sector *sectors, t_pr *m)
{
    int				run;
    SDL_Texture		*tex;
    TTF_Font		*font;
    t_timer			timer;
    char			str[100];
    SDL_Texture		*text;
    SDL_Rect		fps_area;
	float			max;
	unsigned char	move[4];

	max = 0;
    font = TTF_OpenFont("font.ttf", 100);
    fps_area = (SDL_Rect){20, 20, 150, 55};

	ft_memset(move, 0, sizeof(move) * 4);
	
    player->cos_angl = cos(player->angle);
    player->sin_angl = sin(player->angle);
    run = 1;
    sdl->frame_id = 0;
    timer = init_timer();
    start_timer(&timer);
    while(run)
    {
		if (menu)
			run = render_menu(m, sdl, sectors);
		else
		{

			run_with_buff(player, sdl, sdl->win_size.x);
			player->has_key = has_key(player->inventar);
			if(player->current_gun)
				print_player_gun(sdl, player);

			if((sdl->fps = (float)sdl->frame_id / (get_ticks(timer) / 1000.f)) > 2000000)
				sdl->fps = 0;
			max = sdl->fps > max ? sdl->fps : max;
			sdl->frame_id++;
			sprintf(str, "fps:  %f", sdl->fps);

			text = make_black_text_using_ttf_font(sdl->ren, font, str);

			SDL_RenderCopy(sdl->ren, text, NULL, &fps_area);

			SDL_DestroyTexture(text);



			run = hook_event(player, move, sectors);
			// if (sdl->fps > 30)
			// 	SDL_Delay(20);
		}
		SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 255);
		SDL_RenderClear(sdl->ren);
		//SDL_FillRect(sdl->surf, NULL, 0x00);
		tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
		sdl_render(sdl->ren, tex, NULL, NULL);
		SDL_DestroyTexture(tex);
		SDL_RenderPresent(sdl->ren);
    }

	printf("\n\n\t\t---- MAX FPS  %f ----\n\n", max);

    TTF_CloseFont(font);

    SDL_DestroyTexture(tex);

}

void 				free_data_holder(t_read_holder *holder)
{
	int				i;
	
	if(!holder)
		return ;
	delete_items_list_with_animation(holder->all_items);
	i = 0;
	while (i < 5 && holder->maps_path[i])
	{
		ft_strdel(&holder->maps_path[i]);
		i++;
	}
	i = 0;
	while( i < holder->text_count && holder->textures[i])
	{
		SDL_FreeSurface(holder->textures[i]);
		i++;
	}
	ft_memdel((void**)&holder->textures);
	//ft_memdel((void**)&holder);
}

void	load_textures(t_pr *m, t_sdl *sdl)
{
	TTF_Init();
	m->done = SDL_FALSE;
	m->background = IMG_Load("textures/background1.jpg");
	m->play_button = IMG_Load("textures/play_button.png");
	m->exit_button = IMG_Load("textures/exit_button.png");
	m->logo = IMG_Load("textures/logo.png");
	m->choose_level_button = IMG_Load("textures/choose_level_button.png");
	m->font = TTF_OpenFont("amazdoom/AmazDooMLeft2.ttf", 256);
	m->font_color.r = 255;
	m->font_color.g = 255;
	m->font_color.b = 255;
	m->font_color.a = 255;
}

int					main(int argc, char **argv)
{
	t_read_holder	holder;
	t_sector		*sectors;
	t_player		*player;
	t_sdl			*sdl;
	t_pr			m;
	//holder = (t_read_holder*)malloc(sizeof(t_read_holder));
	holder = (t_read_holder){};

	m.i = 0;
	m.win_h = H;
	m.win_w = W;
	initialize_sdl_win(&m);
	read_game_config_file(&holder, "game_info.txt");
	list_sectors(sectors);
	if (holder.maps_path[0])
		sectors = read_map(holder.maps_path[0], &holder);
	if (!sectors)
		exit(1);
	sdl = new_t_sdl(W, H, "doom-nukem.");
	init_sdl(sdl);
	load_textures(&m, sdl);
	readdirec(&m, sdl, holder.maps_path, holder.maps_count);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	player = new_t_player(3, 3, sdl->win_size);
	player->height = EyeHeight;
	player->curr_sector = sectors;
	player->pos.z = player->curr_sector->floor + player->height;


	all_guns = (t_gun**)malloc(sizeof(t_gun*) * 3);
	load_gun(all_guns);

	game_loop(sdl, player, sectors, &m);

	list_items(player->inventar);

	free_player(player);
	delete_sectors(sectors);
	free_data_holder(&holder);
	free_t_sdl(&sdl);
	system("leaks -q doom-nukem");
}
