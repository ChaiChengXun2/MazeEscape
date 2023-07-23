#include "../header/game.h"

int readInstruction(void) {
  /*
    Forces players to read and understand instructions before proceeding

    Parameters:
      None
    
    Returns:
      1: If player has read and understood instructions
  */
  char choice;

  do {
    printf("\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                    Instruction                      |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|     Key     |               Action                  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      W      |                Up                     |\n");
    printf("|      A      |                Down                   |\n");
    printf("|      S      |                Left                   |\n");
    printf("|      D      |                Right                  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|    Boosts   |            Description                |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      @      |             +10 Points                |\n");
    printf("|             |             +3 Seconds                |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|   Penalty   |            Description                |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|   Dead End  |             -1 Point                  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      Do you understand? [y, n] ");

    scanf("%c", &choice);

    if (tolower(choice) != 'y') {
      printf("\nRead again if you don't understand.\n");
      while (getchar() != '\n') {
        continue;
      }
    }
  } while (tolower(choice) != 'y');

  return choice;
}

int gameTerminator(void) {
  /*
    Displays game terminator menu screen after a maze game has ended, allowing player to make choices
    
    Parameters:
      None
    
    Returns:
      1: Main menu choice 
      0: Exit choice 
  */
  int inputStatus, choice = -1;

  do {
    printf("\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                  Game has Ended                     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|               1) Back to Main Menu                  |\n");
    printf("|               0) Exit                               |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      Enter Option: ");

    inputStatus = scanf("%d", &choice);

    if (inputStatus != 1 || validateChoice(choice, 0, 1) == -1) {
      printf("\nPlease enter valid menu choice.\n");
      while (getchar() != '\n') {
        continue;
      }
    }
  } while (validateChoice(choice, 0, 1) == -1);
  
  return choice;
}

void updateGameTimer(Maze* maze, time_t startingGameTime, int* continueGame, int* timeSpentInGame, int* prevTime, int* energyPoints, int* orbsCollected, double decrementRate, int gameStatus, int givenGameDuration) {
  /*
    Handles the logic to update timer in game 
      Energy points will be gradually reduced
      Reduction of energy points will consider the amount of orbs collected as well
      Energy orbs adds more time to player's timer and also slow down the reduction of energy points
    
    Parameters:
      maze: Maze structure
      startingGameTime: Get the starting game time
      continueGame: References the continueGame variable   
      timeSpentInGame: References the timeSpentInGame variable  
      prevTime: References the prevTime variable   
      energyPoints: References the energyPoints variable  
      orbsCollected: References the orbsCollected variable  
      decrementRate: Get decrementRate variable value for calculation
      gameStatus: Get gameStatus variable value for calculation
      givenGameDuration: Get givenGameDuration variable value for calculation
    
    Returns:
      Nothing
  */
  time_t iterationTime = time(NULL);
  *timeSpentInGame = iterationTime - startingGameTime;

  if (*timeSpentInGame != *prevTime) {
    *prevTime = *timeSpentInGame;
    *energyPoints = (10 + (*orbsCollected * 10)) - (int)(decrementRate * (*timeSpentInGame));

    if (*energyPoints < 0) {
      *energyPoints = 0;
    }

    printMaze(maze, gameStatus, givenGameDuration - *timeSpentInGame, *energyPoints);
  }

  if (*timeSpentInGame > givenGameDuration - 1) {
    *continueGame = 0;
  }
}

void handleMoveLogic(Maze* maze, Coordinate* currentPosition, int* deadEndDetected, Node** movesMade, int* orbsCollected, int givenGameDuration, int gameStatus, int timeSpentInGame, int energyPoints) {
  /*
    Handle logic related to moving in a maze
      Only w, a, s and d are accepted
    
    Parameters:
      maze: Maze structure
      currentPosition: References the currentPosition variable
      deadEndDetected: References the deadEndDetected variable
      movesMade: References movesMade linked list 
      orbsCollected: References orbsCollected variable
      givenGameDuration: Get givenGameDuration value
      gameStatus: Get gameStatus value
      timeSpentInGame: Get timeSpentInGame value
      energyPoints: Get energyPoints value
    
    Returns:
      Nothing
  */
  char keyReader = getch();
  char validatedInput = tolower(keyReader);

  int* validMoves = possibleMoves(maze, *currentPosition);
  int newX = currentPosition->x, newY = currentPosition->y;
  int backwardMove = 0;

  if (validatedInput == 'w' && validMoves[0] || validatedInput == 'a' && validMoves[1] || validatedInput == 's' && validMoves[2] || validatedInput == 'd' && validMoves[3]) {

    appendNode(movesMade, validatedInput);

    if (validatedInput == 'w') {
      newX = currentPosition->x - 1;
    } else if (validatedInput == 'a') {
      newY = currentPosition->y - 1;
    } else if (validatedInput == 's') {
      newX = currentPosition->x + 1;
    } else if (validatedInput == 'd') {
      newY = currentPosition->y + 1;
    }

    if (maze->cells[newX][newY] == PATH || maze->cells[newX][newY] == START) {
      backwardMove = 1;
    }

    if (maze->cells[newX][newY] == ENERGY) {
      (*orbsCollected)++;
      givenGameDuration += 3;
    }

    if (backwardMove) {
      maze->cells[currentPosition->x][currentPosition->y] = EMPTY;
      backwardMove = 0;
    } else {
      if (maze->cells[newX][newY] != END && maze->cells[newX][newY] != START) {
        maze->cells[newX][newY] = PATH;
      }
    }

    currentPosition->x = newX;
    currentPosition->y = newY;

    int* deadEndDetection = possibleMoves(maze, *currentPosition);
    if (isDeadEnd(deadEndDetection, 4)) {
      printf("\nDEAD END DETECTED\n");
      (*deadEndDetected)++;
    }

    printf("\nYour Moves: ");
    printNodeList(*movesMade);

    printMaze(maze, gameStatus, givenGameDuration - timeSpentInGame, energyPoints);

    free(validMoves);
  }
}

void playGame(Maze* maze, Player* player, int givenGameDuration) {
  /*
    Handles logic to play game 
      Handles timer logic
      Handles moving in maze logic

    Parameters:
      maze: Maze structure
      player: player structure
      givenGameDuration: Estimated game duration given to players

    Returns:
      Nothing
  */ 
  Node* movesMade = NULL;
  Coordinate currentPosition = maze->start; 
  Maze* copy = copyMaze(maze);
  time_t gameStartTime = time(NULL);

  int continueGame = 1, gameStatus = 0, startTimer = 0;

  int bfs = getQueueLength(bot(copy));

  int timeSpentInGame, prevTime;
  double decrementRate = 10.0 / givenGameDuration;
  int energyPoints = 10, orbsCollected = 0, deadEndDetected = 0;

  do {
    if (startTimer) {
      updateGameTimer(maze, gameStartTime, &continueGame, &timeSpentInGame, &prevTime, &energyPoints, &orbsCollected, decrementRate, gameStatus, givenGameDuration);
    }

    if (kbhit()) {
      startTimer = 1;
      handleMoveLogic(maze, &currentPosition, &deadEndDetected, &movesMade, &orbsCollected, givenGameDuration, gameStatus, timeSpentInGame, energyPoints);

      if (maze->end.x == currentPosition.x && maze->end.y == currentPosition.y) {
        gameStatus = 1;
        continueGame = 0;
        startTimer = 0;
        energyPoints = energyPoints + 10 - deadEndDetected;

        printMaze(maze, gameStatus, -1, energyPoints);

        player->movesMade = getLen(movesMade);
        successfulGame(player, energyPoints, bfs);
        saveGame(player, bfs);
      }
    }
  } while (continueGame);

  free(copy);
  free(movesMade);
}

int handleGameChoice(void) {
  /*
    Handles logic when "Start New Game" is selected
      Initializes player
      Forces player to read instructions
      Display game level menu, allowing player to choose number of games to be played

    Parameter:
      None

    Returns:
      gameTerminator: Choice chosen from game terminator menu
  */
  Player* player = initialisePlayer();

  int understoodInstruction;
  do {
    understoodInstruction = readInstruction();
  } while (!understoodInstruction);

  Maze* maze = createMaze();
  int givenGameDuration = calculateTime(getQueueLength(bot(maze)));

  printf("Your Moves: ");
  printMaze(maze, 0, givenGameDuration, 10);

  playGame(maze, player, givenGameDuration);

  free(maze);
  free(player);

  return gameTerminator();
}

int calculateTime(int length) {
  /*
    Estimates how long a maze would take to solve

    Parameter:
      length: Number of moves made by bot to solve the maze
    
    Returns:
      estimated time
  */
  int movesPerSecond = 2;

  int padding = 0;
  if (length % movesPerSecond != 0) {
    padding = movesPerSecond - (length % movesPerSecond);
  }

  return (length + padding) / movesPerSecond;
}