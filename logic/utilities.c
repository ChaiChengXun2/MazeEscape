#include "../header/utilities.h"

char* getString(char* message) {
  /*
    Receive variable-length string input 

    Parameter:
      message: Message to prompt player

    Returns:
      str: Pointer to string
  */
  char* str = NULL;
  size_t size = 0;
  size_t length = 0;

  printf("%s", message);

  if (getline(&str, &size, stdin) == -1) {
    fprintf(stderr, "Error reading input.\n");
    exit(1);
  }

  length = strlen(str);
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }

  return str;
}

int validateChoice(int choice, int minRange, int maxRange) {
  /*
    Validate choices for menu

    Parameter:
      choice: Choice selected by player
      minRange: Takes the mininum acceptable menu choice input
      maxRange: Takes the maximum acceptable menu choice input

    Returns:
      choice: Choice is valid
      -1: Choice is not valid
  */
  if (choice >= minRange && choice <= maxRange) {
    return choice;
  } 
  return -1;
}

int menu(void) {
  /*
    Display the main menu and prompt the player to select an option

    Parameter:
      None
    
    Returns:
      choice: Choice selected by player
  */
  int choice = -1, inputStatus;

  do {
    printf("\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                       Menu                          |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|               1) Start New Game                     |\n");
    printf("|               2) View Statistics                    |\n");
    printf("|               0) Exit                               |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|      Enter Option: ");

    inputStatus = scanf("%d", &choice);

    if (inputStatus != 1 || validateChoice(choice, 0, 2) == -1) {
      printf("\nPlease enter valid menu choice.\n");
      while (getchar() != '\n') {
        continue;
      }
    }
  } while (validateChoice(choice, 0, 2) == -1);

  return choice;
}

void centeredPrint(char* string, int lengthOfGivenSpace) {
  /*
    Print a given string in the center of a given length

    Parameter: 
      string: String to be printed
      lengthOfGivenSpace: Length of the given space
    
    Returns:
      Nothing
  */
  int spacing = abs(lengthOfGivenSpace - strlen(string)) / 2;

  for (int i = 0; i < spacing; i++) {
    printf(" ");
  }
  printf("%s ", string);
  if (strlen(string) % 2 != 0) {
    printf(" ");
  } 
  for (int i = 0; i < spacing; i++) {
    printf(" ");
  }
}

void successfulGame(Player* player, int energy, int bfs) {
  /*
    Prints a summary of a player's game once a game has completed 

    Parameter: 
      player: Name of the player
      userMoves: Moves made by the player
      energy: Energy level of player at the end of the game
      bfs: Moves made by the bot 

    Returns:
      Nothing
  */
  char userMovesString[4], bfsString[4], energyString[4];

  sprintf(userMovesString, "%d", player->movesMade);
  sprintf(bfsString, "%d", bfs);
  sprintf(energyString, "%d", energy);

  printf("\n");
  printf("|-----------------------------------------------------|\n");

  printf("|");
  centeredPrint(player->name, 52);
  printf("|\n");

  printf("|-----------------------------------------------------|\n");
  printf("|   Player  | Number of Moves Made  |  Energy Points  |\n");
  printf("|-----------------------------------------------------|\n");

  printf("|     You   |");
  centeredPrint(userMovesString, 22);
  printf("|");
  centeredPrint(energyString, 16);
  printf("|\n");

  printf("|     Bot   |");
  centeredPrint(bfsString, 22);
  printf("|");
  centeredPrint("-", 16);
  printf("|\n");

  printf("|-----------------------------------------------------|\n");
  printf("|  For more detailed report, please View Statistics   |\n");
  printf("|-----------------------------------------------------|\n");
}

char* toStringLower(const char* string) {
  /*
    Converts any string to lowercase 

    Parameter:
      string: string to be converted

    Returns:
      lowered: Lower case string
  */
  int length = strlen(string);
  char* lowered = (char*)malloc((length + 1) * sizeof(char)); 

  if (lowered == NULL) {
    printf("Failed to allocate memory for new string.\n");
    return NULL;
  }

  for (int i = 0; i < length; i++) {
    lowered[i] = tolower(string[i]);
  }

  lowered[length] = '\0';

  return lowered;
}