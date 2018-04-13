#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <string.h>

#include "list.h"
#include "list_utils.h"

#define TESTING
#define TESTING_MAIN
#include "testing.h"
#include "test_utils.h"
#include "list_utils.h"

//=============================================================================
//  Callbacks
//=============================================================================

static bool isEven(void *number)
{
    return *((int*) number) % 2 == 0;
}

static bool isOdd(void *number)
{
    return *((int*) number) % 2 != 0;
}

static bool isZero(void *number)
{
    return *((int*) number) == 0;
}

/* if called multiple times, saves all arguments in a single value
 * as a polynomial
 *
 * example:
 *     a = 1; r = 0;
 *     poly(1); poly(2); poly(3)
 *
 *     r == 123
 */
static int a;
static int r;

static void poly(void *n)
{
    r += (a * *((int*) n));
    a *= 10;
}

// integral comparator for listSort
static int cmpnum(void *a, void *b)
{
    int *na = (int*) a;
    int *nb = (int*) b;

    return (*na) - (*nb);
}

//=============================================================================
//  Tests
//=============================================================================

//--  listAny  ----------------------------------------------------------------

TEST(listAny__empty)
{
    struct list list;
    listInitialize(&list, NULL);

    // there is no element in empty list that matches the predicate
    ASSERT(!listAny(&list, &isZero));
    listClear(&list);
}

TEST(listAny__true)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 0, 0, 0, 0, 1, 0 };
    for (int i = 0; i < 6; ++i)
        listPush(&list, numbers + i);

    ASSERT(listAny(&list, &isOdd));
    listClear(&list);
}

TEST(listAny__false)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 3, 5, 7, 9 };
    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    ASSERT(!listAny(&list, &isEven));
    listClear(&list);;
}

//--  listAll  ----------------------------------------------------------------

TEST(listAll__empty)
{
    struct list list;
    listInitialize(&list, NULL);

    // there is no element in the list that DOES NOT match the predicate
    ASSERT(listAll(&list, &isEven));
    listClear(&list);
}

TEST(listAll__true)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 0, 0, 0 };
    for (int i = 0; i < 3; ++i)
        listPush(&list, numbers + i);

    ASSERT(listAll(&list, &isZero));
    listClear(&list);
}

TEST(listAll__false)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 3, 5, 6, 7 };
    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    ASSERT(!listAll(&list, &isOdd));
    listClear(&list);
}

//--  listInsert  -------------------------------------------------------------

TEST(listInsert__begin)
{
    struct list list;
    listInitialize(&list, NULL);
    int numbers[] = { 0, 1, 2, 3 };
    for (int i = 1; i < 4; ++i)
        listPush(&list, numbers + i);

    ASSERT(listInsert(&list, 0, numbers));
    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 4, numbers);
    listClear(&list);
}

TEST(listInsert__end)
{
    struct list list;
    listInitialize(&list, NULL);
    int numbers[] = { 0, 1, 2, 3 };
    for (int i = 0; i < 3; ++i)
        listPush(&list, numbers + i);

    ASSERT(listInsert(&list, 3, numbers + 3));
    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 4, numbers);
    listClear(&list);
}

TEST(listInsert__middle)
{
    struct list list;
    listInitialize(&list, NULL);
    int numbers[] = { -2, -1, 0, 1, 2 };
    for (int i = 0; i < 5; ++i) {
        if (i != 2)
            listPush(&list, numbers + i);
    }

    ASSERT(listInsert(&list, 2, numbers + 2));
    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 5, numbers);
    listClear(&list);
}

//--  listGet  ----------------------------------------------------------------

TEST(listGet)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    for (int i = 0; i < 6; ++i) {
        void *address = (i < 5) ? numbers + i : NULL;
        ASSERT(listGet(&list, i) == address);
    }

    listClear(&list);
}

//--  listRemove  -------------------------------------------------------------

TEST(listRemove)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 2, 3 };
    int dummy     = 42;

    for (int i = 0; i < 7; ++i) {
        if (i % 2)
            listPush(&list, numbers + ((i - 1) / 2));
        else
            listPush(&list, &dummy);
    }

    // the content of the list is [42, 1, 42, 2, 42, 3, 42]

    // let's get rid of 42s, that have indices 0 2 4 6
    // but after each listRemove, indices of remaining 42s 'move' so we
    // actually need to remove 0 1 2 3
    for (int i = 0; i < 4; ++i)
        ASSERT(listRemove(&list, i) == &dummy);

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 3, numbers);
    listClear(&list);
}

//--  listFindFirst  ----------------------------------------------------------

TEST(listFindFirst__noMatch)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 2, 3 };

    for (int i = 0; i < 3; ++i)
        listPush(&list, numbers + i);

    ASSERT(listFindFirst(&list, &isZero) == NULL);
    listClear(&list);
}

TEST(listFindFirst)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 0, 2, 0, 3 };

    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    ASSERT(listFindFirst(&list, &isZero) == list.head->next->data);
    listClear(&list);
}

//--  listFindLast  -----------------------------------------------------------

TEST(listFindLast__noMatch)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 2, 3 };

    for (int i = 0; i < 3; ++i)
        listPush(&list, numbers + i);

    ASSERT(listFindLast(&list, &isZero) == NULL);
    listClear(&list);
}

TEST(listFindLast)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 0, 2, 0, 3 };

    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    ASSERT(listFindLast(&list, &isZero) == list.tail->prev->data);
    listClear(&list);
}

//--  listForEach  ------------------------------------------------------------

TEST(listForEach)
{
    a = 1;
    r = 0;

    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 3, 7, 2, 1 };

    for (int i = 0; i < 4; ++i)
        listPush(&list, numbers + i);

    listForEach(&list, &poly);
    ASSERT(r == 1273);
    listClear(&list);
}

//--  listForEachReverse  -----------------------------------------------------

TEST(listForEachReverse)
{
    a = 1;
    r = 0;

    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 1, 3, 0, 4, 9 };

    for (int i = 0; i < 5; ++i)
        listPush(&list, numbers + i);

    listForEachReverse(&list, &poly);
    ASSERT(r == 13049);
    listClear(&list);
}

//--  listSort  ---------------------------------------------------------------

TEST(listSort)
{
    struct list list;
    listInitialize(&list, NULL);

    int numbers[] = { 6, 7, 2, 3, 8, 1, 9, 4, 0, 5 };
    int ordered[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 10; ++i)
        listPush(&list, numbers + i);

    listSort(&list, &cmpnum);

    ASSERT_LIST_INTEGRITY(&list);
    ASSERT_LIST_CONTENT(&list, 10, ordered);
    listClear(&list);
}
