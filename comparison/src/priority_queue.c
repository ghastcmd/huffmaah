#include "pch.h"
#include "headers/priority_queue.h"

int is_empty_node (struct node *node)
{
	return (node == NULL);
}

struct priority_queue *create_priority_queue ()
{
	struct priority_queue *pq = (struct priority_queue *) malloc (sizeof(struct priority_queue));

	pq->head == NULL;

	if (pq == NULL)
	{
		printf("Core Dump (Segmentation fault)\n");
		return NULL;
	}

	return pq;
}

void enqueue (struct priority_queue *pq, int item, int priority)
{
	struct node *new_node = (struct node *) malloc(sizeof(struct node));

	new_node->item = item;
	new_node->priority = priority;
	new_node->next = NULL;

	if (is_empty_node(pq->head) || priority > pq->head->priority)
	{
		new_node->next = pq->head;
		pq->head = new_node;
	}
	else
	{
		struct node *current = pq->head;
		struct node *previous = current;

		while (current != NULL && priority <= current->priority)
		{
			previous = current;
			current = current->next;
		}
		
		new_node->next = current;
		previous->next = new_node; 
	}
}

int search_without_heap (struct priority_queue *pq, int item)
{
	int n = 1;

	struct node *current = pq->head;

	while ((current != NULL) && ( current->item != item ) )
	{
		n += 1;	
		current = current->next;
	}
	
	return n;
}