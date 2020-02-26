#include <iostream>
#include "GameManager.h"
int main() {
    while (true) {
        GameManager game;
        game.startGame();

        //If the player doesn't want to play anymore we break the while-loop
        if (game.getGameState() == false) {
            break;
        }
    }
    return 0;
}