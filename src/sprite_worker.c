#include "main_head.h"

void    draw_enemy_image(SDL_Surface *screen, SDL_Surface *image, int x, int y, int width, int height, t_draw_data data)
{
    int i = -1;
    int j;
    float tx;
    float ty = 0;
    unsigned char r, g, b, a;
    while (++i < height)
    {
        j = -1;
        tx = 0;
        while (++j < width)
        {
            SDL_GetRGBA(get_pixel(image, (int)tx, (int)ty), image->format, &r, &g, &b, &a);
            if (j + x < W && j + x > 0 && i + y < H && i + y > 0 && a != 0 && j + x > data.start && j + x < data.end && i + y < data.ybottom[j + x] && i + y > data.ytop[j + x])
                put_pixel(screen, j + x, i + y, get_pixel(image, (int)tx, (int)ty));
            tx += (float)image->w / width;
        }
        ty += (float)image->h / height;
    }
}

void    draw_enemy_sprite(t_item obj, t_draw_data data, t_player player, SDL_Surface *surface)
{
        float vx = obj.pos.x - player.pos.x, vy = obj.pos.y - player.pos.y;
        float pcos = player.cos_angl, psin = player.sin_angl;
        float tx = vx * psin - vy * pcos,  tz = vx * pcos + vy * psin;
        if (tz <= 0)
            return ;
        float xscale = (W * m_hfov) / (tz), yscale = (H * m_vfov) / (tz);
        int x1 = W/2 + (int)(-tx * xscale);
        int y1 = H/2 + (int)(-Yaw(5 - (player.height + player.jump) , tz) * yscale);
        float dist = sqrtf(vx * vx + vy * vy);
        draw_enemy_image(surface, obj.id_text[0], x1 - 1000 / dist / 2, y1 - 1000 / dist / 2, 1000 / dist, 1000 / dist, data);
}