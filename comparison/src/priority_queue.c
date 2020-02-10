#include "pch.h"

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

void enqueue (struct priority_queue *pq, int i, int p)
{
	struct node *new_node = (struct node *) malloc(sizeof(struct node));

	new_node->item = i;
	new_node->priority = p;
	new_node->next = NULL;

	if (is_empty_node(pq->head) || p < pq->head->priority)
	{
		new_node->next = pq->head;
		pq->head = new_node;
	}
	else
	{
		struct node *current = pq->head;
		struct node *previous = current;

		while (current != NULL && p >= current->priority)
		{
			previous = current;
			current = current->next;
		}
		
		new_node->next = current;
		previous->next = new_node; 
	}
}

struct node *dequeue (struct priority_queue *pq)
{
	if (is_empty_node(pq->head))
	{
		printf("Priority queue underflow\n");
		return NULL;
	}
	else
	{
		struct node *dequeued = pq->head;

		pq->head = pq->head->next;
		dequeued->next = NULL;

		return dequeued;
	}
}