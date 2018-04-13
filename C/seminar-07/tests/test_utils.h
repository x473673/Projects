#ifndef TEST_UTILS_H
#define TEST_UTILS_H

/**
 *  @file   test_utils.h
 *  @author Roman Lacko <xlacko1@fi.muni.cz>
 */

#include "list.h"
#include "testing.h"

// convenience macros to imitate ASSERT_*
#define ASSERT_LIST_INTEGRITY assertListIntegrity
#define ASSERT_LIST_CONTENT   assertListContent

// why stop at ASSERT_* macros?
#define DESTROY_LIST_RAW      freeNodes

/**
 * @brief Prints the error and calls @c abort.
 *
 * @param str   error message to print
 */
void terminate(const char *str);

/**
 * @brief Checks that the list is sound.
 *
 * @param list  list to check
 */
void assertListIntegrity(struct list *list);

/**
 * @brief Checks that the list contains the specified values.
 *
 * @note Call @c assertListIntegrity before this function.
 *
 * @param list  list to check
 * @param size  number of expected integers
 * @param data  array of expected integers
 */
void assertListContent(struct list *list, size_t size, int *data);

/**
 * @brief Deletes the chain of nodes.
 *
 * @param head  head of the list
 */
void freeNodes(struct node *head);

#endif // TEST_UTILS_H
