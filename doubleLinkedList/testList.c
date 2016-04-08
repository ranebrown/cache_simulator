#include "doubleLinkedList.h"

int main()
{
    // An array of pointers to lists
    list **q = initList(); ///malloc size/blocks

    printf("isEmpty: %d\n", isEmpty(q));

    for(int i=1; i<=15; i++)
    {
        putFirst(q, i);
        printList(q);
    }
    putLast(q,100);
    printList(q);

    printf("isEmpty: %d\n", isEmpty(q));

    printf("nodeCount = %d\n", q->nodeCount);
    while(!isEmpty(q))
    {
        //printf("removing first node\n");
        //removeFirst(q);
        printList(q);
        //printf("removing last node\n");
        removeLast(q);
        //printList(q);
        //printf("\nnodeCount = %d\n", q->nodeCount);
    }

    printf("isEmpty: %d\n", isEmpty(q));

    deleteList(q);


    return 0;
}
