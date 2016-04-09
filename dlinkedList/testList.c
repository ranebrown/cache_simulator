#include "dlinkedList.h"

int main()
{

    list *q = initList(20);


    for (int i=0; i<10; i++)
    {
        putFirst(q, 10-i);
        putLast(q, 11+i);
        printList(q);
    }

    printf("isEmpty: %d\n", isEmpty(q));
    printf("isFUll:  %d\n", isFull(q));


    putFirst(NULL, 10);
    putLast(NULL, 10);

    deleteList(q);
    printList(q);

    removeFirst(q);
    removeLast(q);


    return 0;
}

// An array of pointers to lists
// list **q = initList(20); ///malloc size/blocks
//
// strcpy(cacheCnfg->cacheName,"default.txt");
// cacheCnfg->L1dBlock  = 32;
// cacheCnfg->L1iBlock  = 32;
// cacheCnfg->L2Block   = 64;
//
// /* L1 data */
// cacheCnfg->L1dWays   = 1;
// cacheCnfg->L1dSize   = 8192;
// cacheCnfg->L1dBlock  = 32;
//
// /* L1 instruction */
// cacheCnfg->L1iWays   = 1;
// cacheCnfg->L1iSize   = 8192;
// cacheCnfg->L1iBlock  = 32;
//
// /* L2 */
// cacheCnfg->L2Ways    = 1;
// cacheCnfg->L2Size    = 32768;
// cacheCnfg->L2Block   = 64;
//
//
// q = (list *) malloc(sizeof(list) * );
//
//





















// printf("Adding 1 node (first)\n");
// putFirst(q, 1);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 1 node (first)\n");
// removeFirst(q);
// printList(q);
//
// printf("\n\n");
//
// printf("Adding 2 nodes (first)\n");
// putFirst(q, 1);
// putFirst(q, 2);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 2 nodes (first)\n");
// removeFirst(q);
// removeFirst(q);
// printList(q);
//
// printf("\n\n");
//
// printf("Adding 3 nodes (first)\n");
// putFirst(q, 1);
// putFirst(q, 2);
// putFirst(q, 3);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 3 nodes (first)\n");
// removeFirst(q);
// removeFirst(q);
// removeFirst(q);
// printList(q);
//
// printf("\n\n");
//
// printf("Adding 1 node (last)\n");
// putLast(q, 1);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 1 node (last)\n");
// removeLast(q);
// printList(q);
//
// printf("\n\n");
//
// printf("Adding 2 nodes (last)\n");
// putFirst(q, 1);
// putFirst(q, 2);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 2 nodes (last)\n");
// removeLast(q);
// removeLast(q);
// printList(q);
//
// printf("\n\n");
//
// printf("Adding 3 nodes (last)\n");
// putLast(q, 1);
// putLast(q, 2);
// putLast(q, 3);
// printList(q);
//
// printf("\n\n");
//
// printf("Removing 3 nodes (last)\n");
// removeLast(q);
// removeLast(q);
// removeLast(q);
// printList(q);
