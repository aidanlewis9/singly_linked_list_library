#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>

struct node {
    char	*string;
    int		 number;
    struct node *next;
};

typedef	int   (*node_compare)(const void *a, const void *b);

struct node *	node_create(char *string, struct node *next);
struct node *	node_delete(struct node *n, bool recursive);

void		node_dump(struct node *n, FILE *stream);

int		node_compare_number(const void *a, const void *b);
int		node_compare_string(const void *a, const void *b);

#endif
