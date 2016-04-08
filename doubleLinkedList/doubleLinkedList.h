/**
 * @file        linkedlist.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for double linked list.
 */

#ifndef DOUBLELINKEDLIST_H
    #define DOUBLELINKEDLIST_H

    #include <stdio.h>
    #include <stdlib.h>

    #define DEBUG 1

    typedef unsigned long long int ulli;

    typedef struct _node node;
    struct _node{
        short valid;
        short dirty;
        ulli tag;
        node *next;
        node *prev;
    };

    typedef struct{
        node *first; //not nodes, just pointers to the first and last nodes
        node *last;
        int nodeCount;
        int maxSize;
    }list;


    list *initList();

    int putFirst(list *q, ulli tag);

    int putLast(list *q, ulli tag);

    int removeFirst(list *q);

    int removeLast(list *q);

    /**
     * @brief bumps tagged node to front of list
     * @param[in] the list
     * @param[in] the tag of node to bump to first 
     * @return -1 error, 0 operation successful, 1 tag not found
     */
    int bumpToFirst(list *q, ulli tag);

    /**
     * @brief determines if the list is empty
     * @param[in] the list in question
     * @return 1 if empty, 0 if not empty
     */
    int isEmpty(list *q);

    /**
     * @brief determines if the list is full
     * @param[in] the list in question
     * @return 1 if full, 0 if not full
     */
    int isFull(list *q);

    void printList(list *q);

    int deleteList(list *q);


#endif
