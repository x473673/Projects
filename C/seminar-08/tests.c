#define _POSIX_C_SOURCE 1

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

#define TESTING
#ifndef DEBUG
#  define TESTING_FORK_MODE
#endif
#define TESTING_MAIN
#include "testing.h"

//=============================================================================
//  Examples
//=============================================================================

/*
 * Trivial test that succeeds.
 */
TEST(trivial_success)
{
    int zero = 0;
    ASSERT(zero == 0);
}

/*
 * Trivial test that fails.
 */
TEST(trivial_failure)
{
    int zero = 0;
    ASSERT(zero == 1);
}

/*
 * Example of queueCreate test
 *
 * This test makes sure it is possible to create a queue of zero
 * capacity.
 */
TEST(queueCreate__zero_capacity)
{
    struct queue *queue;
    // the queueCreate should succeed
    ASSERT(queueCreate(&queue, sizeof(int), 0u));

    // queue should now point to allocated structure
    ASSERT(queue != NULL);

    // attributes should be set properly
    ASSERT(queue->element   == sizeof(int));
    ASSERT(queue->capacity  == 0u);
    ASSERT(queue->index     == 0u);
    ASSERT(queue->size      == 0u);
    // queue.memory may or may not be NULL, the documentation does not
    // specify this

    // well done, free the structure
    free(queue);
    // we didn't use queueDestroy since we are supposed to call only
    // one function from the queue interface
}

/**
 * Example of queueEnqueue test
 *
 * Scenario: the queue is initially empty and we try to enqueue a single
 * element
 */
TEST(queueEnqueue__single)
{
    int memory[32u]; // this simulates queue's internal memory
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 32u,          // capacity is same as array size
        .memory     = memory,       // fake internal memory
        // all other attributes not mentioned here will
        // be initialized to 0
    };

    // now let's enqueue a single element
    int number = 123456;
    // the function shall not fail
    ASSERT(queueEnqueue(&queue, &number));

    // check that the element was stored in the memory
    ASSERT(memory[0] == number);
    // make sure that size has increased
    ASSERT(queue.size == 1u);
    // index should remain 0
    ASSERT(queue.index == 0u);
}

//=============================================================================
//  Your tests go here
//=============================================================================


// ---------------*************--------------
// ---------------* SKUPINA 4 *--------------
// ---------------*************--------------

TEST(queueDequeue__Full_index_zero)
{
    const size_t len = 10;
    int memory[len]; // this simulates queue's internal memory

    for(size_t i = 0; i < len; i++)
    {
        memory[i] = (i+1) * 100;
    }

    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = len,          // capacity is same as array size
        .size       = len,          // is full
        .memory     = memory,       // fake internal memory
        // all other attributes not mentioned here will
        // be initialized to 0
    };


    // the elements
    int d = 7;
    for(size_t i = 0; i < len; i++)
    {
        ASSERT(queue.size == len - i);
        ASSERT(queue.index == i);
        ASSERT(queueDequeue(&queue, &d));
        ASSERT(d == (int)(i+1) * 100);
    }

    ASSERT(queue.index == 0);
    ASSERT(queue.size == 0);
    int oldD = d;
    ASSERT(queueDequeue(&queue, &d) == false);
    ASSERT(oldD == d);
    ASSERT(queue.index == 0);
    ASSERT(queue.size == 0);
}

TEST(queueDequeue__Full_index_nonzero)
{
    const size_t len = 1000;
    const size_t index_shift = 782;
    int memory[len]; // this simulates queue's internal memory

    for(size_t i = 0; i < len; i++)
    {
        memory[i] = (i+1) * 100;
    }

    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = len,          // capacity is same as array size
        .size       = len,          // is full
        .index      = index_shift,  // nonzero index
        .memory     = memory,       // fake internal memory
        // all other attributes not mentioned here will
        // be initialized to 0
    };

    // the elements
    int d = 7;
    for(size_t i = 0; i < len; i++)
    {
        ASSERT(queue.size == len - i);
        ASSERT(queue.index == (i + index_shift) % len);
        ASSERT(queueDequeue(&queue, &d));
        ASSERT(d == (int)((i+index_shift) % len + 1) * 100);
    }

    ASSERT(queue.index == index_shift);
    ASSERT(queue.size == 0);
    int oldD = d;
    ASSERT(queueDequeue(&queue, &d) == false);
    ASSERT(oldD == d);
    ASSERT(queue.index == index_shift);
    ASSERT(queue.size == 0);
}

TEST(queueDequeue__empty_doesnot_modify)
{
    int memory[32u]; // this simulates queue's internal memory
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 32u,          // capacity is same as array size
        .memory     = memory,       // fake internal memory
        .size       = 0,
        // all other attributes not mentioned here will
        // be initialized to 0
    };

    int data[] = {0};

    queueDequeue(&queue, data);
    ASSERT(data[0] == 0);
}

TEST(queueDequeue__empty_zero_capacity)
{
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 0u,          // capacity is same as array size
        .size       = 0,
        // all other attributes not mentioned here will
        // be initialized to 0
    };

    int data[] = {0};

    ASSERT(queueDequeue(&queue, data) == false);
    ASSERT(data[0] == 0);
}

TEST(queueDequeue__becomes_empty)
{
    int memory[] = {10}; // this simulates queue's internal memory
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 1u,          // capacity is same as array size
        .memory     = memory,       // fake internal memory
        .index      = 0u,
        .size       = 1
        // all other attributes not mentioned here will
        // be initialized to 0
    };

    int data[] = {0};

    ASSERT(queueDequeue(&queue, data) == true);
    ASSERT(queue.size == 0);
    ASSERT(queueDequeue(&queue, data) == false);
    ASSERT(queue.size == 0);
    ASSERT(data[0] == 10);
}


/**
 * Scenario: the queue is non-empty and we try to dequeue ten
 * element if data is NULL
 */
TEST(queueDequeue__singleElement__dataIsNULL)
{
    int memory[32u]; // this simulates queue's internal memory
    for(size_t i = 0; i < 16; i++)
        memory[i] = i * 1000u;
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 32u,           // capacity is same as array size
        .size       = 16u,           // there are 16 elements
        .index      = 0u,            // index points to 0
        .memory     = memory,       // fake internal memory
    };
    // the function shall not fail
    ASSERT(queueDequeue(&queue, NULL));
    // make sure that size has decreased
    ASSERT(queue.size == 15u);
    // index should increase by 1
    ASSERT(queue.index == 1u);
}


/**
 * Scenario: the queue is non-empty and we try to dequeue up to ten
 * elements if data is NULL
 */
TEST(queueDequeue__upToTenElements__dataIsNULL)
{
    int memory[32u]; // this simulates queue's internal memory
    for(size_t i = 0; i < 16; i++)
        memory[i] = i * 1000u;
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 32u,           // capacity is same as array size
        .size       = 16u,           // there are 16 elements
        .index      = 0u,            // index points to 0
        .memory     = memory,       // fake internal memory
    };
    for(size_t i = 0; i < 10; i++) {
        // the function shall not fail
        ASSERT(queueDequeue(&queue, NULL));
        // make sure that size has decreased by i
        ASSERT(queue.size == 16u - i);
        // index should increase by i
        ASSERT(queue.index == i);
    }
}


/**
 * Scenario: the queue is empty and we try to dequeue single
 * element if data is NULL
 */
TEST(queueDequeue__singleElement__dataIsNULL_qeueIsEmpty)
{
    int memory[32u]; // this simulates queue's internal memory
    struct queue queue = {          // queue initialization
        .element    = sizeof(int),  // element size
        .capacity   = 32u,          // capacity is same as array size
        .size       = 0u,           // there are no elements
        .index      = 0u,           // index points to 0
        .memory     = memory,       // fake internal memory
    };
    // the function shall fail
    ASSERT(!queueDequeue(&queue, NULL));
}

