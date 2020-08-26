////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////
struct Node {
    int value;                 // data portion
    Node *next;                // pointer portion
};

// Adds a node to the front of the list
void AddToEnd(Node **pList, int value);

// Adds a node to the end of the list
void AddToFront(Node **pList, int value);

// Returns the number of nodes in the list
int Count(Node const *list);

// Frees (deletes) all of the nodes in the list
void FreeList(Node *list);

// Prints all of the nodes values
void PrintList(Node const *list);

// Finds the first node with number==value.
// Returns nullptr if not found
Node *Find(Node *list, int value);

//Delete the first node that has number==value
void Delete(Node **pList, int value);

// Inserts a new node at the specified position.
// Postion numbering begins from 0.
// If position exceeds size of list, value is inserted at
// the end of the list.
void Insert(Node **pList, int value, int position);

// Concatenates two list1 and list2.
// list2 is empty after the function is called.
// list1 is list1 + list2 after function is called.
// See driver and sample output for more details.
void Concat(Node **pList1, Node **pList2);

#endif                          // LIST_H
