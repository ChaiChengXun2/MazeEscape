#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
  char data;
  struct Node* next;
} Node;

void appendNode(Node** headRef, char newData);
void printNodeList(Node* linkedList);
int getLen(Node* linkedList);

#endif