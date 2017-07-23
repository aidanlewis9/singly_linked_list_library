#ifndef LIST_H 
#define LIST_H

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

struct list {
    struct node *head;
    struct node *tail;
    size_t	 size;
};

struct list *	list_create();
struct list *	list_delete(struct list *l);

void		list_push_front(struct list *l, char *s);
void		list_push_back(struct list *l, char *s);

void		list_dump(struct list *l, FILE *stream);

struct node **	list_to_array(struct list *l);
void		list_qsort(struct list *l, node_compare f);

void		list_reverse(struct list *l);

void		list_msort(struct list *l, node_compare f);

#endif
