/* Standard list implementation in C */
 
/* list.c */
 
# include <stdlib.h>
 
# include "list.h"
#include "Bitmap.h"
 
struct list* list_push_front(struct list *list, Bitmap x)
{
  struct list *tmp = malloc(sizeof (struct list));
  tmp->next = list;
  tmp->data = x;
  return tmp;
}
 
void list_release(struct list *list)
{
  struct list *tmp = list;
  while (list) {
    tmp = list->next;
    free(list);
    list = tmp;
  }
}