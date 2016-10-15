#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef enum Pixel
{
    BLACK, /// = 0
    WHITE /// = 1
 
}Pixel;

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