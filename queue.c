#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;
    
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    
    struct list_head *node, *safe;
    
    // Free all elements in the list
    list_for_each_safe(node, safe, head) {
        element_t *element = list_entry(node, element_t, list);
        list_del(node);
        free(element->value);
        free(element);
    }
    
    // Free the head itself
    free(head);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return false;
    
    // Allocate space for the string and copy it
    new_element->value = malloc(strlen(s) + 1);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    
    strcpy(new_element->value, s);
    
    // Add to the head of the list
    list_add(&new_element->list, head);
    
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return false;
    
    // Allocate space for the string and copy it
    new_element->value = malloc(strlen(s) + 1);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    
    strcpy(new_element->value, s);
    
    // Add to the tail of the list
    list_add_tail(&new_element->list, head);
    
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return target element.
 * Return NULL if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 *
 * NOTE: "remove" is different from "delete"
 * The space used by the list element and the string should not be freed.
 * The only thing "remove" need to do is unlink it.
 *
 * REF:
 * https://english.stackexchange.com/questions/52508/difference-between-delete-and-remove
 */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    
    // Get the first element
    element_t *element = list_first_entry(head, element_t, list);
    
    // Copy string to sp if provided
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';  // Ensure null termination
    }
    
    // Remove from list (but don't free the element)
    list_del(&element->list);
    
    return element;
}

/*
 * Attempt to remove element from tail of queue.
 * Other attribute is as same as q_remove_head.
 */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    
    // Get the last element
    element_t *element = list_last_entry(head, element_t, list);
    
    // Copy string to sp if provided
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';  // Ensure null termination
    }
    
    // Remove from list (but don't free the element)
    list_del(&element->list);
    
    return element;
}

/*
 * WARN: This is for external usage, don't modify it
 * Attempt to release element.
 */
void q_release_element(element_t *e)
{
    free(e->value);
    free(e);
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    
    int count = 0;
    struct list_head *node;
    
    list_for_each(node, head) {
        count++;
    }
    
    return count;
}

/*
 * Delete the middle node in list.
 * The middle node of a linked list of size n is the
 * ⌊n / 2⌋th node from the start using 0-based indexing.
 * If there're six element, the third member should be return.
 * Return true if successful.
 * Return false if list is NULL or empty.
 */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/*
 * Delete all nodes that have duplicate string,
 * leaving only distinct strings from the original list.
 * Return true if successful.
 * Return false if list is NULL.
 *
 * Note: this function always be called after sorting, in other words,
 * list is guaranteed to be sorted in ascending order.
 */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/*
 * Attempt to swap every two adjacent nodes.
 */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(struct list_head *head) {}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(struct list_head *head) {}
