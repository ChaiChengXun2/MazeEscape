#include "header/bot.h"
#include "header/file.h"
#include "header/filenode.h"
#include "header/game.h"
#include "header/linkedlist.h"
#include "header/maze.h"
#include "header/player.h"
#include "header/queue.h"
#include "header/utilities.h"
#include "header/filenode.h"

void main() {
  int menuChoice;

  do {
    menuChoice = menu();

    switch (menuChoice) {
      case 1: {
        menuChoice = handleGameChoice();
        break;
      }
      case 2: {
        menuChoice = handleStatChoice();
        break;
      }
      default: menuChoice = 0;
    }
  } while (menuChoice == 1 || menuChoice == 2);
}