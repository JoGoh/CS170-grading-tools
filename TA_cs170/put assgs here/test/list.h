////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////
struct Node {
  int value;                 // data portion
  Node *next;                // pointer portion
};

// Push a node to the back of the list
void push_back(Node *&list, int value);

// Push a node to the front of the list
void push_front(Node *&list, int value);

// Returns the number of nodes in the list
int count(Node const *list);

// Frees (deletes) all of the nodes in the list
void clear(Node *&list);

// Prints all of the nodes values
void print_list(Node const *list);

// Reverse the order of the elements in the list
void reverse(Node *&list);

// Sort elements in the list
void sort(Node *&list);

// Remove duplicate values in a sorted list
void unique(Node *&list);

#endif                          // LIST_H
