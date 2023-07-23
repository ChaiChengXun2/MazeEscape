#include "../header/player.h"

Player* initialisePlayer(void) {
  /*
    Initialising a player with a name and setting movesMade to NULL
    
    Parameters:
      None
    
    Returns:
      player: Pointer to Player structure
      NULL: Malloc failed to provide memory required
  */
  Player* player = (Player* )malloc(sizeof(Player));

  if (player == NULL) {
    printf("Failed to allocate memory for a new player.\n");
    return NULL;
  }

  while (getchar() != '\n') {
    continue;
  }
  char *playerName = getString("\nEnter your name: ");
  player->name = playerName; 
  player->movesMade = 0;

  return player;
}