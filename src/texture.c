#include "main_head.h"

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    }
}

int Scaler_Next(struct Scaler* i)
{
    for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca) i->result += i->bop;
    return i->result;
}
/*
void 			Sacaler_Init(Scaler *ret, float a, float b, float c, float d, float f)
{
	ret = {d + (b-1 - a) * (f-d) / (c-a), ((f<d) ^ (c<a)) ? -1 : 1, fabs(f-d), abs(c-a), (int)((b-1-a) * abs((int)(f-d))) % abs(c-a)};
}
*/
void textLine(int x, int y1,int y2, struct Scaler ty,unsigned txtx, SDL_Surface *surface, SDL_Surface *image)
{
    int *pix = (int*) surface->pixels;
    int *imagePix = (int*)image->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    pix += y1 * W + x;
    for(int y = y1; y <= y2; ++y)
    {
        unsigned txty = Scaler_Next(&ty);
        //*pix = imagePix[txtx % image->w + (txty % image->h) * image->w];
        *pix = getpixel(image, txtx % image->w, txty % image->h);
        pix += W;
    }
}
