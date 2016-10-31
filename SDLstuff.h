#include "Bitmap.h"
#include "SDL/SDL_image.h"
#ifndef ONLYONCE_SDL
#define ONLYONCE_SDL
void wait_for_keypressed(void);


void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);

Uint32 getpixelSurface(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel2(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

Bitmap LoadToBitmap(char *path);


SDL_Surface* BitmapToSurface(Bitmap* bitm);
#endif
