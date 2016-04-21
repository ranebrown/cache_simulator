/**
 * @file        dlinkedlist.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for double linked list.
 */

#ifndef DLINKEDLIST_H
    #define DLINKEDLIST_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "common.h"

    /* #define DEBUG 1 */

    /**
     * @brief contains variables necessary for each node
     */
    struct node;
    /**
     * @brief typedef for the node structure (contains variables necessary for each node)
     */
    typedef struct node
    {
        short valid;        ///< marks if a block contains valid information
        short dirty;        ///< marks if a block has been written to
        ulli tag;           ///< the tag for a specific address
        struct node *next;  ///< pointer to the next node in the linked list
        struct node *prev;  ///< pointer to the previous node in the linked list
    } node;

    /**
     * @brief contains variables necessary for lists
     */
    typedef struct{
        node *first;    ///< pointer to the first node in the linked list
        node *last;     ///< pointer to the last node in the linked list
        int nodeCount;  ///< the number of nodes in the linked list
        int maxSize;    ///< the max size of the linked list
    }list;

    /**
     * @brief initilizes a new list
     * @param[in] maxSize the maximum size that the list can be
     * @return A pointer to the newly created list
     */
    list *initList(int maxSize);

    /**
     * @brief Puts a new node at the beginning of the list
     * @param[in] q list the list in which to add the new node
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int putFirst(list *q);

    /**
     * @brief Puts a new node at the end of the list
     * @param[in] q the list in which to add the new node
     * @param[in] tag the tag of node to be added
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int putLast(list *q, ulli tag);

    /**
     * @brief Removes the node at the beginning of the list
     * @param[in] q the list in which to add the new node
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int removeFirst(list *q);

    /**
     * @brief Removes the node at the end of the list
     * @param[in] q the list in which to add the new node
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int removeLast(list *q);

    /**
     * @brief bumps tagged node to front of list
     * @param[in] q the list
     * @param[in] tag the tag of node to bump to first
     * @return -1 error, 0 operation successful, 1 tag not found
     */
    int bumpToFirst(list *q, ulli tag);

    /**
     * @brief determines if the list is empty
     * @param[in] q the list in question
     * @return 1 if empty, 0 if not empty, -1 if error
     */
    int isEmpty(list *q);

    /**
     * @brief determines if the list is full
     * @param[in] q the list in question
     * @return 1 if full, 0 if not full, -1 if error
     */
    int isFull(list *q);

    /**
     * @brief prints out the entire list
     * @param[in] q the list to print
     */
    void printList(list *q);

    /**
     * @brief Deletes the entire list and every node still allocated
     * @param[in] q the list to delete
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int deleteList(list *q);


#endif // DLINKEDLIST_H
