#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_ROW 20
#define MAX_COLUMN 20
#define NUMBER_OF_DIRECTION 4
#define EMPTY '.' 
#define ENERGY '@'
#define START 'S'
#define END 'E'
#define WALL '#'
#define PATH '-'

typedef struct Coordinate {
  int x;
  int y;
} Coordinate;

typedef struct Maze {
  char cells[MAX_ROW][MAX_COLUMN];
  Coordinate start;
  Coordinate end;
} Maze;

Coordinate initialiseCoordinate(int x, int y);
Maze* initialiseMaze(void);
const Coordinate* getDirections(void);
int isWithinBounds(Coordinate coordinate);
void addEnergyOrbs(Maze* maze);
void randomisedDFS(Maze* maze, Coordinate currentCoordinate, Coordinate* lastCoordinate);
void printMaze(const Maze* maze, int status, int time, int points);
void randomlyDestroyWall(Maze* maze);
Maze* createMaze(void);
int isDeadEnd(int* possibleMoves, int size);
int isValidMove(Maze* maze, int x, int y);
int* possibleMoves(Maze* maze, Coordinate coordinate);
Maze* copyMaze(const Maze* original);

typedef struct Queue Queue; // forward declaration
int getQueueLength(Queue* queue); // forward declaration
Queue* bot(Maze* maze); // forward declaration

#endif