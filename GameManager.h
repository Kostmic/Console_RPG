

#ifndef RPG_LES02_GAMEMANAGER_H
#define RPG_LES02_GAMEMANAGER_H

#include <string>
#include <vector>
#include "Character.h"

class GameManager {
public:
    GameManager() {};
    int playerClass;
    std::string playerName;

    std::vector<Character *> playerVector;
    Character *playerObj;

    int target;
    int action;
    int j;

    void startGame();

    bool getGameState();

    friend class Character;

private:
    int players;
    int autoPlayers;
    bool m_newGame = false;

    void run();

    void printStats();

    void getTargets(int currentPlayer);

    void initializePlayers();

    void initializeNPCs();

    bool onCooldown();

    bool notValidInput();
};


#endif //RPG_LES02_GAMEMANAGER_H
