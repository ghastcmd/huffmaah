#include "headers/priority_queue.h"
#include "headers/priority_queue_with_heap.h"

int main()
{
    int i, n = 10;
    time_t t;
    
    struct heap *pq_with_heap = create_heap(n + 1);
    struct priority_queue *pq_without_heap= create_priority_queue();

    FILE *file_pq_without_heap = fopen("data/priority_queue_without_heap.txt","w");
    FILE *file_pq_with_heap = fopen("data/priority_queue_with_heap.txt","w");

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    int priority_array[n];

    /* attributed n numbers random numbers from 0 to 10000 */
    for( i = 1 ; i < n +1; i++ ) 
    {
        int priority = (int) ((rand() % 9) + 1);
        int item = i;

        priority_array[i - 1] = priority;

        enqueue_heap(pq_with_heap, item, priority, n + 1);
        enqueue(pq_without_heap, item, priority);
    }

    fprintf (file_pq_with_heap, "item,n\n");
    // write lines of text into the file stream
    for(i = 1; i <= n; i++)
        fprintf (file_pq_with_heap, "%d,%d\n", i, search_with_heap(pq_with_heap, i, priority_array[i], 1));

    fprintf (file_pq_without_heap, "item,n\n");
    // write lines of text into the file stream
    for(i = 1; i <= n; i++)
        fprintf (file_pq_without_heap, "%d,%d\n", i, search_without_heap(pq_without_heap, i));

    //close the file and structs
    fclose (file_pq_with_heap); 
    fclose (file_pq_without_heap);
    free(pq_with_heap);
    free(pq_without_heap);
    return 0;
}