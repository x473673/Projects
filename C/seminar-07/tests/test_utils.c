#include <stdio.h>

#define TESTING
#ifndef DEBUG
#  define TESTING_FORK_MODE
#endif
#include "test_utils.h"

void terminate(const char *str)
{
    fprintf(stderr, "%s\n", str);
    abort();
}

void assertListIntegrity(struct list *list)
{
    ASSERT(list != NULL);

    // the head is NULL if and only if the tail is NULL
    ASSERT(list->head == NULL || list->tail != NULL);
    ASSERT(list->tail == NULL || list->head != NULL);

    // empty list is trivially correct
    if (list->head == NULL)
        return;

    // check head->prev and tail->next
    ASSERT(list->head->prev == NULL);
    ASSERT(list->tail->next == NULL);

    // the list may only contain one node
    if (list->head == list->tail)
        return;

    // the list now contains at least two nodes, Gotta test'em all!
    for (struct node *node = list->head; node != NULL; node = node->next) {
        // null values are not allowed
        ASSERT(node->data != NULL);

        // identities
        if (node != list->head) {
            ASSERT(node->prev != NULL);
            ASSERT(node->prev->next == node);
        }

        if (node != list->tail) {
            ASSERT(node->next != NULL);
            ASSERT(node->next->prev == node);
        }
    }

    // ok, we are done
}

void assertListContent(struct list *list, size_t size, int *data)
{
    struct node *node = list->head;

    if (size == 0U) {
        // the list should be empty
        ASSERT(node == NULL);
        return;
    }

    for (size_t i = 0U; i < size; ++i) {
        ASSERT(node != NULL);
        ASSERT(node->data != NULL);

        // check i-th value
        int value = *(int*)(node->data);
        ASSERT(value == data[i]);

        node = node->next;
    }

    // if this node is not NULL, there are more values
    // in the list, not cool
    ASSERT(node == NULL);
}

void freeNodes(struct node *head)
{
    if (head != NULL) {
        freeNodes(head->next);
        free(head);
    }
}
