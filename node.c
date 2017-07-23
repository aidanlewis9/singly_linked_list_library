/* node.c */

#include "node.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Create node. 
 *
 * This allocates and configures a node that the user must later deallocate.
 * @param   string      String value.
 * @param   next        Reference to next node.
 * @return  Allocated node structure.
 */
struct node *	node_create(char *string, struct node *next) {
    struct node *new;
    new = malloc(sizeof(struct node));
    if (new == NULL)
    {
        exit(1);
    }
    if ((new->string = strdup(string)) == NULL) // 4 blocks lost, 4 blocks lost
    {
        exit(2);
    }
    new->number = atoi(string);
    new->next = next;
    return new;
}

/**
 * Delete node.
 *
 * This deallocates the given node (recursively if specified).
 * @param   n           Node to deallocate.
 * @param   recursive   Whether or not to deallocate recursively.
 * @return  NULL pointer.
 */
struct node *   node_delete(struct node *n, bool recursive) {
    if (recursive)
    {
        struct node *curr = n->next;
        struct node *temp = curr;
        while (curr != NULL)
        {
            temp = curr;
            curr = curr->next;
            free(temp->string);
            free(temp);
        }
    }
    free(n->string);
    free(n);
    return NULL;
}

/**
 * Dump node to stream.
 * 
 * This dumps out the node structure (Node{string, number, next}) to the stream.
 * @param   n       Node structure.
 * @param   stream  File stream.
 **/
void            node_dump(struct node *n, FILE *stream) {
    printf("Node{%s, %d, %p}\n", n->string, n->number, n->next);
}

/**
 * Compare node structures by number
 *
 * This compares two node structures by their number values.
 * @param   a       First node structure.
 * @param   b       Second node structure.
 * @return  < 0 if a < b, 0 if a == 0, > 0 if a > b
 */
int		node_compare_number(const void *a, const void *b) {
    return ((*(struct node **)a)->number - (*(struct node **)b)->number);
}

/**
 * Compare node structures by string
 *
 * This compares two node structures by their string values.
 * @param   a       First node structure.
 * @param   b       Second node structure.
 * @return  < 0 if a < b, 0 if a == 0, > 0 if a > b
 */
int		node_compare_string(const void *a, const void *b) {
    //puts("compare string");
    //printf("left: %s | right: %s\n", (*(struct node **)a)->string, (*(struct node **)b)->string);
    return strcmp((*(struct node **)a)->string, (*(struct node **)b)->string);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
