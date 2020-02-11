#include "pch.h"
#include "headers/priority_queue_with_heap.h"

int is_empty_heap (struct heap *heap)
{
    return (heap == NULL);
}

struct heap *create_heap (int n)
{
    struct heap *heap = (struct heap *) malloc(sizeof(struct heap));
    
    if (is_empty_heap(heap))
    {
        printf("Core Dump (Segmentation fault)\n");
        return NULL;
    }

    heap->size = 0;
    heap->data = (struct node_heap *) malloc(n * sizeof(struct node_heap));

    if (heap->data == NULL)
    {
        printf("Core Dump (Segmentation fault)\n");
        heap->data = NULL;
    }

    return heap;
}

int get_parent_index (int i)
{
    return i/2;
}

int get_left_index (int i)
{
    return i*2;
}

int get_right_index (int i)
{
    return (i*2) + 1;
}

void swap (struct node_heap *node1, struct node_heap *node2)
{
    struct node_heap aux = *node1;
    *node1               = *node2;
    *node2               = aux;
}

void enqueue_heap (struct heap *heap, int item, int priority, int n)
{
    if (heap->size >= n)
    {
        printf("Heap Overflow\n");
    }
    else
    {
        heap->data[++heap->size].item = item;
        heap->data[heap->size].priority = priority;
        //printf("p: %d - i: %d\n", heap->data[heap->size].priority, heap->data[heap->size].item);
        
        int key_index = heap->size;
        int parent_index = get_parent_index (heap->size);

        while ((parent_index >= 1) && 
                (heap->data[key_index].priority > heap->data[parent_index].priority))
        {
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(key_index);
        }
    }
    
}


int search_with_heap (struct heap *heap, int item, int priority, int index, int *find)
{
    int index_left = get_left_index(index);
    int index_right = get_right_index(index);

    if ( (index_left > heap->size) || index_left > heap->size)
        return 0;
    
    if ( priority == heap->data[index_left].priority)
    {
        if (item == heap->data[index_left].item)
        {
            return 1;
        }
        else
        {
            return 1 + search_with_heap(heap, item, priority, index_right, find); 
        }
        
    }
    else if ( (priority == heap->data[index_right].priority))
    {
        if (item == heap->data[index_right].item)
        {  
            return 1;
        }
        else
        {
            return 1 + search_with_heap(heap, item, priority, index_left, find);    
        }
        
    }
    else
    {
        int aux = 1 + search_with_heap(heap, item, priority, index_left, find);
            aux += 1;
            aux += search_with_heap(heap, item, priority, index_right, find);

        return aux;
    }

}