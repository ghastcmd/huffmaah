#include <pch.h>
#include "linkedList.h"
#include "node.h"

int main()
{
    node* head = malloc(sizeof(node));
    if (!head)
    {
        perror("malloc");
    }

    *head = (node) {
        .val = 10,
        .freq = 1,
        .next = nullptr,
        .left = nullptr,
        .right = nullptr
    };

    insert_sorted(&head);

    free(head);

    return 0;
}