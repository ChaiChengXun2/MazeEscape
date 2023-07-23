#include "../header/maze.h"

Coordinate initialiseCoordinate(int x, int y) {
  /*
    Creates a coordinate with x and y value

    Parameter:
      x: X value of coordinate
      y: Y value of coordinate

    Returns:
      coordinate: Newly created coordinate
  */
  Coordinate coordinate; 
  coordinate.x = x;
  coordinate.y = y; 

  return coordinate;
}

Maze* initialiseMaze(void) {
  /*
    Initialising a maze full of walls

    Parameters:
      None

    Returns:
      maze: Pointer to initialized maze
      NULL: Malloc failed to provide memory required
  */
  Maze* maze = (Maze* )malloc(sizeof(Maze));

  if (maze == NULL) {
    printf("Failed to allocate memory for a maze.\n");
    return NULL;
  }

  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j < MAX_COLUMN; j++) {
      maze->cells[i][j] = WALL;
    }
  }
  return maze; 
}

const Coordinate* getDirections(void) {
  /*
    Returns an array of directions representing w, a, s and d 

    Parameter:
      None

    Returns:
      directions: Array of directions representing w, a, s and d 
  */
  static const Coordinate directions[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
  };
  
  return directions;
}

int isWithinBounds(Coordinate coordinate) {
  /*
    Check if a given coordinate is within the maze

    Parameter:
      coordinate: Coordinate to be checked
    
    Returns:
      1: Coordinate is within bounds
      0: Coordinate is not within bounds
  */
  return (coordinate.x >= 0 && coordinate.x < MAX_ROW && coordinate.y >= 0 && coordinate.y < MAX_COLUMN);
}

void addEnergyOrbs(Maze* maze) {
  /*
    CHANGE THIS
  */
  int iteration, radius = 5;
  int numberOfMove = getQueueLength(bot(maze));

  if (numberOfMove < 35) {
    iteration = 1;
  } else if (numberOfMove < 55) {
    iteration = 2;
  } else if (numberOfMove < 75) {
    iteration = 3;
    radius = 6;
  } else {
    iteration = 4;
    radius = 6;
  }

  srand(time(NULL));
  
  while (iteration > 0) {
    int randomX = rand() % MAX_ROW;
    int randomY = rand() % MAX_COLUMN;
    Coordinate energyOrb = initialiseCoordinate(randomX, randomY);

    if (isWithinBounds(energyOrb) && maze->cells[energyOrb.x][energyOrb.y] == EMPTY) {
      if ((abs(randomX - maze->start.x) <= radius && abs(randomY - maze->start.y) <= radius) || (abs(randomX - maze->end.x) <= radius && abs(randomY - maze->end.y) <= radius)) {
        maze->cells[energyOrb.x][energyOrb.y] = ENERGY;
        iteration--; 
      }
    }
  }
}

void randomisedDFS(Maze* maze, Coordinate currentCoordinate, Coordinate* lastCoordinate) {
  /*
    Using Depth-First Search (DFS) to create a perfect maze
    Perfect maze = a maze with only one solution

    Parameters:
      maze: A maze full of walls
      currentCoordinate: The coordinate that DFS starts from
      lastCoordinate: The last coordinate accessed by the DFS

    Returns:
      Nothing
  */
  maze->cells[currentCoordinate.x][currentCoordinate.y] = EMPTY;

  int randomizedDirections[NUMBER_OF_DIRECTION] = {0, 1, 2, 3};
  for (int i = 0; i < NUMBER_OF_DIRECTION; i++) {
    int j = rand() % NUMBER_OF_DIRECTION;
    int temp = randomizedDirections[i];
    randomizedDirections[i] = randomizedDirections[j];
    randomizedDirections[j] = temp;
  }

  const Coordinate* directions = getDirections();

  for (int i = 0; i < NUMBER_OF_DIRECTION; ++i) {
    Coordinate randomDirection = directions[randomizedDirections[i]];

    int nextRow = currentCoordinate.x + randomDirection.x * 2;
    int nextCol = currentCoordinate.y + randomDirection.y * 2;

    Coordinate nextCoordinate = initialiseCoordinate(nextRow, nextCol);

    if (isWithinBounds(nextCoordinate) && maze->cells[nextCoordinate.x][nextCoordinate.y] == WALL) {
      int wallRow = currentCoordinate.x + randomDirection.x;
      int wallCol = currentCoordinate.y + randomDirection.y;
      maze->cells[wallRow][wallCol] = EMPTY;
      maze->cells[nextRow][nextCol] = EMPTY;
      *lastCoordinate = nextCoordinate;
      randomisedDFS(maze, nextCoordinate, lastCoordinate);
    }
  }
}

void printMaze(const Maze* maze, int status, int time, int points) {
  /*
    Print a given maze

    Parameters:
      maze: Maze structure
      status: Status of a game
        1: Game finished
        0: Game still in progress
    
    Returns:
      Nothing
  */
  printf("\n\n# # # # # # # # # # # # # # # # # # # # # # \n");
  for (int i = 0; i < MAX_ROW; i++) {
    printf("# ");
    for (int j = 0; j < MAX_COLUMN; j++) {
      char cell = maze->cells[i][j];
      if (cell == START || cell == END || cell == PATH || cell == ENERGY) {
        printf(status == 1 ? "\033[32m%c\033[0m " : "\033[31m%c\033[0m ", cell);
      } else {
        printf("%c ", cell);
      }
    }

    if (i == MAX_ROW - 12) {
      printf("# ");
      if (time == -1) {
        printf("   Game Over!\n");
      } else {
        printf("   Time Remaining: %d seconds\n", time);
      }
    } else if (i == MAX_ROW - 13) {
      printf("# ");
      printf("   Energy points: %d\n", points);
    } else {
      printf("#\n");
    }
  }
  printf("# # # # # # # # # # # # # # # # # # # # # # \n");
}

void randomlyDestroyWall(Maze* maze) {
  /*
    Randomly destroys walls in the maze in hopes to create multiple paths from S to E
    Uses the heuristic distance between S and E to determine where to destory walls
    Uses the number of moves from the original maze to destroy a variable number of walls

    Parameters:
      maze: Maze structure
      iteration: Number of walls to destroy
    
    Returns:
      Nothing
  */
  int iteration;
  int numberOfMove = getQueueLength(bot(maze));

  if (numberOfMove < 15) {
    iteration = 0;
  } else if (numberOfMove < 35) {
    iteration = 1;
  } else if (numberOfMove < 50) {
    iteration = 2;
  } else {
    iteration = 3;
  }

  srand(time(NULL));
  
  int distanceSE = abs(maze->start.x - maze->end.x) + abs(maze->start.y - maze->end.y);
  
  int minDistance = distanceSE / MAX_COLUMN + 4; 
  int maxDistance = distanceSE / MAX_COLUMN + 10; 
  
  while (iteration > 0) {
    int randomX = rand() % MAX_ROW;
    int randomY = rand() % MAX_COLUMN;

    if (maze->cells[randomX][randomY] == WALL) {
      int distanceFromStart = abs(randomX - maze->start.x) + abs(randomY - maze->start.y);
      int distanceFromEnd = abs(randomX - maze->end.x) + abs(randomY - maze->end.y);

      if ((distanceFromStart >= minDistance && distanceFromStart <= maxDistance) || (distanceFromEnd >= minDistance && distanceFromEnd <= maxDistance)) {
        maze->cells[randomX][randomY] = EMPTY;
        iteration--;
      }
    }
  }
}

Maze* createMaze(void) {
  /*
    Handles logic to create a maze
      Initialise maze
      Carve path using DFS
      Destroying random walls in hopes to create multiple solutions in maze
    
    Parameters:
      None
    
    Returns:
      maze: Pointer to created maze
      NULL: Malloc failed to provide memory required
  */
  Maze* maze = initialiseMaze();

  Coordinate possibleStart[4] = {{0, 0}, {0, MAX_COLUMN - 1}, {MAX_ROW - 1, 0}, {MAX_ROW - 1, MAX_COLUMN - 1}};
  Coordinate endCoordinate = initialiseCoordinate(-1, -1);

  srand(time(NULL));
  int randomStart = rand() % 4; 

  Coordinate start = initialiseCoordinate(possibleStart[randomStart].x, possibleStart[randomStart].y);

  randomisedDFS(maze, start, &endCoordinate);

  maze->cells[endCoordinate.x][endCoordinate.y] = END; 
  maze->cells[start.x][start.y] = START;

  maze->start = start; 
  maze->end = endCoordinate;

  randomlyDestroyWall(maze);
  addEnergyOrbs(maze);

  return maze;
}

int isValidMove(Maze* maze, int x, int y) {
  /*
    Checks if the cell at the given coordinates is a valid move
    The valid moves are '.', 'E', and '-'

    Parameters:
      maze: Maze structure
      x: X-coordinate of the cell
      y: Y-coordinate of the cell

    Returns:
      1: If the cell is a valid move
      0: If the cell is not a valid move
  */

  return (maze->cells[x][y] == EMPTY || maze->cells[x][y] == END || maze->cells[x][y] == PATH || maze->cells[x][y] == ENERGY);
}

int* possibleMoves(Maze* maze, Coordinate coordinate) {
  /*
    Determines all possible and valid moves for a given coordinate

    Parameters:
      maze: Maze structure
      coordinate: Coordinate to find valid moves for

    Returns:
      directions: Pointer to an array containing all possible moves
      NULL: Malloc failed to provide memory required
  */
  int x = coordinate.x;
  int y = coordinate.y;

  int* directions = (int *)malloc(4 * sizeof(int));

  if (directions == NULL) {
    printf("Failed to allocate memory for directions.\n");
    return NULL;
  }

  directions[0] = (x - 1 >= 0) && isValidMove(maze, x - 1, y); // w
  directions[1] = (y - 1 >= 0) && isValidMove(maze, x, y - 1); // a
  directions[2] = (x + 1 < MAX_ROW) && isValidMove(maze, x + 1, y); // s
  directions[3] = (y + 1 < MAX_COLUMN) && isValidMove(maze, x, y + 1); // d

  return directions;
}

Maze* copyMaze(const Maze* original) {
  /*
    Create a copy for a given maze

    Parameter:
      original: Original maze to be copied

    Returns:
      copy: Pointer to copied maze
      NULL: Malloc failed to provide memory required
  */
  Maze* copy = (Maze*)malloc(sizeof(Maze));

  if (copy == NULL) {
    printf("Failed to allocate memory for maze.\n");
    return NULL;
  }

  memcpy(&copy->start, &original->start, 2 * sizeof(Coordinate));
  memcpy(&copy->start, &original->start, 2 * sizeof(Coordinate));
  memcpy(copy->cells, original->cells, MAX_ROW * MAX_COLUMN);

  return copy;
}

int isDeadEnd(int* possibleMoves, int size) {
  /*
    Checks if a given possibleMoves array is a dead end
    Dead end is defined as a situation in a maze where there is only one possible move, albeit w, a, s or d

    Parameter:
      possilbeMoves: The array to be checked
      size: Size of the array
    
    Returns:
      isTrue: Whether a given array is a dead end
  */
  int isTrue = 0;

  for (int i = 0; i < size; i++) {
    if (possibleMoves[i] == 1) {
      isTrue++; 
    }
  }

  return (isTrue == 1);
}