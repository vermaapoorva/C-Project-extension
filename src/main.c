#include "misc/defs.h"
#include "core_gameplay/game_states.h"
#include "objects/init.h"
#include "objects/destroy.h"

int main(int argc, char *argv[]) {

  init_game();

  game_state next_state = main_menu();

  while (true) {

    switch (next_state) {
      case MENU:
        next_state = main_menu();
        break;
      case SINGLE_PLAYER:
        next_state = in_game(0, select_difficulty());
        break;
      case TWO_PLAYER:
        next_state = in_game(1, 0);
        break;
      case NONE:
      default:
        close_game();
    }

  }

  return 0;
}
