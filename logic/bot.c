#include "../header/bot.h"

int isCoordinateVisited(Queue* visitedQueue, Coordinate coordinate) {
  /*
    Checks if a specific coordinate has been visited in a given queue
    
    Parameter:
      visitedQueue: Queue containing all the visited coordinates
      coordinate: Coordinate to be checked

    Returns:
      1: Coordinate has been visited
      0: Coordinate has not been visited
  */
  QNode* current = visitedQueue->front;
  
  while (current != NULL) {
    if (current->coordinate.x == coordinate.x && current->coordinate.y == coordinate.y) {
      return 1; 
    }
    current = current->next;
  }
  
  return 0;
}

void addValidNeighbour(Maze* maze, Queue* queue, Queue* visitedQueue, Coordinate coordinate) {
  /*
    For a given coordinate, find all valid neighbours and add to queue and visited queue

    Valid is defined as a coordinate that is not a wall and not visited

    Parameters:
      maze: Maze structure
      queue: Queue used for Breadth-First Search (BFS)
      visitedQueue: Queue containing all the visited coordinates
      coordinate: Coordinate to find valid neighbours for

    Returns:
      Nothing
  */

  const Coordinate* directions = getDirections();

  for (int i = 0; i < 4; i++) {
    int newX = coordinate.x + directions[i].x;
    int newY = coordinate.y + directions[i].y;

    Coordinate newCoordinate = initialiseCoordinate(newX, newY);

    if (isWithinBounds(newCoordinate)) {
      if (maze->cells[newX][newY] != WALL && !isCoordinateVisited(visitedQueue, newCoordinate)) {
        enqueue(queue, newCoordinate, coordinate);
        enqueue(visitedQueue, newCoordinate, coordinate);
      }
    }
  }
}

Queue* getSolutionQ(Queue* visitedQueue, Maze* maze) {
  /*
    Retrieves the solution by tracing the path taken from start coordinate to end coordinate by BFS algorithmn
    
    Parameter:
      visitedQueue: Queue containing all the visited coordinates
      maze: Maze structure

    Returns:
      solution: Path taken by BFS algorithmn from start coordinate to end coordinate
      NULL: If no paths are found
  */
  Queue* solution = initialiseQueue();
  Coordinate endCoordinate = maze->end;

  while (!isQEmpty(visitedQueue)) {
    QNode* popped = pop(visitedQueue);

    if (popped->coordinate.x == endCoordinate.x && popped->coordinate.y == endCoordinate.y) {
      enqueue(solution, popped->coordinate, popped->parent);
      endCoordinate = popped->parent;
    }
  }

  return solution;
}

Queue* bot(Maze* maze) {
  /*
    Performs Breadth-First Search to find the shortest path in a given maze

    Parameters:
      maze: Maze structure

    Returns:
      solution: Path taken by BFS algorithmn from start coordinate to end coordinate
      NULL: If no paths are found
  */
  Queue* q = initialiseQueue();
  Queue* visited = initialiseQueue();

  Coordinate parent = initialiseCoordinate(-1, -1);
  enqueue(q, maze->start, parent);

  while (!isQEmpty(q)) {
    Coordinate coordinate = dequeue(q);

    if (coordinate.x == maze->end.x && coordinate.y == maze->end.y) {
      Queue* solution = getSolutionQ(visited, maze);
      return solution;
    } else {
      addValidNeighbour(maze, q, visited, coordinate);
    }
  }

  return NULL;
} 