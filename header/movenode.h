#ifndef MOVENODE_H
#define MOVENODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct MoveNode {
  int moves;
  struct MoveNode* next;
} MoveNode;

int getMoveLen(MoveNode* linkedList);
MoveNode* newMoveNode(int newMove);
void appendMoveNode(MoveNode** headRef, int newMove);
void bubbleSort(MoveNode* start);
void swapMoveNode(MoveNode* a, MoveNode* b);

#endif