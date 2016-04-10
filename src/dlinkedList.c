#include "dlinkedList.h"

list *initList(int maxSize)
{
    /* Create the list on the heap */
    list *q = (list *) malloc(sizeof(list));

    q->first = NULL;
    q->last  = NULL;

    q->nodeCount = 0;
    q->maxSize= maxSize;

    return q;
}

int putFirst(list *q, ulli tag)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. putFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* create the node on the heap */
    node *newnode = NULL;
    if( (newnode = (node*) malloc(sizeof(node))) == NULL)
    {
        fprintf(stderr,"ERROR: Could not allocate memory. putFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if this is the first node to be added */
    if(q->nodeCount == 0)
    {
        q->first       = newnode;
        newnode->prev  = NULL;
        newnode->next  = NULL;
        q->last        = newnode;
    }
    /* If not the only node, add to the beginning */
    else
    {
        newnode->next  = q->first;
        q->first->prev = newnode;
        q->first       = newnode;
        newnode->prev  = NULL;
    }

    newnode->tag = tag;
    (q->nodeCount)++;

    return EXIT_SUCCESS;
}

int putLast(list *q, ulli tag)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. putLast failed.\n");
        return EXIT_FAILURE;
    }

    /* Create the node on the heap */
    node *newnode = NULL;
    if( (newnode = (node*) malloc(sizeof(node))) == NULL )
    {
        fprintf(stderr,"ERROR: Could not allocate memory. putLast failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if the list is empty. */
    if(q->nodeCount == 0)
    {
        q->first       = newnode;
        newnode->prev  = NULL;
        newnode->next  = NULL;
        q->last        = newnode;
    }
    else
    {
        newnode->prev = q->last;
        q->last->next = newnode;
        q->last       = newnode;
        newnode->next = NULL;
    }

    /* Fill in the rest of necessary data */
    newnode->tag = tag;
    (q->nodeCount)++;
    return EXIT_SUCCESS;
}

int removeFirst(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. removeFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if list is empty */
    if(isEmpty(q))
    {
        printf("The list is empty. Exiting removeFirst\n");
        return EXIT_SUCCESS;
    }

    /* Check to make sure there is a first node */
    if( q->first == NULL )
    {
        fprintf(stderr,"ERROR: No node to remove. removeFirst failed.\n");
        return EXIT_FAILURE;
    }

    /* Create and point a temp node to the node to be removed */
    node *temp = NULL;
    if( (temp = q->first) == NULL )
    {
        fprintf(stderr,"ERROR: Could not get first node. removeFirst failed\n");
        return EXIT_FAILURE;
    }

    // if(q->last != NULL)
    //     printf("In removeFirst, last tag exists\n");

    /* check if temp is the last node, if so set the first and last to NULL */
    if(q->nodeCount == 1)
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
    (q->nodeCount)--;
    return EXIT_SUCCESS;
}

int removeLast(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. removeLast failed.\n");
        return EXIT_FAILURE;
    }

    /* Check if list is empty */
    if(isEmpty(q))
    {
        printf("The list is empty. Exiting removeLast\n");
        return EXIT_SUCCESS;
    }

    /* Check to make sure there is a last node */
    if( q->last == NULL )
    {
        fprintf(stderr,"ERROR: No node to remove. removeLast failed.\n");
        return EXIT_FAILURE;
    }


    /* Create and point a temp node to the node to be removed */
    node *temp = NULL;
    if( (temp = q->last) == NULL )
    {
        fprintf(stderr,"ERROR: Could not get last node. removeLast failed\n");
        return EXIT_FAILURE;
    }

    // printf("temp     @ %p\n",temp);
    // printf("q->last  @ %p\n",q->last);

    /* Check if temp is the only node, if so set the last and first to NULL */
    if(q->nodeCount == 1)
    {

        q->first = NULL;
        q->last  = NULL;

    }
    else
    {
        q->last       = q->last->prev;
        q->last->next = NULL;

    }

    // printf("temp2    @ %p\n",temp);

    //printf("%p <-> ... <-> %p\n",q->first->prev, q->last->next);

    free(temp);

    (q->nodeCount)--;

    return 0;
}

int bumpToFirst(list *q, ulli tag)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. bumpToFirst failed.\n");
        return -1;
    }

    /* Check that the list has nodes */
    if( isEmpty(q) )
    {
        fprintf(stderr,"ERROR: The list is empty. bumpToFirst failed.\n");
        return -1;
    }

    /* Create cursor to go down list */
    node *cursor = NULL;
    if( !(cursor = q->first) )
    {
        fprintf(stderr,"ERROR: Could not get first node. bumpToFirst failed\n");
        return -1;
    }

    /* Go down the list looking for the matching tag */
    while(cursor->tag != tag)
    {
        /* Check if we've reached the last node. If so return with message. */
        if(cursor->next == NULL)
        {
            #ifdef DEBUG
                printf("Tag not found.\n");
            #endif
            return 1;
        }
        cursor = cursor->next;
    }

    /* At this point we have the desired node at the cursor */
    if(cursor->prev == NULL)
    {
        /* This tag is already at the beginning of the list */
        return 0;
    }
    else if(cursor->next == NULL)
    {
        /* Tag is at the end of the list */
        q->last        = q->last->prev;
        q->last->next  = NULL;
        cursor->next   = q->first;
        q->first->prev = cursor;
        q->first       = cursor;
        cursor->prev   = NULL;
    }
    else
    {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        cursor->next = q->first;
        q->first->prev = cursor;
        q->first = cursor;
        cursor->prev = NULL;
    }

    return EXIT_SUCCESS;
}

// int replaceNode(list *q, ulli tag, ulli newTag)
// {
//     return 0;
// }

int isEmpty(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. isEmpty failed.\n");
        return -1;
    }
    return ((q->nodeCount == 0) || (q->first==NULL && q->last==NULL));
}

int isFull(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. isFull failed.\n");
        return -1;
    }
    return (q->nodeCount == q->maxSize);
}

void printList(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. printList failed.\n");
        return;
    }

    /* Check that there is something to print */
    if(isEmpty(q))
    {
        printf("List is empty, nothing to print.\n");
        return;
    }
    /* Create cursor to go down list */
    node *cursor = NULL;
    if( !(cursor = q->first) )
    {
        fprintf(stderr,"ERROR: Could not get next node. printList failed\n");
        return;
    }
    #ifdef DEBUG
        printf("%p -> ",cursor->prev);
    #endif

    while(1)
    {
        printf("%llu", cursor->tag);
        if(cursor->next)
        {
            cursor = cursor->next;
            printf(" <-> ");
        }
        else
        {
            #ifdef DEBUG
                printf(" -> %p", cursor->next);
            #endif
            break;
        }
    }
    printf("\n");
}

int deleteList(list *q)
{
    /* Check for malformed input */
    if(!q)
    {
        fprintf(stderr,"ERROR: NULL pointer passed. deleteList failed.\n");
        return EXIT_FAILURE;
    }

    while(q->nodeCount)
    {
        removeFirst(q);
    }
    free(q);
    return EXIT_SUCCESS;
}
