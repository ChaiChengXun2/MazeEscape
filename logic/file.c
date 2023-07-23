#include "../header/file.h"

int handleStatChoice(void) {
  /*
    Logic to handle statistics choice

    Parameter:
      None

    Returns:
      choice: Choice selected by player
  */
  FileNode* fileData = readFile();

  int choice;
  int length = getFileLen(fileData);

  if (length == 0) {
    printTableHead();
    printVoid();
    return 0;
  }

  do {
    choice = fileOperationMenu();

    switch (choice) {
      case 1: {
        return 1;
      }
      case 2: {
        printFileList(fileData);
        break;
      }
      case 3: {
        handleSearchByName(fileData);
        break;
      }
      case 4: {
        FileNode* current = fileData;
        while (current != NULL) {
          bubbleSort(current->playerMoves);
          current = current->next;
        }
        mergeSort(&fileData, 1);
        printFileList(fileData);
        break;
      }
      case 5: {
        FileNode* current = fileData;
        while (current != NULL) {
          bubbleSort(current->botMoves);
          current = current->next;
        }
        mergeSort(&fileData, 0);
        printFileList(fileData);
        break;
      }
      default: choice = 0;
    }
  } while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5);

  return choice;
}

int fileOperationMenu(void) {
  /*
    Display the file operation menu and prompt the player to select an option

    Parameter:
      None
    
    Returns:
      choice: Choice selected by user
  */
  int choice = -1;
  int inputStatus;

  do {
    printf("\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                 File Operations                     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|               1) Back to Main Menu                  |\n");
    printf("|               2) View All                           |\n");
    printf("|               3) Search by Name                     |\n");
    printf("|               4) Sort by Player Moves               |\n");
    printf("|               5) Sort by Bot Moves                  |\n");
    printf("|               0) Exit                               |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      Enter Option: ");

    inputStatus = scanf("%d", &choice);

    if (inputStatus != 1 || validateChoice(choice, 0, 5) == -1) {
      printf("\nPlease enter valid menu choice.\n");
      while (getchar() != '\n') {
        continue;
      }
    }
  } while (validateChoice(choice, 0, 5) == -1);
  
  return choice;
}

void printTableHead(void) {
  /*
    Prints the head of statistics table 

    Parameter:
      None
    
    Returns:
      Nothing
  */
  printf("\n");
  printf("|-------------------------------------------------------------|\n");
  printf("|                         Statistics                          |\n");
  printf("|-------------------------------------------------------------|\n");
  printf("|             Player            | Player Moves  |  Bot Moves  |\n");
  printf("|-------------------------------------------------------------|\n");
}

void printTableRow(FileNode* playerInformation) {
  /*
    Prints each row in the table with corresponding data

    Parameter:
      name: Name of player
      playerMoves: Moves made by players
      botMoves: Moves made by bot
    
    Returns:
      Nothing
  */
  char playerMoveReader[4];
  char botMoveReader[4];

  int length = getMoveLen(playerInformation->botMoves);

  printf("|");
  centeredPrint(playerInformation->name, 30);
  printf("|");

  MoveNode* playerPtr = playerInformation->playerMoves;
  MoveNode* botPtr = playerInformation->botMoves;

  for (int i = 0; i < length; i++) {
    if (i > 0) {
      printf("|                               |");
    }

    if (playerInformation->playerMoves != NULL) {
      sprintf(playerMoveReader, "%d", playerPtr->moves);
      centeredPrint(playerMoveReader, 14);
      printf("|");
    } 

    if (playerInformation->botMoves != NULL) {
      sprintf(botMoveReader, "%d", botPtr->moves);
      centeredPrint(botMoveReader, 12);
      printf("|\n");
    } 

    playerPtr = playerPtr->next;
    botPtr = botPtr->next;
  }
  printf("|-------------------------------------------------------------|\n");
}

void searchByName(FileNode* linkedList, char* name) {
  /*
    Searches the file based on a name

    Parameter:
      linkedlist: List storing the file data
      name: Name that needs to be searched
    
    Returns:
      Nothing
  */
  int count = 0;

  printTableHead();
  while (linkedList != NULL) {
    if (strstr(toStringLower(linkedList->name), toStringLower(name)) != NULL) {
      count++; 
      printTableRow(linkedList);
    }
    linkedList = linkedList->next;
  } 

  if (count == 0) {
    printVoid();
  }
}

void handleSearchByName(FileNode* linkedList) {
  /*
    Handles logic when player wants to search database by name 

    Parameter:
      linkedlist: List storing the file data
    
    Returns:
      Nothing
  */
  while (getchar() != '\n') {
    continue;
  }
  char* name = getString("Enter name to search: ");

  searchByName(linkedList, name);
}

void printVoid(void) {
  /*
    Responsible for printing error message if no names are found
  */
  printf("|                  Sorry no players are found                 |\n");
  printf("|-------------------------------------------------------------|\n");
}