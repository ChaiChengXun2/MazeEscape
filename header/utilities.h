#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

#include "player.h"
#include "file.h"

typedef struct Player Player; // forward declaration

char* getString(char* message);
int validateChoice(int choice, int minRange, int maxRange);
int menu(void);
void centeredPrint(char* string, int lengthOfGivenSpace);
void successfulGame(Player* player, int energy, int bfs);
char* toStringLower(const char* string);

#endif