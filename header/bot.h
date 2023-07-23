#ifndef BOT_H
#define BOT_H

#include "queue.h"
#include "maze.h"

int isCoordinateVisited(Queue* visitedQueue, Coordinate coordinate);
void addValidNeighbour(Maze* maze, Queue* queue, Queue* visitedQueue, Coordinate coordinate);
Queue* getSolutionQ(Queue* visitedQueue, Maze* maze);
Queue* bot(Maze* maze);

#endif