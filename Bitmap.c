#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Bitmap
{
    unsigned long width; /// width of the picture in pixels
 
    unsigned long height; /// heigth of the picture in pixels
 
    unsigned short *p_bitmap; /// pointer to an Pixel array which contains pixels value
 
} Bitmap;

void bitmapInit(Bitmap* bm, unsigned long width, unsigned long height)
{
    bm->width = width;
    bm->height = height;
    bm->p_bitmap = (unsigned short*)malloc(sizeof(unsigned short) * bm->width * bm->height);
 
    //assert(bm->p_bitmap != NULL); // Debug
 
    for (unsigned int i = 0 ; i < width * height ; ++i)
    {
    bm->p_bitmap[i] =0 ; //We can also type "... = 0;"
    }
}
 
unsigned long getPixel(Bitmap* bm, unsigned long x, unsigned long y)
{
    assert(x < bm->width); // Debug
    assert(y < bm->height); // Debug
    
    return (bm->p_bitmap[(x * bm->width) + y]);
}
 
void setPixel(Bitmap* bm, unsigned long x, unsigned long y, unsigned long px)
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
 
static unsigned long distBtwPts(unsigned long x, unsigned long y)
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
 
/*static int maxValue(int x, int y)
{
    return (x > y) ? x : y;
}
 
static int minValue(int x, int y)
{
    return (x < y) ? x : y;
}
*/

void adjustBitmap(Bitmap* bm_in, Bitmap* bm_out, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2)
{
    assert(x1 <= bm_in->width); // Debug
    assert(y1 <= bm_in->height); // Debug    
    assert(x2 <= bm_in->width); // Debug
    assert(y2 <= bm_in->height); // Debug
   
    bitmapInit(bm_out, distBtwPts(x1, x2) + 1, distBtwPts(y1, y2) + 1);
   
   
    for ( unsigned long i = x1; i <= x2 ; ++i ) {
       
        for ( unsigned long j = y1; j <= y2; ++j ) {
            warnx("Try to copy at (%hd,%hd).", i, j);
            int px = getPixel(bm_in, i, j);
            setPixel(bm_out, i - x1, j - y1, px);
            printf("imout\n");
        }
    }
   
}
