#include <assert.h>
#include <stdio.h>  // this header is only used for NOT_IMPLEMENTED
                    // you may remove it afterwards

#include "list.h"
#include "list_utils.h"

//--  REMOVE THE FOLLOWING MACROS WHEN DONE  ----------------------------------

// This is a common way to say that some parameter is not used.
#define UNUSED(VAR) ((void) VAR)

// This function prints an error message to standard error output
// that the function called is not implemented and returns some default value.
#ifdef DEBUG
#  define EXIT_TEST(VALUE) return VALUE
#else
#  define EXIT_TEST(VALUE) abort()
#endif

#define NOT_IMPLEMENTED(VALUE)                                              \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        EXIT_TEST(VALUE);                                                   \
    } while (0)

//-----------------------------------------------------------------------------

/*
 * You may want to add auxiliary functions here.
 *
 * The best way to declare such functions is to use the 'static' keyword,
 * like
 *
 *      static void listSwapNodes(...)
 *      {
 *          // ...
 *      }
 */

bool listAny(struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    for (struct node *node = list -> head; node; node = node -> next) {
        if(p(node -> data))
            return true;
    }
    return false;
}

bool listAll(struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    for (struct node *node = list -> head; node; node = node -> next) {
        if(!p(node -> data))
            return false;
    }
    return true;
}

bool listInsert(struct list *list, size_t index, void *data)
{
    if((list == NULL) || (data == NULL)) {
        return false;
    }

    if(index == 0) {
        listUnshift(list, data);
        return true;
    }

    struct node *node = list -> head;
    if(!node)
        return false;

    for (size_t i = 1; i < index; i++) {
        node = node -> next;
        if(!node)
            return false;
    }

    struct node *newNode = malloc(sizeof(*newNode));
    newNode -> data = data;
    newNode -> prev = node;
    newNode -> next = node -> next;
    if(node -> next)
        node -> next -> prev = newNode;
    else
        list -> tail = newNode;
    node -> next = newNode;
    return true;
}


void *listGet(struct list *list, size_t index)
{
    assert(list != NULL);

    struct node *node = list -> head;

    for (size_t i = 0; i < index; i++) {
        if(!node)
            return NULL;
        node = node -> next;
    }
    if(!node)
        return NULL;
    return node -> data;
}

int listGetIndex(struct list *list, void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    int index = 0;
    for (struct node *node = list -> head; node; node = node -> next) {
        index++;
        if(node -> data = data)
            return index;
    }
    return NULL;
}

void *listRemove(struct list *list, size_t index)
{

    if(list == NULL) {
        return NULL;
    }

    if(index == 0) {
        return listShift(list);
    }

    struct node *node = list -> head;
    if(!node)
        return NULL;

    for (size_t i = 1; i < index; i++) {
        node = node -> next;
        if(!node)
            return NULL;
    }

    if(!(node -> next))
        return NULL;

    void *data = node -> next -> data;
    free(node -> next);
    node -> next = node -> next -> next;
    if(node -> next)
        node -> next -> prev = node;
    else
        list -> tail = node;
    return data;
}

void* listFindFirst(struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    for (struct node *node = list -> head; node; node = node -> next) {
        if(p(node -> data))
            return node;
    }
    return NULL;
}

void* listFindLast(struct list *list, predicate p)
{
    UNUSED(list);
    UNUSED(p);
    NOT_IMPLEMENTED(NULL);
}

void listForEach(struct list *list, action f)
{
    UNUSED(list);
    UNUSED(f);
    NOT_IMPLEMENTED();
}

void listForEachReverse(struct list *list, action f)
{
    UNUSED(list);
    UNUSED(f);
    NOT_IMPLEMENTED();
}

void listSort(struct list *list, comparator cmp)
{
    UNUSED(list);
    UNUSED(cmp);
    NOT_IMPLEMENTED();
}
