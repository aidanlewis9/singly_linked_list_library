/* list.c */

#include "list.h"

/* Internal Function Prototypes */

static struct node*	reverse(struct node *curr, struct node *next);
static struct node *	msort(struct node *head, node_compare f);
static void		split(struct node *head, struct node **left, struct node **right);
static struct node *	merge(struct node *left, struct node *right, node_compare f);

/**
 * Create list.
 *
 * This allocates a list that the user must later deallocate.
 * @return  Allocated list structure.
 */
struct list *	list_create() {
    struct list *l = malloc(sizeof(struct list));
    if (l == NULL)
    {
      printf("Error\n");
      exit(1);
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

/**
 * Delete list.
 *
 * This deallocates the given list along with the nodes inside the list.
 * @param   l	    List to deallocate.
 * @return  NULL pointer.
 */
struct list *	list_delete(struct list *l) {
    node_delete(l->head, true);
    free(l);
    return NULL;
}

/**
 * Push front.
 *
 * This adds a new node containing the given string to the front of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_front(struct list *l, char *s) {
  struct node *n = node_create(s, l->head); // this might not work
  l->head = n;
  if (l->size == 0)
    l->tail = n;
  l->size++;
}

/**
 * Push back.
 *
 * This adds a new node containing the given string to the back of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_back(struct list *l, char *s) {
  struct node *n = node_create(s, NULL);
  if (l->tail != NULL)
    l->tail->next = n;
  l->tail = n;
  if (l->size == 0)
    l->head = n;
  l->size++;
}

/**
 * Dump list to stream.
 *
 * This dumps out all the nodes in the list to the given stream.
 * @param   l	    List structure.
 * @param   stream  File stream.
 */
void		list_dump(struct list *l, FILE *stream) {
  for (struct node *n = l->head; n != NULL; n = n->next)
  {
    node_dump(n, stream);
  }
}

/**
 * Convert list to array.
 *
 * This copies the pointers to nodes in the list to a newly allocate array that
 * the user must later deallocate.
 * @param   l	    List structure.
 * @return  Allocate array of pointers to nodes.
 */
struct node **	list_to_array(struct list *l) {
    struct node ** listArray = malloc(sizeof(struct node)*l->size);
    int i = 0;
    for (struct node *n = l->head; n != NULL; n = n->next, i++)
    {
      listArray[i] = n;
    }
    return listArray;
}

/**
 * Sort list using qsort.
 *
 * This sorts the list using the qsort function from the standard C library.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_qsort(struct list *l, node_compare f) {
  struct node ** listArray = list_to_array(l);
  qsort(listArray, l->size, sizeof(listArray), f);
  l->head = listArray[0];
  l->tail = listArray[(l->size)-1];
  int i = 0;
  for (struct node *n = l->head; n != NULL; n = n->next, i++)
  {
    if (i + 1 < l->size)
      listArray[i]->next = listArray[i+1];
    else
      listArray[i]->next = NULL;
    n = listArray[i];
  }
  free(listArray);
}

/**
 * Reverse list.
 *
 * This reverses the list.
 * @param   l	    List structure.
 */
void		list_reverse(struct list *l) {
  struct node * curr = l->head;
  struct node * prev = NULL;
  l->tail = l->head;
  l->head = reverse(curr, prev);
}

/**
 * Reverse node.
 *
 * This internal function recursively reverses the node.
 * @param   curr    The current node.
 * @param   prev    The previous node.
 * @return  The new head of the singly-linked list.
 */
struct node*	reverse(struct node *curr, struct node *prev) {
  if (curr->next == NULL)
  {
    curr->next = prev;
    return curr;
  }
  struct node * n = reverse(curr->next, curr);
  curr->next = prev;
  return n;
}

/**
 * Sort list using merge sort.
 *
 * This sorts the list using a custom implementation of merge sort.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_msort(struct list *l, node_compare f) {
  l->head = msort(l->head, f);
  struct node * getTail = l->head;
  while (getTail->next != NULL)
  {
    getTail = getTail->next;
  }
  l->tail = getTail;
}

/**
 * Performs recursive merge sort.
 *
 * This internal function performs a recursive merge sort on the singly-linked
 * list starting with head.
 * @param   head    The first node in a singly-linked list.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	msort(struct node *head, node_compare f) {
    struct node * left;
    struct node * right;
    if (head->next == NULL)
      return head;

    // Divide
    split(head, &left, &right);

    // Conquer
    left = msort(left, f);
    right = msort(right, f);

    // Combine
    return merge(left, right, f);
}

/**
 * Splits the list.
 *
 * This internal function splits the singly-linked list starting with head into
 * left and right sublists.
 * @param   head    The first node in a singly-linked list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 */
void		split(struct node *head, struct node **left, struct node **right) {
  struct node * slow = head;
  struct node * fast = head;
  struct node * tail;
  while (fast != NULL && fast->next != NULL)
  {
    tail = slow;
    slow = slow->next;
    fast = fast->next->next; 
  }
  *left = head;
  *right = slow;
  tail->next = NULL;
}

/**
 * Merge sublists.
 *
 * This internal function merges the left and right sublists into one ordered
 * list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	merge(struct node *left, struct node *right, node_compare f) {
  if (f > 0) // right is greater
  {
    struct node * n = right;
    while (n->next != NULL)
    {
      n = n->next;
    }
    n->next = left;
    return right; 
  }
  else // left is greater
  {
    struct node * n = left;
    while (n->next != NULL)
    {
      n = n->next;
    }
    n->next = right;
    return left;
  }    
}
