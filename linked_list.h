#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct Node
{
    int val;
    struct Node* next;
} Node;

Node* add_node(Node* head, int val);
void free_linked_list(Node* head);
void print_linked_list(Node* head);

Node* remove_node(Node* head, int val);
Node* append_node_unique(Node* head, int val);// add node to linked list
Node* add_node(Node* head, int val);
int linked_list_length(Node* head);



#endif