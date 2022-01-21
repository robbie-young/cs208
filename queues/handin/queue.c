// queue.c
// Authors: Robbie Young
// Last modified: 17/01/22
// Use: For use in Carleton's CS208 2022 Course

/*
 * Originally a starter file for CS 208 assignment: Queues in C
 * Adapted by Aaron Bauer and then Jeff Ondich
 * from a lab developed at CMU by R. E. Bryant, 2017-2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Creates a new node
 * If cannot allocate space returns NULL
*/
list_ele_t *node_new(char *s)
{
  list_ele_t *node = malloc(sizeof(list_ele_t));
  if (node == NULL) {
    return NULL;
  }

  char *s_copy = malloc(strlen(s) + 1);
  if (s_copy == NULL) {
    free(node);
    return NULL;
  }

  strcpy(s_copy, s);
  node->value = s_copy;
  node->next = NULL;
  return node;
}

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q = malloc(sizeof(queue_t));
  if (q == NULL) {
    return NULL;
  }
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  if (q == NULL) {
    return;
  }

  list_ele_t *curr = q->head;
  list_ele_t *temp;
  while (curr != NULL) {
    temp = curr;
    curr = curr->next;
    free(temp->value);
    free(temp);
  }

  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
  if (q == NULL) {
    return false;
  }

  list_ele_t *node = node_new(s);
  if (node == NULL) {
    return false;
  }

  node->next = q->head;
  q->head = node;
  if (q->size == 0) {
      q->tail = q->head;
  }

  q->size++;
  return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  if (q == NULL) {
    return false;
  }

  list_ele_t *node = node_new(s);
  if (node == NULL) {
    return false;
  }

  if (q->tail != NULL) {
    q->tail->next = node;
  }
  q->tail = node;

  if (q->size == 0) {
    q->head = node;
  }

  q->size++;
  return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  if (q == NULL || q->head == NULL) {
    return false;
  }

  if (sp != NULL) {
    strncpy(sp, q->head->value, bufsize);
    sp[bufsize - 1] = '\0';
  }

  list_ele_t *temp = q->head->next;
  free(q->head->value);
  free(q->head);
  q->head = temp;

  if (q->size == 1) {
    q->tail = NULL;
  }

  q->size--;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if (q == NULL) {
    return 0;
  }
  return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  if (q == NULL || q->size == 0) {
    return;
  }

  list_ele_t *prev = NULL;
  list_ele_t *curr = q->head;;
  list_ele_t *next = q->head->next;
  q->tail = q->head;
  while (next != NULL) {
    curr->next  = prev;
    prev = curr;
    curr = next;
    next = curr->next;
  }
  curr->next = prev;
  q->head = curr;
}