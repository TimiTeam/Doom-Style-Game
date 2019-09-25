#include "sdl_head.h"
#include "main_head.h"

void	draw_custom_image(SDL_Surface *screen, SDL_Surface *image, int x, int y, int width, int height, int imx, int imy, int imw, int imh)
{
	int i = -1;
    int j;
    float tx;
    float ty = 0;
    int *pix = (int*)screen->pixels;
    unsigned char r, g, b, a;
    while (++i < height)
    {
        j = -1;
        tx = 0;
        while (++j < width)
        {
            SDL_GetRGBA(get_pixel(image, (int)tx + imx, (int)ty + imy), image->format, &r, &g, &b, &a);
            if (j + x < W && j + x > 0 && i + y < H && i + y > 0 && a != 0)
                put_pixel(screen, j + x, i + y, SDL_MapRGBA(screen->format, r, g, b, a));
            tx += (float)imw / width;
        }
        ty += (float)imh / height;
    }
}

void	draw_skybox(SDL_Surface *surface, SDL_Surface *skybox, t_player player)
{
		int skyW;
		struct Scaler scalH = Scaler_Init(-5, player.yaw, 5, 0, skybox->h);
		int skyH = scalH.result / 2;
		float degreeAngle = rtod(player.angle);
		float tmp = 360 + (degreeAngle - 360 * ((int)degreeAngle / 360));
		struct Scaler scalW = Scaler_Init(0, tmp - 360 * ((int)tmp / 360), 360, 0, skybox->w - 1);
		skyW = scalW.result;
		draw_custom_image(surface, skybox, 0, 0, W, H, skyW, skyH, skybox->w / 3, skybox->h / 4);
}