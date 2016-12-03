#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "listB.h"


struct listB* push_frontB(Bitmap *b,struct listB* next) {
  struct listB *LB = malloc(sizeof(struct listB));
  LB->is_end =0;
  LB->next = next;
  LB->bmp = b;
  return LB; 
}

struct listB* empty_listB() 
{
	struct listB* new_list = malloc(sizeof(struct listB));
  
    new_list->is_end = 1;
    new_list->next = NULL;
    new_list->bmp = NULL;
    return new_list;
}


int is_emptyB(struct listB* list) {
    return list->is_end;
}


struct listB* get_nB(int index, struct listB* list) {
    while (list->is_end == 0 && index > 0) {
        index--;
        list = list->next;
    }
    if (list->is_end != 0) {
        err(1, "List : get_n : index too big !");
    }
    return list;
}

struct listB* MergeB(struct listB* L1, struct listB* L2)
{
	struct listB* new_list = empty_listB();
	new_list = L1;
	while (new_list->next->is_end == 0) {
		new_list = new_list -> next;
	}
	new_list -> next = L2;
	return L1;
}

void freeB(struct listB* B)
{
    free(LB->bmp);
    free(B);
} 
