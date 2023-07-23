#ifndef GAME_H
#define GAME_H

#include <conio.h> 
#include <ctype.h>
#include <time.h>

#include "linkedlist.h"
#include "player.h"
#include "queue.h"
#include "bot.h"
#include "utilities.h"
#include "file.h"

int readInstruction(void);
int gameTerminator(void);
void updateGameTimer(Maze* maze, time_t startingGameTime, int* continueGame, int* timeSpentInGame, int* prevTime, int* energyPoints, int* orbsCollected, double decrementRate, int gameStatus, int givenGameDuration);
void handleMoveLogic(Maze* maze, Coordinate* currentPosition, int* deadEndDetected, Node** movesMade, int* orbsCollected, int givenGameDuration, int gameStatus, int timeSpentInGame, int energyPoints);
void playGame(Maze* maze, Player* player, int givenGameDuration);
int handleGameChoice(void);
int calculateTime(int length);

#endif