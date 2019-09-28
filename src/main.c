#include "main_head.h"

void 				free_data_holder(t_read_holder *holder)
{
	int				i;
	
	if(!holder)
		return ;
	delete_sectors(holder->all);
	delete_items_list_with_animation(holder->all_items);
	i = 0;
	while (i < 5 && holder->maps_path[i])
	{
		ft_strdel(&holder->maps_path[i]);
		i++;
	}
	i = 0;
	while(i < holder->text_count && holder->textures[i])
	{
		SDL_FreeSurface(holder->textures[i]);
		i++;
	}
	ft_memdel((void**)&holder->textures);
}

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

void 			fill_super_data(t_super_data *super, t_sector *sec, t_draw_data *data, t_wall wall)
{
	super->data = data;
	super->drawing_line = wall;
	super->floor_texture = sec->floor_tex;
	super->ceil_texture = sec->ceil_tex;
}

void 			*thread_draw_sector(void *param)
{
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
	int 		txtx;
	int			x_lenght;

	t_draw_data *data;
	t_super_data *super;
	t_sector	*sec;
	super = (t_super_data*)param;

	float maxDist = 15;	
	int z;
	cp = super->drawing_line;
	t_vector vec = {super->wall.start.x - super->wall.end.x, super->wall.start.y - super->wall.end.y};	
	float dist = sqrtf(vec.x * vec.x + vec.y * vec.y);	
	float mapped;
	float dx;
	data = super->data;
	x = super->start_x;
	end = super->end_x;
	sec = super->sect;
	x_lenght = cp.end.x - cp.start.x;
	float  scale_width_texture = super->wall.texture->w * super->scaleL;
	while (x < end)
	{
		ya = (x - cp.start.x) * (data->ceil_height) / x_lenght + data->ceil_y_s;

		cya = clamp(ya, data->ytop[x], data->ybottom[x]);

        yb = (x - cp.start.x) * (data->floor_height) / x_lenght + data->floor_y_s;

		cyb = clamp(yb, data->ytop[x], data->ybottom[x]);

		txtx = (super->u0 * ((cp.end.x - x) * cp.end.y) + super->u1 * ((x - cp.start.x) * cp.start.y)) / ((cp.end.x - x) * cp.end.y + (x - cp.start.x) * cp.start.y);
		
	//	if (sec->door)
			draw_floor_or_ceil(super->main_screen, super->ceil_texture, x, super->data->ytop[x], cya, super->data->diff_ceil, super->player, super->sect, super->sect->sector_light);
	//	else
	//		draw_skybox(super->main_screen, super->player.sky, x, super->data->ytop[x], cya, super->player);
		draw_floor_or_ceil(super->main_screen, super->floor_texture, x, cyb, super->data->ybottom[x], super->data->diff_floor, super->player, super->sect, super->sect->sector_light);
		mapped = txtx / (scale_width_texture) * dist;
		dx = (dist - mapped) / dist;
		t_vector tex_pos = {vec.x * dx + super->wall.end.x, vec.y * dx + super->wall.end.y};
		if (super->wall.type == filled_wall)
			textLine(x, cya, cyb, (struct Scaler)Scaler_Init(ya, cya, yb, 0, fabsf(sec->floor - sec->ceil) * super->scaleH), txtx, sec, super->main_screen, super->wall.texture, tex_pos, super->scaleL, super->scaleH, super->sect->sector_light);
		else
		{
			nya = (x - cp.start.x) * (data->n_ceil_height) / x_lenght + data->n_ceil_y_s;
			nyb = (x - cp.start.x) * (data->n_floor_height) / x_lenght + data->n_floor_y_s;
			n_cya = clamp((x - cp.start.x) * (data->n_ceil_height) / x_lenght + data->n_ceil_y_s, data->ytop[x], data->ybottom[x]);
			n_cyb = clamp((x - cp.start.x) * (data->n_floor_height) / x_lenght + data->n_floor_y_s, data->ytop[x], data->ybottom[x]);
			if (nya - 1 != ya && cya != n_cya)
    	 	{
			//	if (!sec->door)
			//		draw_skybox(super->main_screen, super->player.sky, x, cya, n_cya - 1, super->player);
			//	else
					textLine(x, cya, n_cya - 1, (struct Scaler)Scaler_Init(ya, cya, nya - 1, 0, super->scaleH * 10), txtx, sec, super->main_screen, super->wall.texture, tex_pos, super->scaleL, super->scaleH, super->sect->sector_light);
			}
        	if (yb - 1 !=  nyb && n_cyb != cyb)
      			textLine(x, n_cyb + 1, cyb, (struct Scaler)Scaler_Init(nyb, n_cyb, yb - 1, 0,  super->scaleH * 10), txtx, sec, super->main_screen, super->wall.texture, tex_pos, super->scaleL, super->scaleH, super->sect->sector_light);
			data->ytop[x] = n_cya;
			data->ybottom[x] = n_cyb;
		}
		x++;
	}
	return (NULL);
}

void 			draw_world(t_sector *sec, t_wall wall, t_player player, t_sdl *sdl, t_draw_data data)
{
	t_vector 	scale1;
	t_vector 	scale2;
	t_wall		line;
	int 		u0;
	int			u1;
	float 		scaleL;

	line.start = (t_vector){wall.start.x - player.pos.x, wall.start.y - player.pos.y, wall.start.z - player.pos.z};
	line.end = (t_vector){wall.end.x - player.pos.x, wall.end.y - player.pos.y, wall.end.z - player.pos.z};

	line.start = (t_vector){line.start.x * player.sin_angl - line.start.y * player.cos_angl,
				line.start.x * player.cos_angl + line.start.y * player.sin_angl, .z = line.start.y};
	line.end = (t_vector){line.end.x * player.sin_angl - line.end.y * player.cos_angl,
			line.end.x * player.cos_angl + line.end.y * player.sin_angl, .z = line.end.y};

	if (line.start.y <= 0 && line.end.y <= 0)
		return ;

	t_vector org1 = {line.start.x, line.start.y}, org2 = {line.end.x, line.end.y};

	if (line.start.y <= 0 || line.end.y <= 0)
		make_intersect(&line);

	if(fabsf(wall.start.x - wall.end.x) > fabsf(wall.start.y - wall.end.y))
    	scaleL = fabsf(wall.start.x - wall.end.x) / 10;
    else
    	scaleL = fabsf(wall.start.y - wall.end.y) / 10;

	if(fabs(line.end.x - line.start.x) > fabs(line.end.y - line.start.y))
		maping_wall_texture(&u0, &u1, line.start.x - org1.x, line.end.x - org1.x, (wall.texture->w * scaleL - 1) / (org2.x - org1.x));
	else
		maping_wall_texture(&u0, &u1, line.start.y - org1.y, line.end.y - org1.y, (wall.texture->w * scaleL - 1) / (org2.y - org1.y));
	
	scale1 =(t_vector) {player.hfov / line.start.y, player.vfov / line.start.y};
    scale2 =(t_vector) {player.hfov / line.end.y, player.vfov / line.end.y};

	line.start.x = player.half_win_size.x - (int)(line.start.x * scale1.x);
	line.end.x = player.half_win_size.x - (int)(line.end.x * scale2.x);

	if(line.start.x >= line.end.x || line.end.x < data.start || line.start.x > data.end)
		return ;
	data.ceil_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_ceil, line.start.y), scale1.y);
	data.ceil_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_ceil, line.end.y), scale2.y);
	data.floor_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_floor, line.start.y), scale1.y);
	data.floor_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(data.diff_floor, line.end.y), scale2.y);
	data.floor_height = data.floor_y_e - data.floor_y_s;
	data.ceil_height = data.ceil_y_e - data.ceil_y_s;
	if(wall.type != filled_wall)
	{
		data.n_ceil_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(min(wall.sectors[0]->ceil, wall.sectors[1]->ceil) - data.player_current_height, line.start.y), scale1.y);
		data.n_ceil_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(min(wall.sectors[0]->ceil, wall.sectors[1]->ceil) - data.player_current_height, line.end.y),scale2.y);
    	data.n_floor_y_s = calc_floor_ceil(player.half_win_size.y, Yaw(max(wall.sectors[0]->floor, wall.sectors[1]->floor) - data.player_current_height,line.start.y), scale1.y);
		data.n_floor_y_e = calc_floor_ceil(player.half_win_size.y, Yaw(max(wall.sectors[0]->floor, wall.sectors[1]->floor) - data.player_current_height,line.end.y), scale2.y);
		data.n_floor_height = data.n_floor_y_e - data.n_floor_y_s;
		data.n_ceil_height = data.n_ceil_y_e - data.n_ceil_y_s;
	}
	int THREAD_COUNT = 4;
	pthread_t	thread[THREAD_COUNT];
	t_super_data super[THREAD_COUNT];
	int step;

	data.start = max(line.start.x, data.start);
	data.end = min(line.end.x, data.end);
	step = (data.end - data.start) / THREAD_COUNT;
	for(int i = 0; i < THREAD_COUNT; i++)
	{
		fill_super_data(&super[i], sec, &data, line);
		super[i].start_x = data.start + (step * i);
		super[i].end_x = i + 1 == THREAD_COUNT ? data.end : super[i].start_x + step;
		super[i].main_screen = sdl->surf;
		super[i].player = player;
		super[i].sect = sec;
		super[i].scaleH = sec->ceil - sec->floor;
		super[i].scaleL = scaleL;
		super[i].u0 = u0;
		super[i].u1 = u1;
		super[i].wall = wall;
		pthread_create(&thread[i], NULL, thread_draw_sector, &super[i]);
	}
	for(int i = 0; i < THREAD_COUNT; i++)
	{
		pthread_join(thread[i], NULL);
	}
	if (wall.type != filled_wall)
	{
		if (wall.sectors[0]->sector != player.curr_sector->sector && wall.sectors[0]->sector != sec->sector)
			draw_sectors(wall.sectors[0], &player, sdl, data);
		else if (wall.sectors[1]->sector != player.curr_sector->sector && wall.sectors[1]->sector != sec->sector)
			draw_sectors(wall.sectors[1], &player, sdl, data);
	}
}

void				draw_projectiles(t_projectile **projectiles, t_player player, t_draw_data data, SDL_Surface *screen, t_item *items)
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
		enemy->speed = 0.22;
		if (enemy->is_dying)
			enemy->is_dying--;
		else if (enemy->dist_to_player < 30 && enemy->dist_to_player > 5)
		{
			enemy->curr_state = walk;
			enemy->speed = 0.44;
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


void 			get_gun_to_player(t_player *player, t_gun **guns, enum gun_type gun_type, SDL_Surface *icon)
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
		dst = (t_gun*)malloc(sizeof(t_gun));
		*dst = (t_gun){};
		i = 0;
		while (i < 10)
		{
			dst->frame[i] = src->frame[i];
			i++;
		}
		dst->damage = src->damage;
		dst->icon = src->icon;
		dst->type = src->type;
		player->current_gun = dst;
		player->gun[gun_type] = dst;
		player->gun[gun_type]->icon = icon;
		printf("New player gun : %p\n", player->gun[gun_type] );
	}
	player->gun[gun_type]->ammo += src->ammo;
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
		if ((it->curr_frame += it->speed) >= it->states[it->curr_state].max_textures)
		{
			if (it->curr_state == action)
				player->health -= it->damage;
			if (player->health <= 0 && !player->dead)
				player->dead = 1;
			it->curr_frame = 0;
			if (it->type == enemy && it->curr_state == die)
			{
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
		}
		if (it->dist_to_player <= 1.2f && it->type != object && it->type != enemy & it->type != light)
		{

			if (it->type == gun)
			{
				get_gun_to_player(player, all_guns, it->gun_type, it->states[waiting].texture[0]);
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
			else if (it->type == health)
			{
				if(player->health < 100)
				{
					player->health += it->health;
					player->health = player->health > 100 ? 100 : player->health;
					tmp = it->next;
					delete_item_by_ptr(items, it);
					it = tmp;
					continue ;
				}
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
		get_damege->is_dying = 4;
	}
}

void			draw_sectors(t_sector *sec, t_player *player, t_sdl *sdl, t_draw_data data)
{
	int			i;
	int			p;
	t_wall		*w;

	i = -1;
	p = -1;
	if (sec->door && sec->opening && sec->ceil <= sec->floor + 15)
		sec->ceil += 0.2f;
	data.diff_ceil = sec->ceil - data.player_current_height;
	data.diff_floor = sec->floor - data.player_current_height;
	if (data.diff_ceil < 0)
		player->fall = 1;
	while (++i < MAX_PORTALS && (w = sec->only_walls[i]))
	{
		draw_world(sec, *w, *player, sdl, data);
	}
	while (++p < MAX_PORTALS && (w = sec->portals[p]))
	{
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

int 			intersect_lines(t_vector one_start, t_vector one_end, t_vector two_start, t_vector two_end)
{
	float 		d;
	float		a;
	float		b;
	float 		Ua;
	float 		Ub;

	d = (two_end.y-two_start.y)*(one_start.x-one_end.x)-(two_end.x-two_start.x)*(one_start.y-one_end.y);
    if (d == 0){
        if ((one_start.x*one_end.y-one_end.x*one_start.y)*(two_end.x-two_start.x) - (two_start.x*two_end.y-two_end.x*two_start.y)*(one_end.x-one_start.x) == 0 && (one_start.x*one_end.y-one_end.x*one_start.y)*(two_end.y-two_start.y) - (two_start.x*two_end.y-two_end.x*two_start.y)*(one_end.y-one_start.y) == 0)
            return (1);
        else 
			return (0);
    }
    else{
        a = (two_end.x-one_end.x) * (two_end.y-two_start.y) - (two_end.x-two_start.x) * (two_end.y-one_end.y);
        b = (one_start.x - one_end.x) * (two_end.y - one_end.y) - (two_end.x-one_end.x) * (one_start.y-one_end.y);
        Ua = a / d;
        Ub = b / d;
        if (Ua >= 0 && Ua <=1 && Ub >= 0 && Ub <= 1)
			return (1);
    }
    return 0;
}

unsigned short   	dot_inside_sector(t_vector player_pos, t_wall **walls, unsigned arr_size)
{
	int				i;
	unsigned char	odd;
	t_wall			*curr;

	i = -1;
	odd = 0;
	while(++i < arr_size)
	{
		curr = walls[i];
		if ((curr->start.y < player_pos.y && curr->end.y >= player_pos.y) || (curr->end.y < player_pos.y && curr->start.y >= player_pos.y) )
		{
			if (curr->start.x + (float)(player_pos.y - curr->start.y) / (curr->end.y - curr->start.y) * (curr->end.x - curr->start.x) < player_pos.x)
				odd = odd == 0 ? 1 : 0;
		}
	}
	return (odd);
}

t_sector			*get_new_player_sector(t_vector player_pos, t_sector *intersect_sector)
{
	unsigned char 	i;
	t_wall			*w;

	if (!intersect_sector)
		return (NULL);
	i = 0;
	while (i < MAX_PORTALS && (w = intersect_sector->portals[i]))
	{
		if (w->sectors[0] && dot_inside_sector(player_pos, w->sectors[0]->wall, w->sectors[0]->n_walls))
			return (w->sectors[0]);
		if (w->sectors[1] && dot_inside_sector(player_pos, w->sectors[1]->wall, w->sectors[1]->n_walls))
			return (w->sectors[1]);
		i++;
	}
	return (NULL);
}

void			move_player(t_player *player, float sin_angle, float cos_angle)
{
	int			i;
	t_vector	step;
	t_wall		**wall;
	t_sector	*next;
	t_sector	*new;

	i = 0;
	step = (t_vector){player->pos.x + cos_angle * player->speed, player->pos.y + sin_angle * player->speed};
	wall = player->curr_sector->wall;
	float step_len = len_between_points(player->pos,step);
	while (i < player->curr_sector->n_walls)
	{
		if(IntersectBox(player->pos.x, player->pos.y, step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y)
        && PointSide(step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y) < 0)
		{
			if (wall[i]->type == filled_wall)
				return;
			if (wall[i]->sectors[0] && player->curr_sector!= wall[i]->sectors[0])
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1] && player->curr_sector != wall[i]->sectors[1])
				next = wall[i]->sectors[1];
			if (!next || (int)(next->ceil - next->floor) <= (int)(player->height + player->jump + player->sit))
				return ;
			new = get_new_player_sector(step, next);
			if (!new || (int)(new->ceil - new->floor) <= (int)(player->height + player->jump + player->sit))
				return ;
			player->curr_sector = new;
			break;
        }
		i++;
	}
	step.z = player->height + player->curr_sector->floor;
	player->pos = step;
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
	t_wall		**walls;

	i = -1;
	if (!has_key(player->inventar))
	{
		printf("You dont have a key\n");
		return ;
	}
	walls = player->curr_sector->portals;
	while (++i < MAX_PORTALS && walls[i])
	{
		if (find_dot_radius_intersect(player->pos, 3, walls[i]->start, walls[i]->end))
        {
			printf("Opening door...\n");
			t_sector *se = player->curr_sector == walls[i]->sectors[0] ? walls[i]->sectors[1] : walls[i]->sectors[0];
			if (se->door)
			{
				if (!se->opening)
				{
					use_key(player);
				}
				se->opening = 1;
			}
			return ;
        }
	} 
	printf("There is no door\n");
}

int					guess_event(SDL_Keycode code, t_player *player, unsigned char move[4], SDL_EventType type)
{
	if (code == SDLK_w || code == SDLK_UP)
		move[0] = type == SDL_KEYDOWN;
	else if (code == SDLK_s || code == SDLK_DOWN)
		move[1] = type == SDL_KEYDOWN;
	else if (code == SDLK_a)
		move[2] = type == SDL_KEYDOWN;
	else if (code == SDLK_d)
		move[3] = type == SDL_KEYDOWN;
	else if (code == SDLK_LSHIFT && type == SDL_KEYDOWN && !player->sit)
		player->speed = 1.2f;
	else if (code == SDLK_LSHIFT && type == SDL_KEYUP)
		player->speed = 0.6;
	else if (code == SDLK_SPACE && !player->jump && type == SDL_KEYDOWN)
		player->jump = 1;
	else if (code == SDLK_1 && type == SDL_KEYDOWN)
		player->current_gun = player->gun[pistol];
	else if (code == SDLK_2 && type == SDL_KEYDOWN)
		player->current_gun = player->gun[shotgun];
	else if (code == SDLK_3 && type == SDL_KEYDOWN)
		player->current_gun = player->gun[plasmagun];
	else if (type == SDL_KEYDOWN && code == SDLK_e)
			check_door(player, player->curr_sector);
	if (type == SDL_KEYDOWN && code == SDLK_LCTRL)
		player->sit = -3;
	if (type == SDL_KEYUP && code == SDLK_LCTRL)
		player->sit = 0;
	return (1);
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
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			return (0);
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (!player->dead)
				guess_event(e.key.keysym.sym, player, move, e.type);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN && player->current_gun && e.button.button == SDL_BUTTON_LEFT
		&& player->current_gun->ammo > 0 && !player->dead)
				player->shooting = 1;
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
				player->shooting = 0;
		
	}
	if (move[0] && !player->dead)
		move_player(player, player->sin_angl, player->cos_angl);
	if (move[1] && !player->dead)
		move_player(player, -player->sin_angl, -player->cos_angl);
	if (move[2] && !player->dead)
		move_player(player, -player->cos_angl, player->sin_angl);
	if (move[3] && !player->dead)
		move_player(player, player->cos_angl, -player->sin_angl);
	SDL_GetRelativeMouseState(&x, &y);
	y = -y;
    player->angle += x * 0.01;
	player->skyW += x * (player->sky->w / 360.0f);
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
    yaw = clamp(player->yaw - y * 0.05f, -5, 5);
	player->yaw = yaw;
	if (player->current_gun && player->current_gun->state == 0.44f && player->current_gun->type == plasmagun)
		add_projectile(&player->curr_sector->projectiles, create_projectile(*player));
	return (1);
}



int					game_loop(t_sdl *sdl, t_player *player, t_sector *sectors)
{
    int				run;
    SDL_Texture		*tex;
    char			str[100];
	unsigned char	move[4];
	SDL_Surface		*dead_text;

	ft_memset(move, 0, sizeof(move) * 4);
    player->cos_angl = cos(player->angle);
    player->sin_angl = sin(player->angle);
    run = 1;
	dead_text = get_text_surfcae(sdl->font, "YOU DIED", (SDL_Color){255, 30, 30, 255});
    while(run > 0)
    {
        SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 255);
        SDL_RenderClear(sdl->ren);
        SDL_FillRect(sdl->surf, NULL, 0x00);
        run_with_buff(player, sdl, sdl->win_size.x);
		draw_hud(sdl, player);
		run = hook_event(player, move, sectors);
		if (player->dead)
		{
			player->dead++;
			apply_filter(sdl->surf, 1.0f - (1.0f / 50) * player->dead);
			draw_image(sdl->surf, dead_text, (t_point){player->half_win_size.x - 200, player->half_win_size.y - 100}, (t_point){400, 200});
			player->yaw -= 3.0f/ 50.0f;
			player->pos.z -= 6.0f / 50;
			if (player->dead > 49)
			{
				player->dead = 0;
				run = 0;
				player->curr_map = -1;
			}
		}
        tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
        sdl_render(sdl->ren, tex, NULL, NULL);
        SDL_DestroyTexture(tex);
        SDL_RenderPresent(sdl->ren);
    }
    SDL_DestroyTexture(tex);
	SDL_FreeSurface(dead_text);
	return (run);
}

void				run_game(t_sdl *sdl, t_player *player, t_pr *m, t_read_holder *holder)
{
	int				in_game;
	SDL_Texture		*tex;

	in_game = 0;
	while (1)
	{
		if ((in_game = menu_hooks(m, holder)) < 0)
			break ;
		if (in_game > 0)
		{
			if (player->curr_map != holder->curr_map)
				if (!load_game(player, holder))
					error_message("Nooo");
			in_game = game_loop(sdl, player, holder->all);
		}
		render_menu(m, sdl);
		SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
		SDL_RenderClear(sdl->ren);
		tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
		sdl_render(sdl->ren, tex, NULL, NULL);
		SDL_DestroyTexture(tex);
		SDL_RenderPresent(sdl->ren);
	}
	SDL_DestroyTexture(tex);
}


int					main(int argc, char **argv)
{
	t_read_holder	holder;
	t_player		*player;
	t_sdl			*sdl;
	t_vector		player_pos;
	t_pr			m;

	holder = (t_read_holder){};
	m = (t_pr){};

	m.i = 0;
	m.win_h = H;
	m.win_w = W;
	
	if (read_game_config_file(&holder, "game_info.txt"))
	{
		sdl = new_t_sdl(W, H, "doom-nukem");
		init_sdl(sdl);

		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);

		load_textures(&m, sdl, &holder);
		initialize_sdl_win(&m);

		sdl->font = m.font;
		player = new_t_player(3, 3, sdl->win_size);
		player->sky = load_jpg_png("textures/skybox.png");

		all_guns = (t_gun**)malloc(sizeof(t_gun*) * 3);
		load_gun(all_guns);

		run_game(sdl, player, &m, &holder);

		free_player(player);
		delete_light_source(holder.light_source, holder.light_count);
		free_t_sdl(&sdl);
		free_menu(&m);
	}

	free_data_holder(&holder);

	system("leaks -q doom-nukem");
}