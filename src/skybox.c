#include "sdl_head.h"
#include "main_head.h"

void	put_custom_pixel(SDL_Surface *screen, SDL_Surface *image, int x, int y, int width, int height, int imx, int imy, int imw, int imh)
{
    float tx;
    float ty = 0;
    int *pix = (int*)screen->pixels;
    unsigned char r, g, b, a;
	tx = ((float)imw / width) * x;
	ty = ((float)imh / height) * y;
	SDL_GetRGBA(get_pixel(image, (int)tx + imx, (int)ty + imy), image->format, &r, &g, &b, &a);
    if (x < W && x > 0 && y < H && y > 0 && a != 0){
        put_pixel(screen, x, y, SDL_MapRGBA(screen->format, r, g, b, a));
    } 
}

void			draw_skybox(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, t_player player)
{
	t_scaler scalH = init_scaler(player.yaw, (t_point){-5, 5}, (t_point){0, src->h / 2});
	player.skyH = scalH.result;
	while(y < end_y)
	{
		put_custom_pixel(dst, src, x, y, W, H, player.skyW, player.skyH, src->w / 2, src->h / 4);
		++y;
	}
}