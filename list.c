#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "list.h"

typedef struct List {

    int a;
    int b;
    int c;
    int d;

    int is_end;
    List* next;

} List;

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

int main() {
    
    List* list = empty_list();
    print_list(list);
    int tab1[4] = {1, 2, 3, 4};
    int tab2[4] = {2, 3, 4, 5};
    int tab3[4] = {10, 10, 10, 10};
    list = push_front(tab1, list);
    list = push_front(tab2, list);
    list = push_front(tab1, list);
    list = push_front(tab3, list);
    print_list(list);
    printf("%d\n", get_coord(2, list));
    printf("%d\n", get_coord(3, get_n(0, list)));
    printf("%d\n", get_coord(3, get_n(1, list)));
    printf("%d\n", get_coord(3, get_n(2, list)));
    printf("%d\n", get_coord(3, get_n(3, list)));
    return 0;
}
