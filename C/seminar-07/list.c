#include <assert.h>
#include <stdio.h>  // this header is only used for NOT_IMPLEMENTED
                    // you may remove it afterwards

#include "list.h"

//--  REMOVE THE FOLLOWING MACROS WHEN DONE  ----------------------------------

// This is a common way to say that some parameter is not used.
#define UNUSED(VAR) ((void) VAR)

// This function prints an error message to standard error output
// that the function called is not implemented and returns some default value.

// __builtin_unreachable is an GCC extension that will tell the compiler
// that the function shall never return
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

void listInitialize(struct list *list, deallocator dealloc)
{
    // you may add checks like this to the following functions as well
    assert(list != NULL);

    list->head = NULL;
    list->tail = NULL;
    list->dealloc = dealloc;
}

void listClear(struct list *list)
{
    if(!list -> dealloc)
        return;
    while(list -> tail) {
        list -> dealloc(listPop(list));
    }
}

size_t listSize(const struct list *list)
{
    assert(list != NULL);

    struct node *node = list -> head;
    size_t size = 0;
    while(node) {
        size++;
        node = node -> next;
    }
    return size;
}

bool listIsEmpty(const struct list *list)
{
    assert(list != NULL);

    return !(list -> head);
}

bool listPush(struct list *list, void *data)
{

    if((list == NULL) || (data == NULL)) {
        return false;
    }

    struct node *node = malloc(sizeof(*node));
    if(node == NULL) {
        return false;
    }

    node -> prev = list -> tail;
    node -> next = NULL;
    node -> data = data;

    if(list -> head == NULL) {
        list -> head = node;
    } else {
        list -> tail -> next = node;\
    }

    list -> tail = node;

    return true;
}

void *listPop(struct list *list)
{
    if((!list -> head) || (!list))
        return NULL;

    struct node *node = list -> tail;
    void *data = node -> data;

    if(node -> prev)
        node -> prev -> next = NULL;
    else
        list -> head = NULL;
    list -> tail = node -> prev;
    free(node);
    return data;
}

bool listUnshift(struct list *list, void *data)
{
    if((list == NULL) || (data == NULL)) {
        return false;
    }

    struct node *node = malloc(sizeof(*node));
    if(node == NULL) {
        return false;
    }

    node -> next = list -> head;
    node -> prev = NULL;
    node -> data = data;

    if(list -> tail == NULL) {
        list -> tail = node;
    } else {
        list -> head -> prev = node;\
    }

    list -> head = node;

    return true;
}

void *listShift(struct list *list)
{
    if((!list -> tail) || (!list))
        return NULL;

    struct node *node = list -> head;
    void *data = node -> data;

    if(node -> next)
        node -> next -> prev = NULL;
    else
        list -> tail = NULL;
    list -> head = node -> next;
    free(node);
    return data;
}
