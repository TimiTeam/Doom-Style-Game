#ifndef __SCALER_H
#define __SCALER_H

#define CeilingFloorScreenCoordinatesToMapCoordinates(mapY, screenX,screenY, X,Z) \
            do { Z = (mapY)*H*(1.0 * .2f)/ ((H/2 - (screenY))); \
                 X = (Z) * (W/2 - (screenX)) / (W*(1.0 * 0.73f*H/W)); \
                RelativeMapCoordinatesToAbsoluteOnes(X,Z); } while(0)
#define RelativeMapCoordinatesToAbsoluteOnes(X,Z) \
            do { float rtx = (Z) * player.cos_angl + (X) * player.sin_angl; \
                 float rtz = (Z) * player.sin_angl - (X) * player.cos_angl; \
         X = rtx + player.pos.x; Z = rtz + player.pos.y; \
         } while(0)
		 
#define Scaler_Init(a,b,c,d,f) \
    { d + (b-1 - a) * (f-d) / (c-a), ((f<d) ^ (c<a)) ? -1 : 1, \
      abs(f-d), abs(c-a), (int)((b-1-a) * abs(f-d)) % abs(c-a) }

typedef struct 		Scaler {
	int result, bop, fd, ca, cache; 
} 					Scaler;

Uint32      getpixel(SDL_Surface *surface, int x, int y);

#endif