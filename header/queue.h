#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include "maze.h"

typedef struct QNode {
  Coordinate coordinate;
  Coordinate parent;
  struct QNode* next; 
} QNode;

typedef struct Queue {
  QNode* front; 
  QNode* back;
} Queue;

QNode* newQNode(Coordinate coordinate, Coordinate parent);
Queue* initialiseQueue(void);
void enqueue(Queue* queue, Coordinate coordinate, Coordinate parent);
Coordinate dequeue(Queue* queue);
void printQueue(Queue* queue);
int isQEmpty(Queue* queue);
QNode* pop(Queue* queue);
int getQueueLength(Queue* queue);

#endif