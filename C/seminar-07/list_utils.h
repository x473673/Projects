#ifndef LIST_UTILS_H
#define LIST_UTILS_H

/**
 * \file   list_utils.h
 * \author ...
 */

#include <stdbool.h>
#include "list.h"

//=============================================================================
//  Types
//=============================================================================

/**
 * \brief Predicate.
 */
typedef bool (*predicate)(void*);

/**
 * \brief Comparator.
 *
 * Let a1 &lt; a2 denote that argument 1 should be before argument 2 in the
 * ordering implemented by this function; then the comparator returns number
 * <ul>
 *     <li> &lt; 0 if a1 &lt; a2</li>
 *     <li> &gt; 0 if a1 &gt; a2</li>
 *     <li> 0 otherwise </li>
 * </ul>
 */
typedef int (*comparator)(void*, void*);

/**
 * \brief Action.
 */
typedef void (*action)(void*);

//=============================================================================
//  List predicates
//=============================================================================

/**
 * \brief Returns \c true if at least one element satisfies the predicate \p p.
 *
 * \param list  the list
 * \param p     the predicate
 *
 * \note In empty list there is no element that satisfies \p p.
 */
bool listAny(struct list *list, predicate p);

/**
 * \brief Returns \c false if at least one element does not satisfy
 * the predicate \p p.
 *
 * \param list  the list
 * \param p     the predicate
 *
 * \note In empty list there is no element that does not satisfy \p p.
 */
bool listAll(struct list *list, predicate p);

//=============================================================================
//  Index-based functions
//=============================================================================

/**
 * \brief Inserts a new element at position specified by \p index from the head.
 *
 * The original element at the specified index will be moved after the new one.
 *
 * \param list  the list
 * \param index distance from list's head
 * \param data  pointer to store
 *
 * \note If \p index is \c listSize(&list), then the new element
 * will be appended after the tail.
 *
 * \return \c true if the operation was successful
 */
bool listInsert(struct list *list, size_t index, void *data);

/**
 * \brief Returns the element at the position \p index
 * or \c NULL if no such element exists.
 *
 * \param list  the list
 * \param index distance from list's head
 * \return Element or \c NULL if not found.
 */
void *listGet(struct list *list, size_t index);

/**
 * \brief Finds the first index of the specified element in the list.
 *
 * \param list  the list
 * \param data  the element to search
 * \return Index in the list or -1 if not found.
 */
int listGetIndex(struct list *list, void *data);

/**
 * \brief Removes and returns the element at position \p index
 * or \c NULL if no such element exists.
 *
 * \param list  the list
 * \param index distance from list's head
 * \return Element or \c NULL if not found.
 */
void *listRemove(struct list *list, size_t index);

//=============================================================================
//  Search functions
//=============================================================================

/**
 * Returns the the first element that satisfies predicate \p p
 * or \c NULL if no such element exists.
 *
 * \param list  the list
 * \param p     the predicate
 */
void *listFindFirst(struct list *list, predicate p);

/**
 * Returns the the last element that satisfies predicate \p p
 * or \c NULL if no such element exists.
 *
 * \param list  the list
 * \param p     the predicate
 */
void *listFindLast(struct list *list, predicate p);

//=============================================================================
//  Enumeration
//=============================================================================

/**
 * \brief Calls function \p f on each element from head to tail.
 *
 * \param list  the list
 * \param f     the function to call
 */
void listForEach(struct list *list, action f);

/**
 * \brief Calls function \p f on each element from tail to head.
 *
 * \param list  the list
 * \param f     the function to call
 */
void listForEachReverse(struct list *list, action f);

//=============================================================================
//  Sorting
//=============================================================================

/**
 * \brief Sorts all elements in the list using \p cmp comparator.
 *
 * \param list  the list
 * \param cmp   the comparator
 */
void listSort(struct list *list, comparator cmp);

#endif // LIST_UTILS_H
