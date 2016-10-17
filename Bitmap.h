# include <stdlib.h>

#ifndef ONLYONCE_BITMAP
#define ONLYONCE_BITMAP
typedef enum Pixel
{

    BLACK, /// = 0
    WHITE /// = 1
 
} Pixel;



typedef struct Bitmap {

    unsigned short width; /// width of the picture in pixels
 
    unsigned short height; /// heigth of the picture in pixels
 
    Pixel *p_bitmap; /// pointer to an Pixel array which contains pixels value
 
}Bitmap;

void bitmapInit(Bitmap* bm, unsigned short width, unsigned short height);
int getPixel(Bitmap* bm, unsigned short x, unsigned short y);

void setPixel(Bitmap* bm, unsigned short x, unsigned short y, Pixel px);

void printBitmap(Bitmap* bm);
static unsigned short distBtwPts(unsigned int x, unsigned int y);

static int maxValue(int x, int y);


static int minValue(int x, int y);
void adjustBitmap(Bitmap* bm_in, Bitmap* bm_out, unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);

#endif