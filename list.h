

/* Standard list implementation in C */
 
/* lists.h */
 
# ifndef EPITA_IP_SAMPLES_LISTS_H_
# define EPITA_IP_SAMPLES_LISTS_H_
#include "Bitmap.h"
 
/* simply linked list of integer */
 
struct list
{
  struct list *next;
  Bitmap          data;
};
 
static inline
struct list* list_empty(void)
{
  return NULL;
}
 
static inline
int list_is_empty(struct list *list)
{
  return list == NULL;
}
 
struct list* list_push_front(struct list *list, Bitmap x);
 
void list_release(struct list *list);
 
# endif /* EPITA_IP_SAMPLES_LISTS_H_ */