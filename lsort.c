/* lsort.c */

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "  -n   Numerical sort\n");
    fprintf(stderr, "  -q   Quick sort\n");
    exit(status);
}

void lsort(FILE *stream, bool numeric, bool quicksort) {
    char buffer[BUFSIZ];
    struct list * l = list_create();
    while (fgets(buffer, BUFSIZ, stream))
    {
        list_push_back(l, buffer);   
    } 
    if (quicksort && numeric)
        list_qsort(l, node_compare_number);
    else if (quicksort && !numeric)
        list_qsort(l, node_compare_string);
    else if (!quicksort && numeric)
        list_msort(l, node_compare_number);
    else
        list_msort(l, node_compare_string);
    printf("\n");
    for (struct node * n = l->head; n != NULL; n = n->next)
    {
        printf("%s\n", n->string);
    }
    list_delete(l);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    int argind = 1;
    bool numeric = false;
    bool quicksort = false;
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-')
    {
        char *arg = argv[argind++];
        switch (arg[1])
        {
            case 'h':
                usage(0);
                break;
            case 'n':
                numeric = true;
                break;
            case 'q':
                quicksort = true;
                break;
            default:
                usage(1);
                break;
        }
    }

    /* Sort using list */
    lsort(stdin, numeric, quicksort);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
