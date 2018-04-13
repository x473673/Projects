#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <string.h>

#include "list.h"
#include "list_utils.h"

#define TESTING
#ifndef DEBUG
#  define TESTING_FORK_MODE
#endif
#define TESTING_MAIN
#include "testing.h"
#include "test_utils.h"

//=============================================================================
//  Callbacks
//=============================================================================

static int counter     = 0;
static int testvalue   = 0;

// increases counter after each call and
// tests that the node's value is testvalue
static void incCounter(void *dummy)
{
    int *num = (int*) dummy;

    ASSERT(*num == testvalue);
    ++counter;
}

//=============================================================================
//  Tests
//=============================================================================

//--  listInitialize  ---------------------------------------------------------

TEST(listInitialize)
{
    // this test makes sure that listInitialize initializes
    // head and tail to NULL
    struct list list = { (struct node*)(42), (struct node*)(666), &free };
    listInitialize(&list, NULL);

    ASSERT(list.head == NULL);
    ASSERT(list.tail == NULL);
    ASSERT(list.dealloc == NULL);

    // check that the function sets dealloc to &free
    listInitialize(&list, &free);
    ASSERT(list.dealloc == &free);
}

//--  listClear  --------------------------------------------------------------

TEST(listClear__empty)
{
    struct list list = { NULL, NULL, &free };

    // this should just end without SIGSEGV nor other bad stuff
    listClear(&list);
}

TEST(listClear)
{
    int num = 42;
    struct node *nodes[3];

    // create 3 nodes
    for (int i = 0; i < 3; ++i) {
        nodes[i] = malloc(sizeof(struct node));

        if (nodes[i] == NULL)
            terminate("malloc() failed");
    }

    // 'entangle' links and set data
    for (int i = 0; i < 3; ++i) {
        nodes[i]->data = &num;
        nodes[i]->next = i < 2 ? nodes[i + 1] : NULL;
        nodes[i]->prev = i > 0 ? nodes[i - 1] : NULL;
    }

    struct list list = { nodes[0], nodes[2], &incCounter };

    counter   = 0;
    testvalue = 42;
    listClear(&list);

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 0, NULL);
    ASSERT(counter == 3);
}

//--  listSize  ---------------------------------------------------------------

TEST(listSize__empty)
{
    struct list list = { NULL, NULL, NULL };
    ASSERT(listSize(&list) == 0U);
}

TEST(listSize)
{
    int dummy = 90210;

    // try lists of length 1 to 30
    for (int size = 1; size < 30; ++size) {
        // create an array of nodes
        struct node *nodes = malloc(size * sizeof(struct node));

        // 'entangle' nodes and set data
        for (int i = 0; i < size; ++i) {
            nodes[i].data = &dummy;
            nodes[i].next = i < size - 1 ? nodes + i + 1 : NULL;
            nodes[i].prev = i > 0        ? nodes + i - 1 : NULL;
        }

        struct list list = { nodes, nodes + size - 1, NULL };
        ASSERT(listSize(&list) == (size_t) size);
        free(nodes);
    }
}

//--  listIsEmpty  ------------------------------------------------------------

TEST(listIsEmpty__whenItIsEmpty)
{
    struct list list = { NULL, NULL, NULL };
    ASSERT(listIsEmpty(&list));
}

TEST(listIsEmpty__whenItIsInFactNotEmptyAtAll)
{
    struct node node;
    node.next = node.prev = NULL;
    node.data = &node;

    struct list list = { &node, &node, NULL };

    ASSERT(!listIsEmpty(&list));
}

TEST(listIsEmpty__makeSureThatListSizeIsNotUsed)
{
    // this test makes sure listIsEmpty does not use
    // listSize (if it's correctly implemented)
    struct node h, s, t;

    // make head and tail point to a single node s
    // where s behaves like a 'sink' (it points to itself)
    h.prev = t.next = NULL;
    h.next = t.prev = s.next = s.prev = &s;
    h.data = t.data = s.data = &s;

    // the test will fail if listSize is called on this abomination
    struct list list = { &h, &t, NULL };
    // .. well, OK, it will not fail, it will not end at all

    // BUT you can solve halting problem in your free time and
    // uncomment the following line:
    //ASSERT(willHalt(&listIsEmpty, &list));

    ASSERT(!listIsEmpty(&list));
}

//--  listPush  ---------------------------------------------------------------

TEST(listPush__NULL)
{
    struct list list = { NULL, NULL, NULL };

    ASSERT(!listPush(&list, NULL));

    // list remains unmodified
    ASSERT(!list.head);
    ASSERT(!list.tail);
    ASSERT(!list.dealloc);
}

TEST(listPush__empty)
{
    struct list list = { NULL, NULL, NULL };
    int randomNumber = 2; // It changed, see? It's guaranteed to be random.

    ASSERT(listPush(&list, &randomNumber));

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 1, &randomNumber);

    DESTROY_LIST_RAW(list.head);
}

TEST(listPush__singleElement)
{
    int nums[4] = { 10, 11, 12, 13 };
    struct node *nodes[3];

    // create 3 nodes
    for (int i = 0; i < 3; ++i) {
        nodes[i] = malloc(sizeof(struct node));

        if (nodes[i] == NULL)
            terminate("malloc() failed");
    }

    // set first 3 elements of nums as values
    for (int i = 0; i < 3; ++i) {
        nodes[i]->data = nums + i;
        nodes[i]->next = i < 2 ? nodes[i + 1] : NULL;
        nodes[i]->prev = i > 0 ? nodes[i - 1] : NULL;
    }

    struct list list = { nodes[0], nodes[2], NULL };

    // push the last value to the list
    ASSERT(listPush(&list, nums + 3));

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 4, nums);

    for (int i = 0; i < 3; ++i)
        free(nodes[i]);

    free(list.tail);
}

TEST(listPush__manyElements)
{
    struct list list = { NULL, NULL, NULL };

    int nums[6] = { 2, 4, 8, 16, 32, 64 };

    for (int i = 0; i < 6; ++i)
        ASSERT(listPush(&list, nums + i));

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 6, nums);

    DESTROY_LIST_RAW(list.head);
}

//--  listPop  ----------------------------------------------------------------

TEST(listPop__empty)
{
    struct list list = { NULL, NULL, NULL };
    ASSERT(!listPop(&list));
}

TEST(listPop__single)
{
    int data = 123;
    struct node *node = malloc(sizeof(struct node));

    node->data = &data;
    node->next = node->prev = NULL;

    struct list list = { node, node, NULL };
    ASSERT(listPop(&list) == &data);

    // listShift should not modify data
    ASSERT(data == 123);

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 0, NULL);
}

TEST(listPop__many)
{
    int nums[5] = { 8, 6, 4, 2, 0 };

    struct node *nodes[5];

    // create 5 nodes
    for (int i = 0; i < 5; ++i) {
        nodes[i] = malloc(5 * sizeof(struct node));

        if (nodes[i] == NULL)
            terminate("malloc() failed");

        nodes[i]->data = &nums[i];
    }

    // entangle links
    for (int i = 0; i < 5; ++i) {
        nodes[i]->next = i < 4 ? nodes[i + 1] : NULL;
        nodes[i]->prev = i > 0 ? nodes[i - 1] : NULL;
    }

    struct list list = { nodes[0], nodes[4], NULL };
    for (int i = 0; i < 5; ++i) {
        ASSERT(listPop(&list) == nums + (4 - i));
        ASSERT(nums[4 - i] == 2 * i);

        ASSERT_LIST_INTEGRITY(&list);
        ASSERT_LIST_CONTENT(&list, 4 - i, nums);
    }
}

//--  listUnshift  ------------------------------------------------------------

TEST(listUnshift__NULL)
{
    struct list list = { NULL, NULL, NULL };

    ASSERT(!listUnshift(&list, NULL));

    // list remains unmodified
    ASSERT(list.head == NULL);
    ASSERT(list.tail == NULL);
    ASSERT(list.dealloc == NULL);
}

TEST(listUnshift__empty)
{
    struct list list = { NULL, NULL, NULL };
    int randomNumber = 3; // nobody would expect this

    ASSERT(listUnshift(&list, &randomNumber));

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 1, &randomNumber);

    DESTROY_LIST_RAW(list.head);
}

TEST(listUnshift__singleElement)
{
    int nums[4] = { 3, 4, 5, 6 };
    struct node *nodes[3];

    // create 3 nodes
    for (int i = 0; i < 3; ++i) {
        nodes[i] = malloc(sizeof(struct node));

        if (nodes[i] == NULL)
            terminate("malloc() failed");
    }

    // add values and indices 1 to 3 (skip 0)
    for (int i = 0; i < 3; ++i) {
        nodes[i]->data = nums + i + 1;
        nodes[i]->next = i < 2 ? nodes[i + 1] : NULL;
        nodes[i]->prev = i > 0 ? nodes[i - 1] : NULL;
    }

    struct list list = { nodes[0], nodes[2], NULL };

    // add 0th element
    ASSERT(listUnshift(&list, nums));

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 4, nums);

    for (int i = 0; i < 3; ++i)
        free(nodes[i]);

    free(list.head);
}

TEST(listUnshift__manyElements)
{
    struct list list = { NULL, NULL, NULL };

    int nums[6] = { 2, 3, 5, 7, 11, 13 };

    for (int i = 5; i >= 0; --i) {
        ASSERT(listUnshift(&list, nums + i));
    }

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 6, nums);

    DESTROY_LIST_RAW(list.head);
}

//--  listShift  --------------------------------------------------------------

TEST(listShift__empty)
{
    struct list list = { NULL, NULL, NULL };
    ASSERT(!listShift(&list));
}

TEST(listShift__single)
{
    int     data = 123;
    struct node *node = malloc(sizeof(struct node));

    node->data = &data;
    node->next = node->prev = NULL;

    struct list list = { node, node, NULL };
    ASSERT(listShift(&list) == &data);

    // listShift should not modify data
    ASSERT(data == 123);

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 0, NULL);
}

TEST(listShift__many)
{
    int nums[5] = { 5, 10, 15, 20, 25 };

    struct node *nodes[5];

    // create 5 nodes
    for (int i = 0; i < 5; ++i) {
        nodes[i] = malloc(5 * sizeof(struct node));

        if (nodes[i] == NULL)
            terminate("malloc() failed");

        nodes[i]->data = &nums[i];
    }

    // 'entangle' links
    for (int i = 0; i < 5; ++i) {
        nodes[i]->next = i < 4 ? nodes[i + 1] : NULL;
        nodes[i]->prev = i > 0 ? nodes[i - 1] : NULL;
    }

    struct list list = { nodes[0], nodes[4], NULL };
    for (int i = 0; i < 5; ++i) {
        ASSERT(listShift(&list) == nums + i);
        ASSERT(nums[i] == 5 * (i + 1));

        ASSERT_LIST_INTEGRITY(&list);
        ASSERT_LIST_CONTENT(&list, 4 - i, nums + i + 1);
    }
}
