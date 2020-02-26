//
// Created by Michael Kosther on 29/01/2020.
//

#ifndef RPG_LES02_GAMEMANAGER_H
#define RPG_LES02_GAMEMANAGER_H
#include <string>
#include <vector>
#include "PlayerCharacter.h"

class GameManager {
public:
    GameManager(){};
    std::vector<PlayerCharacter *> playerVector;
    PlayerCharacter *playerObj;


    void startGame();
    bool getGameState();

private:
    int players;
    int autoPlayers;
    bool m_newGame = false;
    void run();
    void printStats();
    void getTargets(int currentPlayer);
};


#endif //RPG_LES02_GAMEMANAGER_H
