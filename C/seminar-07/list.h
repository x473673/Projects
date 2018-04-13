#ifndef LIST_H
#define LIST_H

/**
 * \file   list.h
 * \author ...
 */

#include <stdlib.h>
#include <stdbool.h>

//=============================================================================
//  Types
//=============================================================================

/**
 * \brief Type of functions that take a pointer in order to free it.
 */
typedef void (*deallocator)(void*);

/**
 * \brief Doubly linked list node.
 */
struct node
{
    struct node *prev; /**< previous node        */
    struct node *next; /**< next node            */
    void        *data; /**< pointer to node data */
};

/**
 * \brief Doubly linked list.
 */
struct list
{
    struct node *head; /**< list's first node */
    struct node *tail; /**< list's last node  */

    deallocator dealloc; /**< deallocator for \c listClear */
};

//=============================================================================
//  Consistency requirements
//=============================================================================

/*
 * Let P be a property that a list has if and only if it satisfies
 * the following requirements:
 *
 * A) list head is NULL if and only if the tail is NULL,
 * B) if head is not NULL, then head->prev is NULL,
 * C) if tail is not NULL, then tail->next is NULL,
 * D) data pointer of any node is not NULL
 *
 * Each of the following functions must satisfy this condition:
 *     If the function's argument is a list with property P, then
 *     the list has the property P after the function ends.
 */

//=============================================================================
//  Functions
//=============================================================================

/* ------------------------------  NOTE  --------------------------------------
 *
 * Unless stated otherwise, NULL value passed as a parameter to any of
 * the following functions causes undefined behaviour. This is not tested
 * by the included tests.
 */

/**
 * \brief Initializes the list structure.
 *
 * The result of this operation is an empty list.
 *
 * \param list      pointer to the \c list structure
 * \param dealloc   pointer to a function of the type \a deallocator
 */
void listInitialize(struct list *list, deallocator dealloc);

/**
 * \brief Removes all nodes.
 *
 * Calls \a list->dealloc on \c data pointer of each node.
 * The result of this operation is an empty list.
 *
 * \param list  pointer to the \c list structure
 */
void listClear(struct list *list);

/**
 * \brief Returns the number of elements stored in the list.
 *
 * \param list  pointer to the \c list structure
 */
size_t listSize(const struct list *list);

/**
 * \brief Predicate that tells wheter the \a list is empty or not.
 *
 * \param list pointer to the \c list structure
 * \return \c true if the \a list is empty, \c false otherwise
 */
bool listIsEmpty(const struct list *list);

/**
 * \brief Inserts a new element after the last element in the list.
 *
 * \param list  pointer to the \c list structure
 * \param data  pointer to be stored
 * \return \c true if the operation was successful, \c false otherwise
 *
 * \note If \p data is \c NULL, the operation fails.
 */
bool listPush(struct list *list, void *data);

/**
 * \brief Removes and returns the last element stored in the list.
 *
 * \param list pointer to the \c list structure
 * \return a pointer from the last node or \c NULL if operation failed.
 *
 * \note If \p list is empty, the operation fails.
 */
void *listPop(struct list *list);

/**
 * \brief Inserts a new element before the first element in the list.
 *
 * \param list  pointer to the \c list structure
 * \param data  pointer to be stored
 * \return \c true if the operation was successful, \c false otherwise
 *
 * \note If \p data is \c NULL, the operation fails.
 */
bool listUnshift(struct list *list, void *data);

/**
 * \brief Removes and returns the first element stored in the list.
 *
 * \param list  pointer to the \c list structure
 * \return a pointer from the first node or \c NULL if operation failed.
 *
 * \note If \p list is empty, the operation fails.
 */
void *listShift(struct list *list);

#endif // LIST_H
