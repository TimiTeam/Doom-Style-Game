#include "sdl_head.h"
#include "main_head.h"

typedef struct	s_fpoint
{
	float x;
	float y;
}				t_fpoint;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

float   fNumberPart(float n)
{
    if (n > 0)
    {
        return (n - (int)n);
    }
    else
    {
        return (n - ((int)n + 1));
    }
}

float   rfNumberPart(float n)
{
    return (1 - fNumberPart(n));
}

void    draw_pixel(SDL_Renderer *renderer, float x, float y, float brightness, t_color color)
{
    SDL_SetRenderDrawColor(renderer, color.r * brightness, color.g * brightness, color.b * brightness, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void    line(SDL_Surface *surface, t_point start, t_point end, int color)
{
    int *pix = (int*)surface->pixels;
    int steep;
    t_fpoint diff;
    float gradient;
    float intersecY;

    if (abs(end.y - start.y) > abs(end.x - start.x))
        steep = 1;
    else
        steep = 0;
    if (steep)
    {
        swap(&start.x, &start.y);
        swap(&end.x, &end.y);
    }
    if (start.x > end.x)
    {
        swap(&start.x, &end.x);
        swap(&start.y, &end.y);
    }
    diff.x = end.x - start.x;
    diff.y = end.y - start.y;
    gradient = diff.y / diff.x;
    if (diff.x == 0.0)
        gradient = 1;
    intersecY = start.y;
    if (steep)
    {
        while (start.x <= end.x)
        {
            if (start.x >= 0 && start.x < H && intersecY >= 0 && intersecY < W)
            {
                pix[(int)intersecY + W * start.x] = color;
                pix[(int)intersecY - 1 + W * start.x] = color;
            }
            intersecY += gradient;
            start.x++;
        }
    }
    else
    {
        while (start.x <= end.x)
        {
            if (start.x >= 0 && start.x < W && intersecY >= 0 && intersecY < H)
            {
                pix[start.x + W * (int)intersecY] = color;
                pix[start.x + (W * (int)intersecY - 1)] = color;
            }
            intersecY += gradient;
            start.x++;
        }
    }
}

void    quad(SDL_Surface *surface, int x, int y, int w, int h, int color)
{
    int tmp = y;
    while (tmp <= y + h)
    {
        t_point start = {x, tmp};
        t_point end = {x + w, tmp};
        line(surface, start, end, color);
        tmp++;
    }
}