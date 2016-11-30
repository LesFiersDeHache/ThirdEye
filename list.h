#include <stdlib.h>
#include <stdio.h>
#include <err.h>


#ifndef ONLYONCE_LIST
#define ONLYONCE_LIST
// List type
// You don't need to know what is inside
typedef struct List List;

struct List {

  int a;
  int b;
  int c;
  int d;

  int is_end;
  List* next;

};

//push_front
//Push a new entry at the head of the list
// - tab[4] : the 4 int you want to push
// - next : the head of the list
// 
// return : the new head of the list
List* push_front(int* tab, List* next);

//empty_list
//Return a empty list.
//
// return : an empty list
List* empty_list();

//print_list
//Print the list
// - list : the list to print
//
// return : void
void print_list(List* list);

//is_empty
//Return 0 if the list is NOT empty
//Return 1 if the list is empty
// - list : list to test
//
// return : 0 or 1
int is_empty(List* list);

//get_coord
//Get the index-th coord in the list
// - index : the index of the wanted coord (0, 1, 2, 3)
// - list : the list
//
// return : the wanted coord
int get_coord(int index, List* list);

//get_n
//Get the n-th list in the list
// - index : n
// - list : the head of the list
//
// return : the n-th list
List* get_n(int index, List* list);
int cmpList(List *a,List *b);
List* Merge(List* L1, List* L2);

void freeList(List* l);
#endif
