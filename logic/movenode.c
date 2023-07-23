#include "../header/movenode.h"

int getMoveLen(MoveNode* linkedList) {
  /*
    Calculate the length of a given Linked List

    Parameter:
      linkedList: Linked List to be calculated

    Returns:
      count: Length of the linked list
  */
  int count = 0; 

  MoveNode* current = linkedList; 
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

MoveNode* newMoveNode(int newMove) {
  /*
    Helper function to create new move node

    Parameter:
      newMove: New data to be created

    Returns:
      newNode: Newly created move node
  */
  MoveNode* newNode = (MoveNode* )malloc(sizeof(MoveNode));

  if (newNode == NULL) {
    printf("Failed to allocate memory for a new node.\n");
    return NULL;
  }

  newNode->moves = newMove;
  newNode->next = NULL;
  return newNode;
}

void appendMoveNode(MoveNode** headRef, int newMove) {
  /*
    Add a new node containing given data to move node Linked List

    Parameter:
      headRef: Pointer reference to the head of the linked list
      newMove: Data to be added

    Returns:
      Nothing
  */
  MoveNode* newNode = newMoveNode(newMove);
  MoveNode* last = *headRef;

  if (*headRef == NULL) {
    *headRef = newNode;
    return;
  }

  while (last->next != NULL) {
    last = last->next;
  }
  last->next = newNode;
}

void bubbleSort(MoveNode* linkedlist) { 
  /*
    Bubble sort algorithmn implementation
      Sorts the largest elements first
      Ascending order 
    
    Parameter:
      linkedlist: Linked list to be sorted
    
    Return:
      Nothing
  */
  int swapped; 
  MoveNode* currentPtr; 
  MoveNode* lastPtr = NULL; 
  
  if (linkedlist == NULL) {
    return;
  }
  
  do { 
    swapped = 0; 
    currentPtr = linkedlist; 

    while (currentPtr->next != lastPtr) { 
      if (currentPtr->moves > currentPtr->next->moves) { 
        swapMoveNode(currentPtr, currentPtr->next); 
        swapped = 1; 
      } 
      currentPtr = currentPtr->next; 
    } 
    lastPtr = currentPtr; 
  } while (swapped); 
} 
  
void swapMoveNode(MoveNode* a, MoveNode* b) { 
  /*
    Helper functiont to swap nodes

    Parameter:
      a: Move node to be swapped
      b: Move node to be swapped
    
    Returns:
      Nothing
  */
  int temp = a->moves; 
  a->moves = b->moves; 
  b->moves = temp; 
} 