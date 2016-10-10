#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>



void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}
SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}



static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixelSurface(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}



/////// Structure Bitmap



typedef enum Pixel
{
    BLACK, /// = 0
    WHITE /// = 1
 
} Pixel;

typedef struct Bitmap
{
    unsigned short width; /// width of the picture in pixels
 
    unsigned short height; /// heigth of the picture in pixels
 
    Pixel *p_bitmap; /// pointer to an Pixel array which contains pixels value
 
} Bitmap;

void bitmapInit(Bitmap* bm, unsigned short width, unsigned short height)
{
    bm->width = width;
    bm->height = height;
    bm->p_bitmap = (Pixel*)malloc(sizeof(Pixel) * bm->width * bm->height);
 
    //assert(bm->p_bitmap != NULL); // Debug
 
    for (unsigned int i = 0 ; i < width * height ; ++i)
    {
    bm->p_bitmap[i] = BLACK; //We can also type "... = 0;"
    }
}
 
int getPixel(Bitmap* bm, unsigned short x, unsigned short y)
{
   // assert(x < bm->width); // Debug
   // assert(y < bm->height); // Debug
 
    return (bm->p_bitmap[(x * bm->width) + y]);
}
 
void setPixel(Bitmap* bm, unsigned short x, unsigned short y, Pixel px)
{
    //assert(x < bm->width); // Debug
    //assert(y < bm->height); // Debug
   
    bm->p_bitmap[(x * bm->width) + y] = px;
    //warnx("Pixel (%hd, %hd) set to %d.", x, y, px);
}
 
void printBitmap(Bitmap* bm)
{
    for (unsigned long i = 0 ; i < bm->width * bm->height ; ++i)
    {
    if (i % bm->width == 0 && i != 0)
    {
        printf("\n");
    }
    printf("%d", bm->p_bitmap[i]);
    }
    printf("\n");
}
 
static unsigned short distBtwPts(unsigned int x, unsigned int y)
{
    if (x == y)
    {
    return 0;
    }
    else if (x > y)
    {
    return x - y;
    }
    else
    {
    return y - x;
    }
}
 
static int maxValue(int x, int y)
{
    return (x > y) ? x : y;
}
 
static int minValue(int x, int y)
{
    return (x < y) ? x : y;
}
 
void adjustBitmap(Bitmap* bm_in, Bitmap* bm_out, unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    assert(x1 < bm_in->width); // Debug
    assert(y1 < bm_in->height); // Debug    
    assert(x2 < bm_in->width); // Debug
    assert(y2 < bm_in->height); // Debug
   
    bitmapInit(bm_out, distBtwPts(x1, x2) + 1, distBtwPts(y1, y2) + 1);
   
   
    for ( unsigned short i = x1; i <= x2 ; ++i ) {
       
        for ( unsigned short j = y1; j <= y2; ++j ) {
            warnx("Try to copy at (%hd,%hd).", i, j);
            int px = getPixel(bm_in, i, j);
            setPixel(bm_out, i - x1, j - y1, px);
        }
    }
   
}

/////////



void putpixel2(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) { 
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}
  




Bitmap LoadToBitmap(char *path)
{
  init_sdl();
  SDL_Surface *surface = load_image(path);  
  int width = surface -> w;
  int height = surface -> h;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Bitmap BitM;
  bitmapInit(&BitM, width, height);
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
      {
	Uint32 pixel = getpixelSurface(surface,i,j);
	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
       	float lum = (0.3*r + 0.59*g + 0.11*b);
	if (lum > 120)
	  {
	    setPixel(&BitM, i, j, 1);
	    lum = 255;
	  }
	else
	  {
	    setPixel(&BitM, i, j, 0);
	    lum = 0;
	  }
	pixel = SDL_MapRGB(surface->format, lum, lum, lum);
	putpixel2(surface,i,j,pixel); 
      }
  }  
  display_image(surface);
  return BitM;    
}

int main(int argc, char *argv[])
{  
  Bitmap b = LoadToBitmap("/afs/cri.epita.net/user/b/be/benete_p/u/globe.bmp");    
  return 0;  
}




