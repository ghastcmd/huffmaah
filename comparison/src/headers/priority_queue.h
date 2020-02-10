#pragma once
#include "pch.h"

struct node {
	int item;
	int priority;
	struct node *next;
};

struct priority_queue {
	struct node *head;
};

//function to verify if head of the struct node is null
int is_empty_node (struct node *node);

//alloc memory for to struct priority_queue (create struct)
struct priority_queue *create_priority_queue ();

//add one node on struct with priority
void enqueue (struct priority_queue *pq, int item, int priority);

// count number of verifications
int search_without_heap (struct priority_queue *pq, int item);