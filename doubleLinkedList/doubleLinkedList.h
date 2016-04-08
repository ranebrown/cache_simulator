
#ifndef DOUBLELINKEDLIST_H
    #define DOUBLELINKEDLIST_H

    #include <stdio.h>
    #include <stdlib.h>

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
    }list;


    list *initList();

    int putFirst(list *q, ulli data);

    int putLast(list *q, ulli data);

    int removeFirst(list *q);

    int removeLast(list *q);

    int bumpToFirst(list *q);

    /**
      * Returns 1 if list is empty
      */
    int isEmpty(list *q);

    void printList(list *q);

    int deleteList(list *q);


#endif
