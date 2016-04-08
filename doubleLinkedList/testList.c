#include "doubleLinkedList.h"

int main()
{
    // An array of pointers to lists
    list *q = initList(21); ///malloc size/blocks

    printf("\nPutting Last, Removing First\n");
    putLast(q, 1024);
    printList(q);
    removeFirst(q);
    printf("isEmpty: %d\n", isEmpty(q));

    printf("\nPutting First, Removing Last\n");
    putFirst(q, 2048);
    printList(q);
    removeLast(q);
    printf("isEmpty: %d\n", isEmpty(q));

    printf("\nFilling List\n");
    for(int i=11; i>1; i--)
    {
        putFirst(q, i);
        putLast(q, 20-i);
    }
    printList(q);

    printf("isFull: %d\n", isFull(q));
    putLast(q,100);
    printList(q);
    printf("isFull: %d\n", isFull(q));

    printf("\nbumping the first tag.\n");
    bumpToFirst(q, 10);
    printList(q);

    printf("\nbumping the '5' tag.\n");
    bumpToFirst(q, 5);
    printList(q);

    printf("\nbumping the last tag.\n");
    bumpToFirst(q, 100);
    printList(q);

    printf("\nbumping a nonexistant tag.\n");
    bumpToFirst(q, 99);
    printList(q);


    printf("\nRemoving the first node.\n");
    removeFirst(q);
    printList(q);

    printf("\nRemoving the last node.\n");
    removeLast(q);
    printList(q);

    printf("\nRemoving the first node.\n");
    removeFirst(q);
    printList(q);

    printf("\nRemoving the last node.\n");
    removeLast(q);
    printList(q);

    printf("nodeCount = %d\n", q->nodeCount);
    while(!isEmpty(q))
    {
        //printf("removing first node\n");
        //removeFirst(q);
        //printList(q);
        //printf("removing last node\n");
        removeLast(q);
        //printList(q);
        //printf("\nnodeCount = %d\n", q->nodeCount);
    }
    printf("Empty List ");
    printList(q);
    printf("isEmpty: %d\n", isEmpty(q));
    printf("isFull: %d\n", isFull(q));
    deleteList(q);


    return 0;
}
