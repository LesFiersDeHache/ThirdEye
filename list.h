#include <stdlib.h>
#include <stdio.h>
#include <err.h>

/* Standard list implementation in C */
 
/* lists.h */
 
// List

typedef struct List List;

List* push_front(int* tab, List* next);

List* empty_list();

void print_list(List* list);

int is_empty(List* list);

int get_coord(int index, List* list);

List* get_n(int index, List* list);
