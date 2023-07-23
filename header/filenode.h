#ifndef FILENODE_H
#define FILENODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "movenode.h"
#include "player.h"

typedef struct Player Player;

typedef struct FileNode {
  char* name; 
  MoveNode* playerMoves;
  MoveNode* botMoves;
  struct FileNode* next;
} FileNode;

void saveGame(Player* player, int botMoves);
FileNode* newFileNode(const char* name, int playerMoves, int botMoves);
FileNode* readFile(void);
int searchNameIndex(FileNode* linkedList, const char* name);
int getFileLen(FileNode* linkedList);
void printFileList(FileNode* linkedList);
void read(FileNode** headRef, const char* name, int playerMoves, int botMoves);
void mergeSort(FileNode** headRef, int version);
FileNode* sortedMerge(FileNode* left, FileNode* right, int version);
void splitList(FileNode* source, FileNode** frontRef, FileNode** backRef);

#endif
