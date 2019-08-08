#include "main_head.h"
#define EyeHeight  5
#define DuckHeight 2.5
#define HeadMargin 1
#define KneeHeight 2

#define Yaw(y,z) (y + z*player.yaw)


void			draw_yellow_line(SDL_Renderer *ren, t_vector start, t_vector end)
{
	SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0, 200);
	SDL_RenderDrawLine(ren, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
}

void			draw_line_any_colar(SDL_Renderer *ren,  t_vector start, t_vector end, int r, int g, int b)
{
	SDL_SetRenderDrawColor(ren, r, g, b, 200);
	SDL_RenderDrawLine(ren, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
}

static void vline(SDL_Surface *surface, int x, int y1, int y2, int top, int middle, int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}

void			draw_sectors(t_sector *sectors, t_player player, t_sdl *sdl, int *y_top, int *y_bottom, int s_x, int e_x);

int t = 0;

void			draw_world(t_sector *sectors, t_wall wall, t_player player, t_sdl *sdl, int *ytop, int *ybottom, int sx1, int sx2)
{
	t_vector	v1;
	t_vector	v2;
	t_vector	t1;
	t_vector	t2;
	float 		yceil;
	float 		yfloor;
	t_vector 	i1;
	t_vector 	i2;
	t_vector 	scale1; 
	t_vector 	scale2;
	int 		x1;
	int 		x2;
	int 		y1a;
	int 		y2a;
	int			begin;
	int			end;
	int 		cya;
	int 		cyb;
	int			y1b;
 	int			y2b;
	int 		ya; 
	int 		yb;

	v1 = (t_vector){wall.start.x - player.pos.x, wall.start.y - player.pos.y};
	v2 = (t_vector){wall.end.x - player.pos.x, wall.end.y - player.pos.y};

	t1.x = v1.x * player.sin_angl - v1.y * player.cos_angl;
	t1.y = v1.x * player.cos_angl + v1.y * player.sin_angl;

	t2.x = v2.x * player.sin_angl - v2.y * player.cos_angl;
	t2.y = v2.x * player.cos_angl + v2.y * player.sin_angl;
	if(t1.y <= 0 && t2.y <= 0)
		return ;

	int u0 = 0, u1 = wall.type != empty_wall? wall.texture->w - 1 : 1;

	if (t1.y <= 0 || t2.y <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
		i1 = Intersect(t1.x,t1.y,t2.x,t2.y, -nearside,nearz, -farside,farz);
        i2 = Intersect(t1.x,t1.y,t2.x,t2.y,  nearside,nearz,  farside,farz);
		t_vector org1 = {t1.x, t1.y}, org2 = {t2.x, t2.y};
		if(t1.y < nearz)
		{
			if(i1.y > 0)
			{
				t1.x = i1.x;
				t1.y = i1.y;
			}
			else
			{
				t1.x = i2.x;
				t1.y = i2.y;
			}
		}
        if(t2.y < nearz)
		{
			if(i1.y > 0)
			{
				t2.x = i1.x;
				t2.y = i1.y;
			}
			else
			{
				t2.x = i2.x;
				t2.y = i2.y;
			}
		}
		if (wall.type != empty_wall)
		{
			if(fabs(t2.x-t1.x) > fabs(t2.y-t1.y))
    	    	    u0 = (t1.x-org1.x) * (wall.texture->w - 1) / (org2.x-org1.x), u1 = (t2.x-org1.x) * (wall.texture->w - 1) / (org2.x-org1.x);
    		    else
    		        u0 = (t1.y-org1.y) * (wall.texture->w - 1) / (org2.y-org1.y), u1 = (t2.y-org1.y) * (wall.texture->w - 1) / (org2.y-org1.y);
		}
	}

    scale1 =(t_vector) {player.hfov / t1.y, player.vfov / t1.y};
    scale2 =(t_vector) {player.hfov / t2.y, player.vfov / t2.y};
	x1 = player.half_win_size.x -(int)(t1.x * scale1.x);
	x2 = player.half_win_size.x -(int)(t2.x * scale2.x);

	if(x1 >= x2 || x2 < sx1 || x1 > sx2)
		return ;

	if (wall.type == empty_wall)
	{
		yceil = min(wall.sectors[0]->ceil, wall.sectors[1]->ceil) - player.height;
    	yfloor = max(wall.sectors[0]->floor, wall.sectors[1]->floor) - player.height;
	}
	else
	{	
		yceil = wall.sectors[0]->ceil - player.height;
    	yfloor = wall.sectors[0]->floor - player.height;
	}
	
//	y1a = player.half_win_size.y - (int)(yceil * scale1.y),  y1b = player.half_win_size.y - (int)(yfloor * scale1.y);
//  y2a = player.half_win_size.y - (int)(yceil * scale2.y),  y2b = player.half_win_size.y - (int)(yfloor * scale2.y);

	y1a = player.half_win_size.y - (int)Yaw(yceil, t1.y) * scale1.y,  y1b = player.half_win_size.y - (int)(Yaw(yfloor, t1.y) * scale1.y);
	y2a = player.half_win_size.y - (int)Yaw(yceil, t2.y) * scale2.y,  y2b = player.half_win_size.y - (int)(Yaw(yfloor, t2.y) * scale2.y);

	begin = max(x1, sx1);
	end = min(x2, sx2);

//	Scaler ya_int = Scaler_Init(x1, begin, x2, y1a, y2a);
//	Scaler yb_int = Scaler_Init(x1, begin, x2, y1b, y2b);

	for(int x = begin; x <= end && x < sdl->win_size.x; ++x)
	{
		int txtx = (u0*((x2-x)*t2.y) + u1*((x-x1)*t1.y)) / ((x2-x)*t2.y + (x-x1)*t1.y);
		ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;
//		int ya = Scaler_Next(&ya_int);
		cya = clamp(ya, ytop[x], ybottom[x]); // top
        yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;
//        int yb = Scaler_Next(&yb_int);
		cyb = clamp(yb, ytop[x], ybottom[x]); // bottom
		SDL_SetRenderDrawColor(sdl->ren, 55, 35, 35, 255);
		SDL_RenderDrawLine(sdl->ren, x, ytop[x], x, cya-1);

/*		for(int y=ytop[x]; y<=ybottom[x]; ++y)
        {
            if (y >= cya && y <= cyb) {
				y = cyb;
				continue;
			}
            float 	hei;
            float 	mapx, mapz;
			hei = y < cya ? yceil: yfloor;
            CeilingFloorScreenCoordinatesToMapCoordinates(hei, x, y,mapx, mapz);
            unsigned tx = (mapx * 50), txtz = (mapz * 50);
            //printf("%d\n%d\n", txtx, txtz);
            int *floorPix = (int*)sectors->floor_tex->pixels;
            int *surfacePix = (int*)sdl->surf->pixels;
            int pel = floorPix[tx % sectors->floor_tex->w + (txtz % sectors->floor_tex->h) * sectors->floor_tex->w];
            surfacePix[y * W + x] = getpixel(sectors->floor_tex, tx % sectors->floor_tex->w, txtz % sectors->floor_tex->h);
        }
*/
		ytop[x] = cya;
		SDL_SetRenderDrawColor(sdl->ren, 20 * sectors->sector, 20  * (sectors->sector + 1), 12 * (sectors->sector + 1), 255);
		SDL_RenderDrawLine(sdl->ren, x, cyb+1, x, ybottom[x]);

		ybottom[x] = cyb;
		SDL_SetRenderDrawColor(sdl->ren, 255, 200 * (sectors->sector + 1), 0, 255);
		if (wall.type != empty_wall)
		{
			if (t % 2 == 0)
				textLine(x, cya, cyb, (struct Scaler)Scaler_Init(ya,cya,yb, 0, wall.texture->h), txtx, sdl->surf, wall.texture);
	/*		else 
				vline(sdl->surf, x, cya, cyb, 0xff0000, 0x00ff00, 0x000000);*/
			SDL_RenderDrawLine(sdl->ren, x, cya,x, cyb);
		}
		SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 255);
		SDL_RenderDrawPoint(sdl->ren, x, cya - 1);
		SDL_RenderDrawPoint(sdl->ren, x, cyb + 1);
	}
	SDL_RenderDrawLine(sdl->ren, end - 1, cya, end - 1, cyb);
	if (wall.type == empty_wall)
	{
		if (wall.sectors[0] && wall.sectors[0]->sector != sectors->sector && wall.sectors[0]->sector != player.curr_sector->sector)
			draw_sectors(wall.sectors[0], player, sdl, ytop, ybottom, begin, end);
		else if (wall.sectors[1] && wall.sectors[1]->sector != sectors->sector && wall.sectors[1]->sector != player.curr_sector->sector)
			draw_sectors(wall.sectors[1], player, sdl, ytop, ybottom, begin, end);
	}
}

float				len_between_points(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

float				get_triangle_height(t_vector a, t_vector b, t_vector c)
{
	int				ab;
	int				bc;
	int				ca;
	int				p;

	ab = len_between_points(a, b);
	bc = len_between_points(b, c);
	ca = len_between_points(c, a);
	p = (ab + bc + ca) >> 1;
	return (2 * (sqrt (p * (p - ab) * (p - bc) * (p - ca))) / ab);
}

int				get_nearest_line_to_dot(t_vector a, t_vector d1, t_vector d2)
{
	int 		ad1;
	int			ad2;

	ad1 = len_between_points(a, d1);
	ad2 = len_between_points(a, d2);
	return min(ad1, ad2);
}

void			sort_by_nearest(t_wall **walls, t_player player, signed short *tab, unsigned short max)
{
	int			i;
	int			j;
	float 		i_dist;
	float 		j_dist;
	int			tmp;
	
	i = 0;
	while (i < max && tab[i] != -1)
	{
		j = 0;
		i_dist = get_nearest_line_to_dot(player.pos, walls[tab[i]]->start, walls[tab[i]]->end);
		while (j < max && tab[j] != -1)
		{
			if (tab[i] != tab[j])
			{
				j_dist = get_nearest_line_to_dot(player.pos, walls[tab[j]]->start, walls[tab[j]]->end);
				if (i_dist < j_dist)
				{
					tmp = tab[i];
					tab[i] = tab[j];
					tab[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
}

void			draw_sectors(t_sector *sec, t_player player, t_sdl *sdl, int *y_top, int *y_bottom, int start_x, int end_x)
{
	int			i;
	int			p;
	int			wall;

	i = 0;
	p = 0;
	while (i < sec->n_walls)
	{
		if(sec->wall[i]->type != empty_wall)
			draw_world(sec, *sec->wall[i], player, sdl, y_top, y_bottom, start_x, end_x);
		i++;
	}
	sort_by_nearest(sec->wall, player, sec->portals, MAX_PORTALS);
	while (p < MAX_PORTALS && sec->portals[p] >= 0)
	{
		draw_world(sec, *sec->wall[sec->portals[p]], player, sdl, y_top, y_bottom, start_x, end_x);
		p++;
	}
}

void				run_with_buff(t_player player, t_sdl *sdl, unsigned int win_x)
{
	int 			ytop[win_x];
	int				ybottom[win_x];
	t_draw_data		border;

    for(unsigned x = 0; x < win_x; ++x)
		ybottom[x] = sdl->win_size.y - 1;
	for(unsigned x = 0; x < win_x; ++x)
		ytop[x] = 0;
	draw_sectors(player.curr_sector, player, sdl, ytop, ybottom, 0, win_x);
}

void			move_player(t_player *player, float sin_angle, float cos_angle)
{
	int			i;

	i = 0;
	while (i < player->curr_sector->n_walls)
	{
		if(IntersectBox(player->pos.x,player->pos.y, player->pos.x + cos_angle, player->pos.y + sin_angle,
			player->curr_sector->wall[i]->start.x, player->curr_sector->wall[i]->start.y,
			player->curr_sector->wall[i]->end.x, player->curr_sector->wall[i]->end.y)
        && PointSide( player->pos.x + cos_angle, player->pos.y + sin_angle,player->curr_sector->wall[i]->start.x, player->curr_sector->wall[i]->start.y,
			player->curr_sector->wall[i]->end.x, player->curr_sector->wall[i]->end.y) < 0)
        {
			if (player->curr_sector->wall[i]->type == fieled_wall)
				return;
			if (player->curr_sector->wall[i]->sectors[0] &&
				player->curr_sector->sector != player->curr_sector->wall[i]->sectors[0]->sector) 
				player->curr_sector = player->curr_sector->wall[i]->sectors[0];
			else if (player->curr_sector->wall[i]->sectors[1] &&
				player->curr_sector->sector != player->curr_sector->wall[i]->sectors[1]->sector) 
				player->curr_sector = player->curr_sector->wall[i]->sectors[1];
			player->pos = (t_vector){player->pos.x + cos_angle, player->pos.y + sin_angle};
			player->height = EyeHeight + player->curr_sector->floor;
			break;
        }
		i++;
	}
	player->pos = (t_vector){player->pos.x + cos_angle, player->pos.y + sin_angle};
}

int					hook_event(t_player *player)
{
	SDL_Event		e;

	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return (0);
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP)
				move_player(player, player->sin_angl, player->cos_angl);
			if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
				move_player(player, -player->sin_angl, -player->cos_angl);
			if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
			{
				if (e.key.keysym.sym == SDLK_LEFT)
					player->angle -= 0.05;
				else
					player->angle += 0.05;
				player->cos_angl = cos(player->angle);
				player->sin_angl = sin(player->angle);
			}
			if (e.key.keysym.sym == 't')
				t++;
			if (e.key.keysym.sym == SDLK_a)
				move_player(player, -player->cos_angl, player->sin_angl);
			if (e.key.keysym.sym == SDLK_d)
				move_player(player, player->cos_angl, -player->sin_angl);
			if (e.key.keysym.sym == SDLK_ESCAPE)
				return (0);
		}
	}
	return (1);
}

void			game_loop(t_sdl *sdl, t_player player, t_sector *sectors)
{
	int			run;
	SDL_Texture *tex;

	player.cos_angl = cos(player.angle);
	player.sin_angl = sin(player.angle);
	run = 1;
	while(run)
	{
		SDL_RenderClear(sdl->ren);
		SDL_FillRect(sdl->surf, NULL, 0x00);
		run_with_buff(player, sdl, sdl->win_size.x);
		if (t % 2 == 0)
		{
			tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
			sdl_render(sdl->ren, tex, NULL, NULL);
			SDL_DestroyTexture(tex);
		}
		SDL_RenderPresent(sdl->ren);
		run = hook_event(&player);
	}
	SDL_DestroyTexture(tex);
}


int				main(int argc, char **argv)
{
	t_sector	*sectors;
	t_player	player;
	t_sdl		*sdl;

	if (argc > 1)
		sectors = read_map(argv[1]);
	if (!sectors)
		exit(1);
	sdl = new_t_sdl(W, H, "test_sectors");
	init_sdl(sdl);
	SDL_ShowCursor(SDL_DISABLE);

	player = (t_player){};
	player.pos = (t_vector){3, 3, 1};
	player.half_win_size = (t_point) {sdl->win_size.x / 2, sdl->win_size.y / 2};
//	player.yaw = -0.3;
	// screenHeight / tan(horizontalfov) good value tan(400) 
	player.hfov = /*sdl->win_size.x / tan(400) */0.73f * sdl->win_size.y; 

	// screenWidth / tan(verticalfov) good value tan(350)
	player.vfov	= /*sdl->win_size.y / tan(350)*/ .2f * sdl->win_size.y;
	player.height = EyeHeight;
	player.curr_sector = sectors;

	game_loop(sdl, player, sectors);

	list_sectors(sectors);
	
	delete_sectors(sectors);
	free_t_sdl(&sdl);
//	system("leaks -q test");
}