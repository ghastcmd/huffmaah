#include "headers/priority_queue.h"
#include "headers/priority_queue_with_heap.h"

int main()
{
    int i, n = 10;
    time_t t;
    
    struct heap *pq_with_heap = create_heap(n + 1);
    struct priority_queue *pq_without_heap= create_priority_queue();

    FILE *file_pq_without_heap = fopen("data/priority_queue_without_heap.txt","w");

    /* open the file for writing
    FILE *file_pq_with_heap = fopen("data/priority_queue_with_heap.txt","w");
    */

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    /* attributed n numbers random numbers from 0 to 10000 */
    for( i = 1 ; i < n +1; i++ ) 
    {
        int priority = (int) ((rand() % 9) + 1);
        int item = i;

        enqueue_heap(pq_with_heap, item, priority, n + 1);
        enqueue(pq_without_heap, item, priority);
    }
    
    /*
    for (i = 1; i < n + 1; i++)
    {
        if (pq_with_heap->data[i].item && pq_with_heap->data[i].priority)
        {
            if (i + 1 != n + 1)
            {
                printf("%d ", pq_with_heap->data[i].priority);
            }
            else
            {
                printf("%d\n", pq_with_heap->data[i].priority);
            }
        }
        
    }
    
    struct node *current = pq_without_heap->head;

    while (current != NULL)
    {
        if (current->next != NULL)
        {
            printf("%d ", current->priority);
        }
        else
        {
            printf("%d\n", current->priority);
        }
        
        current = current->next;
    }
    */
   
    // write lines of text into the file stream
    for(i = 1; i <= n;i++)
    {
        int item = i;

        fprintf (file_pq_without_heap, "item sorteado: %d, number of verification: %d\n", item, search_without_heap(pq_without_heap, item));
    }

    //close the file  
    fclose (file_pq_without_heap);
    return 0;
}