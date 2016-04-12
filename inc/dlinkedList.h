/**
 * @file        linkedlist.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for double linked list.
 */

#ifndef DLINKEDLIST_H
    #define DLINKEDLIST_H

    #include <stdio.h>
    #include <stdlib.h>

    #define DEBUG 1

    typedef unsigned long long int ulli;    ///< shorten long type

    /**
     * @brief contains variables necessary for each node
     */
    struct node;
    typedef struct node
    {
        short valid;
        short dirty;
        ulli tag;
        struct node *next;
        struct node *prev;
    } node;

    /**
     * @brief contains variables necessary for lists
     */
    typedef struct{
        node *first; //not nodes, just pointers to the first and last nodes
        node *last;
        int nodeCount;
        int maxSize;
    }list;

    /**
     * @brief initilizes a new list
     * @param[in] the maximum size that the list can be
     * @return A pointer to the newly created list
     */
    list *initList(int maxSize);

    /**
     * @brief Puts a new node at the beginning of the list
     * @param[in] the list in which to add the new node
     * @param[in] the tag of node to be added
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int putFirst(list *q);

    /**
     * @brief Puts a new node at the end of the list
     * @param[in] the list in which to add the new node
     * @param[in] the tag of node to be added
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int putLast(list *q, ulli tag);

    /**
     * @brief Removes the node at the beginning of the list
     * @param[in] the list in which to add the new node
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int removeFirst(list *q);

    /**
     * @brief Removes the node at the end of the list
     * @param[in] the list in which to add the new node
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int removeLast(list *q);

    /**
     * @brief bumps tagged node to front of list
     * @param[in] the list
     * @param[in] the tag of node to bump to first
     * @return -1 error, 0 operation successful, 1 tag not found
     */
    int bumpToFirst(list *q, ulli tag);

    // /**
    //  * @brief replaces node 'tag' with node 'newTag'
    //  * @param[in] the list
    //  * @param[in] the tag of node to remove
    //  * @param[in] the tag of node to input
    //  * @return -1 error, 0 operation successful, 1 tag not found
    //  */
    // int replaceNode(list *q, ulli tag, ulli newTag);


    /**
     * @brief determines if the list is empty
     * @param[in] the list in question
     * @return 1 if empty, 0 if not empty, -1 if error
     */
    int isEmpty(list *q);

    /**
     * @brief determines if the list is full
     * @param[in] the list in question
     * @return 1 if full, 0 if not full, -1 if error
     */
    int isFull(list *q);

    /**
     * @brief prints out the entire list
     * @param[in] the list to print
     */
    void printList(list *q);

    /**
     * @brief Deletes the entire list and every node still allocated
     * @param[in] the list to delete
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int deleteList(list *q);


#endif
