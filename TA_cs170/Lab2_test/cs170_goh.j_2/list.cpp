/******************************************************************************/
/*!
\file   list.cpp
\author Josiah Goh
\par    email: goh.j\@digipen.edu
\par    DigiPen login: goh.j
\par    Course: CS170
\par    Lab 02
\date   25/1/2019
\brief  
    This file contains the implementation of the following functions for the
      linked list lab.
    Functions include:
        MakeNode
        PrintList
        Count
        AddToEnd
        AddToFront
        FreeList
        Delete
        Insert
        Concat
    
*/
/*****************************************************************************/
#include <iostream>//cout, endl
#include <iomanip>//setw
#include "list.h"


namespace{
	
	void Swaggeroone(){
		std::cout<<"here";
	}
	
	
}
/*****************************************************************************/
/*!
  \brief
    Creates a new node.

  \param value
    The value of the node.

  \return pNode
   the pointer to the new node.  

*/
/*****************************************************************************/
// Allocate memory and set members
Node *MakeNode(int value) {
  Node *pNode = new Node;
  pNode->value = value;
  pNode->next = nullptr;

  return pNode;
}
/*****************************************************************************/
/*!
  \brief
    Prints the linked list.

  \param list
    the linked list.

*/
/*****************************************************************************/
// Prints all of the nodes values
void PrintList(Node const *list) {
  while (list) {
    std::cout << std::setw(4) << list->value;
    list = list->next;
  }
  std::cout << std::endl;
}
/*****************************************************************************/
/*!
  \brief
    Counts number of nodes in list.

  \param list
    The linked list.

  \return count
  the number of nodes.
  

*/
/*****************************************************************************/
// Returns the number of nodes in the list
int Count(Node const *list) {
  int count = 0;
  while (list) {
    count++;
    list = list->next;
  }
  return count;
}
/*****************************************************************************/
/*!
  \brief
   Adds new node to end of list.

  \param pList
    The pointer to the start of the list.

  \param value
    The value of the node.
*/
/*****************************************************************************/
// Adds a node to the end of the list
void AddToEnd(Node **pList, int value) {
  Node *pNewNode = MakeNode(value);
  Node *pCurrNode = *pList;

  if (*pList == 0)
    *pList = pNewNode;
  else {
    while (pCurrNode->next) pCurrNode = pCurrNode->next;
    pCurrNode->next = pNewNode;
  }
			Swaggeroone();
}
/*****************************************************************************/
/*!
  \brief
   Adds new node to front of list.

  \param pList
    The pointer to the start of the list.

  \param value
    The value of the node.
*/
/*****************************************************************************/
// Adds a node to the front of the list
void AddToFront(Node **pList, int value) {
  Node *pNewNode = MakeNode(value);
  pNewNode->next = *pList;
  *pList = pNewNode;
}
/*****************************************************************************/
/*!
  \brief
   deletes the nodes of the list.

  \param list
    The pointer to the start of the list.
    
*/
/*****************************************************************************/
// Frees (deletes) all of the nodes in the list
void FreeList(Node *list) {
  Node *pCurrNode = list;
  while (pCurrNode) {
    list = pCurrNode->next;
    delete pCurrNode;
    pCurrNode = list;

  }
}

/*****************************************************************************/
/*!
  \brief
   Finds the first node that has number==value.
   Returns nullptr if not found 
  \param list
    The start of the list

  \param value
    The value to be found.
    
  \return cycle
   either the node that has the value or a nullptr.
*/
/*****************************************************************************/
Node *Find(Node *list, int value) {
   Node * cycle = list;
   while (cycle)
    {
          if(cycle->value==value)
              return cycle;
          cycle=cycle->next;
    }
   return nullptr;
          
   
}
/*****************************************************************************/
/*!
  \brief
   Delete the first node that has number==value.

  \param pList
    The pointer to the start of the list

  \param value
    The value of the node.
*/
/*****************************************************************************/
void Delete(Node **pList, int value) {
    Node * last = nullptr;
    Node * del=Find(*pList, value);
    Node * temp  = *pList;

   
    if(del!=nullptr&&del->next !=NULL)
    {
         //node found and its not last node
         temp  = del->next;
         del->value  = temp->value;
         del->next  = temp->next;
         delete temp;
    }
    
     else if (del!=nullptr)
    {
         //node found but its the last
        if(!(temp->next))
        {
             //if only node
             delete *pList;
             *pList=nullptr;
        }
        else
        {
            while(temp->next!= NULL)
            {
                last=temp;
                temp=temp->next;
            }
            last->next=NULL; 
            delete(temp);
        }

    
    } 
    
    
    
    
}
/*****************************************************************************/
/*!
  \brief
   Inserts a new node at the specified position.

  \param pList
    The pointer to the start of the list

  \param value
    The value of the node.
  
  \param position
    The position the node to be placed.
    
*/
/*****************************************************************************/
void Insert(Node **pList, int value, int position) 
{		
		if(!pList) //no list 
			return;
		
		if(position<0) //before 0 just addtofront
		{
			AddToFront(pList, value);
			return;
		}
		
		Node * origin = *pList;
    Node * prev=*pList;
    int size = Count(*pList);
		
    if(position>size)    //if position is over the size
        AddToEnd(pList, value);
    else if (!position) //if it is at the front
        AddToFront(pList,value);
    else
    {
        while(position)
        {   
           prev=*pList;
           *pList=((*pList)->next);
           position--;
        }
        Node * here = MakeNode(value);
        here->next=*pList;
        prev->next=here;
        *pList=origin;//shift back the ptr
     
    }


        
    
        
}
/*****************************************************************************/
/*!
  \brief
   Concatenates two lists.

  \param pList1
    The pointer to the start of list 1.
  
  \param pList2
    The pointer to the start of list 2.


*/
/*****************************************************************************/
void Concat(Node **pList1, Node **pList2) {
    Node * current = *pList1;
    Node * two = *pList2;
    if(*pList1==nullptr) //if pList1 is empty
        *pList1=two;
    else{
        while(current->next)
            current=current->next;
        current->next=two;
    }
    *pList2=NULL; 
    
    
        
}


