#include "../header/linkedlist.h"

void appendNode(Node** headRef, char newData) {
  /*
    Add a new node containing given data to the front of Linked List

    Parameter:
      headRef: Pointer reference to the head of the linked list
      newData: Data to be added

    Returns:
      Nothing
  */
  Node* newNode = (Node* )malloc(sizeof(Node));

  if (newNode == NULL) {
    printf("Failed to allocate memory for a new node.\n");
    return;
  }

  Node* last = *headRef;

  newNode->data = newData;
  newNode->next = NULL;

  if (*headRef == NULL)
  {
    *headRef = newNode;
    return;
  }

  while (last->next != NULL)
  {
    last = last->next;
  }

  last->next = newNode;
}

void printNodeList(Node* linkedList) {
  /*
    Prints contents of Linked List

    Paramter:
      linkedList: Linked List to be printed

    Returns:
      Nothing
  */
	while (linkedList != NULL) {
		printf("%c", linkedList->data);
		linkedList = linkedList->next;
	} 
}

int getLen(Node* linkedList) {
  /*
    Calculate the length of a given Linked List

    Parameter:
      linkedList: Linked List to be calculated

    Returns:
      count: Length of the linked list
  */
  int count = 0; 

  Node* current = linkedList; 
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}