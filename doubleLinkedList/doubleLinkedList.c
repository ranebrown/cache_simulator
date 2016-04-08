#include "doubleLinkedList.h"

list *initList()
{
    /* Create the first node on the heap */
    list *q = (list *) malloc(sizeof(list));

    q->fulli
    q->last  = NULL;

    q->nodeCount = 0;

    printf("Done initiating list.\n");
    return q;
}

int putFirst(list *q, ulli data)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. putFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* create the node on the heap */
    node *newnode = NULL;
    if( !(newnode = (node*) malloc(sizeof(node))) )
    {
        printf("ERROR: Could not allocate memory. putFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if this is the first node to be added */
    if(q->first == NULL)
    {
        q->first       = newnode;
        q->first->prev = NULL;
        q->first->next = NULL;
        q->last        = newnode;
    }
    /* If not the only node add to the beginning */
    else
    {
        newnode->next  = q->first;
        q->first->prev = newnode;
        q->first       = newnode;
        newnode->prev  = NULL;
    }

    newnode->data = data;
    (q->nodeCount)++;

    return EXIT_SUCCESS;
}

int putLast(list *q, ulli data)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. putLast failed.\n");
        return EXIT_FAILURE;
    }

    /* create the node on the heap */
    node *newnode = NULL;
    if( !(newnode = (node*) malloc(sizeof(node))) )
    {
        printf("ERROR: Could not allocate memory. putLast failed.\n");
        return EXIT_FAILURE;
    }

    if(q->last == NULL)
    {
        newnode->prev  = q->first;
        newnode->next  = q->last;
        q->first->next = newnode;
        q->last->prev  = newnode;
    }
    else
    {
        newnode->prev = q->last;
        q->last->next = newnode;
        q->last       = newnode;
    }

    /* Fill in the rest of necessary data */
    newnode->data = data;
    (q->nodeCount)++;
    return EXIT_SUCCESS;
}

int removeFirst(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. removeFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if list is empty */
    printf("In removeFirst, nodeCount=%d, list is empty if 1=%d\n", q->nodeCount,isEmpty(q));
    printf("q->first=%p\n",q->first);
    if(isEmpty(q))
    {
        printf("The list is empty. Exiting removeFirst\n");
        return EXIT_SUCCESS;
    }

    /* Check to make sure there is a first node */
    if( !(q->first) )
    {
        printf("ERROR: No node to remove. removeFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Create and point a temp node to the node to be removed */
    node *temp = NULL;
    if( !(temp = q->first) )
    {
        printf("ERROR: Could not get first node. removeFirst failed\n");
        return EXIT_FAILURE;
    }

    /* check if this is the last node, if so set the first and last to NULL */
    if(q->first->next == NULL)
    {
        q->first = NULL;
        q->last  = NULL;
    }
    /* If not, remove from the list and make next node the first */
    else
    {
        q->first = q->first->next;
        q->first->prev = NULL;
    }

    free(temp);
    q->nodeCount--;
    return 0;
}

int removeLast(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. removeLast failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if list is empty */
    if(isEmpty(q))
    {
        printf("The list is empty. Exiting removeLast\n");
        return EXIT_SUCCESS;
    }

    /* Check to make sure there is a last node */
    if( !(q->last) )
    {
        printf("ERROR: No node to remove. removeLast failed.\n");
        return EXIT_FAILURE;
    }

    /* Create and point a temp node to the node to be removed */
    node *temp = NULL;
    if( !(temp = q->last) )
    {
        printf("ERROR: Could not get last node. removeLast failed\n");
        return EXIT_FAILURE;
    }

    /* check if this is the first node, if so set the last and first to NULL */
    if(q->last->prev == NULL)
    {
        q->first = NULL;
        q->last  = NULL;
    }
    /* If not, remove from the list and make next node the first */
    else
    {
        q->last = q->last->prev;
        q->last->next = NULL;
    }

    free(temp);

    q->nodeCount--;

    return 0;
}

int isEmpty(list *q)
{
    return ((q->nodeCount == 0) || (q->first==NULL && q->last==NULL));
}

void printList(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. printList failed.\n");
        return;
    }

    /* Create cursor to go down list */
    node *cursor = NULL;
    if( !(cursor = q->first) )
    {
        printf("ERROR: Could not get next node. printList failed\n");
        return;
    }

    while(1)
    {
        printf("%llu", cursor->data);
        if(cursor->next)
        {
            cursor = cursor->next;
            printf(" -> ");
        }
        else
            break;
    }
    printf("\n");
}

int deleteList(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        printf("ERROR: NULL pointer passed. printList failed.\n");
        return EXIT_FAILURE;
    }

    if(isEmpty(q))
        free(q);
    else
    {
        printf("List is not empty!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
