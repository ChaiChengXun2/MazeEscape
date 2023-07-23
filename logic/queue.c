#include "../header/queue.h"

QNode* newQNode(Coordinate coordinate, Coordinate parent) {
  /*
    Create a queue node 

    Parameter:
      coordinate: Coordinate of the new node
      parent: Parent coordinate of new coordinate
    
    Returns:
      newNode: Pointer to newly created QNode 
      NULL: Malloc failed to provide memory required
  */
  QNode* newNode = (QNode* )malloc(sizeof(QNode));

  if (newNode == NULL) {
    printf("Failed to allocate memory for a new node.\n");
    return NULL;
  }

  newNode->coordinate = coordinate;
  newNode->parent = parent; 
  newNode->next = NULL;

  return newNode;
}

Queue* initialiseQueue(void) {
  /*
    Initalises queue

    Parameter:
      Nothing

    Returns:
      q: Pointer to initialised queue
      NULL: Malloc failed to provide memory required
  */
  Queue* q = (Queue* )malloc(sizeof(Queue));

  if (q == NULL) {
    printf("Failed to allocate memory for a queue.\n");
    return NULL;
  }

  q->front = NULL; 
  q->back = NULL;

  return q;
}

void enqueue(Queue* queue, Coordinate coordinate, Coordinate parent) {
  /*
    Adding a node to the back of the queue

    Parameter:
      queue: Queue to which new node is added
      coordinate: Coordinate of the new node
      parent: Parent coordinate of new node

    Returns:
      Nothing
  */
  QNode* temp = newQNode(coordinate, parent);

  if (queue->back == NULL) {
    queue->front = temp; 
    queue->back = temp;
    return;
  }

  queue->back->next = temp; 
  queue->back = temp; 
}

Coordinate dequeue(Queue* queue) {
  /*
    Remove a node from the back of the queue

    Parameter:
      queue: Queue to which node is removed
    
    Returns:
      coordinate: Coordinate of dequeued QNode
      {-1, -1}: Queue is empty
  */
  Coordinate coordinate = {-1, -1};

  if (queue->front == NULL) {
    return coordinate;
  }

  QNode* temp = queue->front;

  queue->front = queue->front->next;

  if (queue->front == NULL) {
    queue->back = NULL;
  }

  coordinate = temp->coordinate;

  free(temp);
  return coordinate;
}

void printQueue(Queue* queue) {
  /*
    Print a given queue

    Parameter:
      queue: Queue to be printed
    
    Returns:
      Nothing
  */
  if (queue == NULL || queue->front == NULL) {
    printf("Queue is empty.\n");
    return;
  }

  QNode* current = queue->front;
  printf("Queue: ");

  while (current != NULL) {
    printf("(%d, %d) ", current->coordinate.x, current->coordinate.y);
    current = current->next;
  }

  printf("\n");
}

int isQEmpty(Queue* queue) {
  /*
    Checks if the queue is empty

    Parameter:
      queue: Queue to be checked

    Returns:
      1: Queue is empty
      0: Queue is not empty
  */
  return (queue == NULL || queue->front == NULL);
}

QNode* pop(Queue* queue) {
  /*
    Removing a node from the back of the queue

    Parameter:
      queue: Queue to which node is removed
    
    Returns:
      popped: Popped QNode
      NULL: Queue is empty
  */
  if (queue->front == NULL) {
    return NULL;
  }

  QNode* current = queue->front;
  QNode* prev = NULL;

  while (current->next != NULL) {
    prev = current;
    current = current->next;
  }

  QNode* popped = current;

  if (prev != NULL) {
    prev->next = NULL;
    queue->back = prev;
  } else {
    queue->front = NULL;
    queue->back = NULL;
  }

  return popped;
}

int getQueueLength(Queue* queue) {
  /*
    Get the length of the queue

    Parameter:
      queue: Queue to be calculated
    
    Returns:
      length: Length of queue
  */
  int length = 0;
  QNode* current = queue->front;

  while (current != NULL) {
    length++;
    current = current->next;
  }

  return length;
}