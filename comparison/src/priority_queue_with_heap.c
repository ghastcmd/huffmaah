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
    heap->data = (struct node_heap *) malloc((n + 1) * sizeof(struct node_heap));

    if (heap->data == NULL)
    {
        printf("Core Dump (Segmentation fault)\n");
        heap->data = NULL;
    }

    return heap;
}

int get_parent_index (struct heap *heap, int i)
{
    return i/2;
}

int get_left_index (struct heap *heap, int i)
{
    return i*2;
}

int get_right_index (struct heap *heap, int i)
{
    return (i*2) + 1;
}

void swap (struct node_heap *node1, struct node_heap *node2)
{
    struct node_heap aux = *node1;
    *node1          = *node2;
    *node2          = aux;
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
        
        int key_index = heap->size;
        int parent_index = get_left_index (heap, heap->size);

        while ((parent_index >= 1) && 
                (heap->data[key_index].priority >= heap->data[parent_index].priority))
        {
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(heap, key_index);
        }
    }
    
}

struct node_heap *dequeue_heap (struct heap *heap)
{
    if (is_empty_heap(heap))
    {
        printf("Heap Underflow\n");
        return NULL;
    }
    
    struct node_heap *dequeued = &heap->data[1];

    heap->data[1] = heap->data[heap->size];
    heap->size -= 1;

    max_heapify (heap, 1);

    return dequeued;
}

void max_heapify (struct heap *heap, int i)
{
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if ((left_index <= heap->size) && 
        (heap->data[left_index].priority > heap->data[i].priority))
    {
        largest = left_index;
    }
    else
    {
        largest = i;
    }
    
    if ((right_index <= heap->size) && 
        (heap->data[right_index].priority > heap->data[largest].priority))
    {
        largest = right_index;
    }

    if (heap->data[i].priority != heap->data[largest].priority )
    {
        swap(&heap->data[i], &heap->data[largest]);
        max_heapify(heap, largest);
    }
}