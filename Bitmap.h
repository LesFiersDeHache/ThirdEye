# include <stdlib.h>

#ifndef ONLYONCE_BITMAP2
#define ONLYONCE_BITMAP2

typedef struct Bitmap {

    unsigned long width; /// width of the picture in pixels
 
    unsigned long height; /// heigth of the picture in pixels
 
    unsigned short *p_bitmap; /// pointer to an Pixel array which contains pixels value
 
}Bitmap;

void bitmapInit(Bitmap* bm, unsigned long width, unsigned long height);

int getPixel(Bitmap* bm, unsigned long x, unsigned long y);
void setPixel(Bitmap* bm, unsigned long x, unsigned long y, unsigned long px);

void printBitmap(Bitmap* bm);

void adjustBitmap(Bitmap* bm_in, Bitmap* bm_out, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2);

void freeBitmap(Bitmap *bmp);
#endif
