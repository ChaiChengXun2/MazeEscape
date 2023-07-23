#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "linkedlist.h"
#include "utilities.h"

typedef struct Player {
  char* name;
  int movesMade; 
} Player;

Player* initialisePlayer(void);

#endif