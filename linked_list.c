#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"




// append node to linked list using iteration
Node* append_node(Node* head, int val)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;

    if(head == NULL) return new_node;
    
    Node* current = head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
    return head;
}


// print linked list
void print_linked_list(Node* head)
{
    while (head)
    {
        printf("%d, ", head->val);
        head = head->next;
    }
    
    printf("\n"); fflush(stdout);
}

// free linked list
void free_linked_list(Node* head)
{
    if(head == NULL) return;
    free_linked_list(head->next);
    free(head);
}

// append node to linked list using iteration if not already in list
Node* append_node_unique(Node* head, int val)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;

    if(head == NULL) return new_node;
    
    Node* current = head;
    while(current->next != NULL)
    {
        
        if (current->val == val) return head;
    
        current = current->next;
    }
    if (current->val == val) return head;

    current->next = new_node;

    return head;
}


// remove value from linked list
Node* remove_node(Node* head, int val)
{
    if(head == NULL) return NULL;
    if(head->val == val)
    {
        Node* new_head = head->next;
        free(head);
        return new_head;
    }
    head->next = remove_node(head->next, val);
    return head;
}

int linked_list_length(Node* head)
{
    int count = 0;
    Node* current = head;
    while(current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}