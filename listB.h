#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "Bitmap.h"
#ifndef ONLYONCE_LISTB
#define ONLYONCE_LISTB
struct listB {

  Bitmap *bmp;
  int is_end;
  struct listB* next;

};
struct listB* push_frontB(Bitmap *b, struct listB* next);

struct listB* empty_listB();

int is_emptyB(struct listB* list);

struct listB* get_nB(int index, struct listB* list);
struct listB* MergeB(struct listB* L1, struct listB* L2);

void freeB(struct listB* B);
#endif
