#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "filenode.h"
#include "movenode.h"

typedef struct Player Player; // Forward declaration
typedef struct FileNode FileNode;

int handleStatChoice(void);
int fileOperationMenu(void);
void searchByName(FileNode* linkedList, char* name);
void handleSearchByName(FileNode* linkedList);
void printTableHead(void);
void printTableRow(FileNode* playerInformation);
void printVoid(void);

#endif
