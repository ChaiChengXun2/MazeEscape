#include "../header/filenode.h"

FileNode* newFileNode (const char* name, int playerMoves, int botMoves) {
  /*
    Creating a new file node

    Parameter:
      name: Name of the player
      playerMoves: Number of moves taken by player
      botMoves: Number of moves taken by bot
    
    Returns:
      newNode: Newly created file node
  */
  FileNode* newNode = (FileNode* )malloc(sizeof(FileNode));

  if (newNode == NULL) {
    printf("\nFailed to allocate memory for a new node.\n");
    return NULL;
  }

  newNode->name = malloc(strlen(name) + 1);
  if (newNode->name == NULL) {
    printf("\nFailed to allocate memory for the name.\n");
    free(newNode);
    return NULL;
  }

  if (strcpy(newNode->name, name) == NULL) {
    printf("\nFailed to copy the name.\n");
    free(newNode->name); 
    free(newNode); 
    return NULL;
  }

  newNode->playerMoves = (MoveNode* )malloc(sizeof(MoveNode));
  newNode->botMoves = (MoveNode* )malloc(sizeof(MoveNode));

  if (newNode->playerMoves == NULL) {
    printf("\nFailed to allocate memory for a new node.\n");
    return NULL;
  } 

  if (newNode->botMoves == NULL) {
    printf("\nFailed to allocate memory for a new node.\n");
    return NULL;
  } 

  newNode->playerMoves = NULL;
  newNode->botMoves = NULL;

  appendMoveNode(&(newNode->playerMoves), playerMoves);
  appendMoveNode(&(newNode->botMoves), botMoves);
  newNode->next = NULL;

  return newNode;
}

void read(FileNode** headRef, const char* name, int playerMoves, int botMoves) {
  /*
    Storing each row of data into file node structure

    Parameter:
      headRef: Pointer reference to the head of the linked list
      name: Name of the player
      playerMoves: Moves taken by player
      botMoves: Moves taken by bot

    Returns:
      Nothing
  */
  int findPlayerIndex = searchNameIndex(*headRef, name);
  
  if (findPlayerIndex != -1) {
    FileNode* head = *headRef;
    for (int i = 0; i < findPlayerIndex; i++) {
      head = head->next;
    }

    appendMoveNode(&(head->playerMoves), playerMoves);
    appendMoveNode(&(head->botMoves), botMoves);
  } else {
    FileNode* newNode = newFileNode(name, playerMoves, botMoves);

    if (*headRef == NULL) {
      *headRef = newNode;
      return;
    }

    FileNode* last = *headRef;
    while (last->next != NULL) {
      last = last->next;
    }
    last->next = newNode;
  }
}

void printFileList(FileNode* linkedList) {
  /*
    Prints contents of Linked List

    Paramter:
      linkedList: Linked List to be printed

    Returns:
      Nothing
  */
  printTableHead();
	while (linkedList != NULL) {
    printTableRow(linkedList);
		linkedList = linkedList->next;
	} 
}

void mergeSort(FileNode** headRef, int version) {
  /*
    Merge sort algorithmn

    Parameter:
      headRef: References the linked list
      version: sort by player moves or bot moves
    
    Returns:
      Nothing
  */
  FileNode* head = *headRef;
  FileNode* left;
  FileNode* right;

  if ((head == NULL) || (head->next == NULL)) {
    return;
  }

  splitList(head, &left, &right);

  mergeSort(&left, version);
  mergeSort(&right, version);

  *headRef = sortedMerge(left, right, version);
}
 
FileNode* sortedMerge(FileNode* left, FileNode* right, int version) {
  /*
    Sorts smaller linked list 

    Parameter:
      left: References the left linked list
      right: References the right linked list 
      version: sort by player moves or bot moves
    
    Returns:
      result: Sorted linked list
  */
  FileNode* result = NULL;

  if (left == NULL) {
    return right;
  }
  else if (right == NULL) {
    return left;
  }

  if (version == 1) {
      if (left->playerMoves->moves <= right->playerMoves->moves) {
      result = left;
      result->next = sortedMerge(left->next, right, version);
    } else {
      result = right;
      result->next = sortedMerge(left, right->next, version);
    }
  } else {
      if (left->botMoves->moves <= right->botMoves->moves) {
      result = left;
      result->next = sortedMerge(left->next, right, version);
    } else {
      result = right;
      result->next = sortedMerge(left, right->next, version);
    }
  }
  return (result);
}
 
void splitList(FileNode* source, FileNode** leftRef, FileNode** rightRef) {
  /*
    Responsible for splitting the linked list into smaller and smaller linked lists 

    Parameters:
      source: The source linked list for traversal
      leftRef: References the left linked list
      rightRef: Refernces the right linked list
    
    Returns:
      Nothing
  */
  FileNode* fast;
  FileNode* slow;
  slow = source;
  fast = source->next;

  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  *leftRef = source;
  *rightRef = slow->next;
  slow->next = NULL;
}

int getFileLen(FileNode* linkedList) {
  /*
    Calculate the length of a given Linked List

    Parameter:
      linkedList: Linked List to be calculated

    Returns:
      count: Length of the linked list
  */
  int count = 0; 

  FileNode* current = linkedList; 
  while (current != NULL)
  {
    count++;
    current = current->next;
  }
  return count;
}

int searchNameIndex(FileNode* linkedList, const char* name) {
  /*
    Searches for the index of a name in a file node linked list

    Parameter:
      linkedlist: List storing the file data
      name: Name that needs to be searched
    
    Returns:
      count: 
        count: Index of a name if found 
        -1: Name not found
  */
  int count = 0;

  while (linkedList != NULL) {
    if (strcmp(toStringLower(linkedList->name), toStringLower(name)) == 0) {
      return count;
    }
    count++; 
    linkedList = linkedList->next;
  } 

  return -1;
}

void saveGame(Player* player, int botMoves) {
  /*
    Saves game information into file

    Parameter:
      player: Player structure
      botMoves: Moves made by bot
    
    Returns:
      Nothing
  */
  FILE* filePointer;
  filePointer = fopen("./data.txt", "a");
  if (filePointer == NULL) {
    printf("\nSomething went wrong.\n");
    exit(0);
  } else {
    fprintf(filePointer, "%s, %d | %d\n", player->name, player->movesMade, botMoves);
  }

  fclose(filePointer);
}

FileNode* readFile(void) {
  /*
    Reads a file and stores it in a linked list

    Parameter:
      None
    
    Returns:
      newlist: Contents from the file in the form of a linked list
  */
  FILE *file;
  char name[100];
  int playerMoves, botMoves, length = 0;

  file = fopen("data.txt", "r");  

  FileNode* newList = NULL;

  if (file == NULL) {
    printf("\nFailed to open the file.\n");
    exit(0);
  }

  while (fscanf(file, " %[^,\n], %d | %d", name, &playerMoves, &botMoves) == 3) {
    read(&newList, name, playerMoves, botMoves);
    length++;
  }

  fclose(file);

  return newList;
}