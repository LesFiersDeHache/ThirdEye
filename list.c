#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "list.h"

/*
typedef struct List {

    int a;
    int b;
    int c;
    int d;

    int is_end;
    List* next;

} List;
*/

List* push_front(int* tab, List* next) {
    List* new_list = malloc(sizeof(List));
    new_list->a = tab[0];
    new_list->b = tab[1];
    new_list->c = tab[2];
    new_list->d = tab[3];
    new_list->is_end = 0;
    new_list->next = next;
    return new_list;
}

List* empty_list() {
    List* new_list = malloc(sizeof(List));
    new_list->a = -1;
    new_list->b = -1;
    new_list->c = -1;
    new_list->d = -1;
    new_list->is_end = 1;
    new_list->next = NULL;
    return new_list;
}

void print_list(List* list) {

  printf("PRINT LIST\n");
    
    while(list->is_end == 0) {

        int a = list->a;
        int b = list->b;
        int c = list->c;
        int d = list->d;
        printf("{ %d, %d, %d, %d }\n", a, b, c, d);

        list = list->next;
    }
}

int is_empty(List* list) {
    return list->is_end;
}

int get_coord(int index, List* list) {
    
    switch (index) {
        case 0 :
            return list->a;
            break;
        case 1 :
            return list->b;
            break;
        case 2 :
            return list->c;
            break;
        case 3 :
            return list->d;
            break;
        default :
            err(1, "List : get_coord() : index >= 4 !");
            break;
    }
}

List* get_n(int index, List* list) {
    while (list->is_end == 0 && index > 0) {
        index--;
        list = list->next;
    }
    if (list->is_end != 0) {
        err(1, "List : get_n : index too big !");
    }
    return list;
}

List* Merge(List* L1, List* L2)
{
	List* new_list = empty_list();
	new_list = L1;
	while (new_list->next->is_end == 0) {
		new_list = new_list -> next;
	}
	new_list -> next = L2;
	return L1;
}

void freeList(List* l)
{
	free(l->next);
	free(l);
}
