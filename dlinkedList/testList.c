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
// list **q;// = initList(20); ///malloc size/blocks
// memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));
//
// strcpy(cacheCnfg->cacheName,"default.txt");
// cacheCnfg->L1dBlock  = 32;
// cacheCnfg->L1iBlock  = 32;
// cacheCnfg->L2Block   = 64;
//
// /* L1 data */
// cacheCnfg->L1dWays   = 8;
// cacheCnfg->L1dSize   = 8192;
// cacheCnfg->L1dBlock  = 32;
//
// /* L1 instruction */
// cacheCnfg->L1iWays   = 8;
// cacheCnfg->L1iSize   = 8192;
// cacheCnfg->L1iBlock  = 32;
//
// /* L2 */
// cacheCnfg->L2Ways    = 1;
// cacheCnfg->L2Size    = 32768;
// cacheCnfg->L2Block   = 64;
//
// int numIdx = cacheCnfg->L1dSize / cacheCnfg->L1dBlock;
// printf("number of indices: %d\n", numIdx);
//
// q = (list *) malloc(sizeof(list) * numIdx);
//
// for(int i=0; i<numIdx; i++)
// {
//     q[i] = initList(cacheCnfg->L1dWays);
//     for (int i=0; i<cacheCnfg->L1dWays; i++)
//     {
//         putFirst(q[i], i*numIdx);
//     }
// }
//
// for(int i=0; i<numIdx; i++)
// {
//     printList(q[i]);
//     printf("\n");
// }
//
// for(int i=0; i<numIdx; i++)
// {
//     deleteList(q[i]);
// }






















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
