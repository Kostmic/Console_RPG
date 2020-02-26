

#include <iostream>
#include "GameManager.h"
#include <string>
#include "PlayerCharacter.h"

void GameManager::startGame() {
    int playerClass;
    std::string playerName;

    std::cout << "Enter number of players:";
    std::cin >> players;
/*
    std::cout << "Enter number of CPUs:";
    std::cin >> autoPlayers;

    players += autoPlayers;
    */
    std::cout << std::endl << "Initializing " << players << " players..."<< '\n' << std::endl;


    for (int i = 1; i <= players; ++i) {
        std::cout << "Player Classes:\n"
                  << "1.Wizard\n"
                  << "2.Warrior\n"
                  << "3.Druid"
                  << std::endl;
        do {
            std::cout << "Pick player " << i << "'s class:" << std::endl;
            std::cin >> playerClass;
        } while (playerClass < 1 || playerClass > 3);

        std::cout << "Write player " << i << "'s name:" << std::endl;
        std::cin.get();
        getline(std::cin, playerName);

        switch (playerClass) {
            //Creating a Wizard
            case 1: {
                playerObj = new PlayerCharacter(playerName, 250);
                playerObj->PlayerCharacter::addAttack("Fireball", 20, 0);
                playerObj->PlayerCharacter::addAttack("Arcane Torrent", 50, 3);
                break;
            }
                //Creating a Warrior
            case 2: {
                playerObj = new PlayerCharacter(playerName, 450);
                playerObj->PlayerCharacter::addAttack("Slash", 15, 0);
                playerObj->PlayerCharacter::addAttack("Crippling strike", 40, 2);
                break;
            }
                //Creating a Druid
            case 3: {
                playerObj = new PlayerCharacter(playerName, 300);
                playerObj->PlayerCharacter::addAttack("Wrath", 25, 0);
                playerObj->PlayerCharacter::addAttack("Mighty Bash", 50, 2);
                break;
            }


        }
        playerVector.push_back(playerObj);

    }

    GameManager::run();
}

void GameManager::run() {
    std::vector<std::string> turnActions;
    std::string turnAction;

    int roundCounter = 1;
    int target;
    int damage;
    char newGame;

    while (playerVector.size() > 1) {
        std::cout << "Round " << roundCounter << " - player stats:" << std::endl;
        GameManager::printStats();

        for (j = 0; j < playerVector.size(); ++j) {
            std::cout << playerVector.at(j)->getName() << "'s Actions:  (Damage|Cooldown) (Remaining cooldown) " << std::endl;
            playerVector.at(j)->getAttacks();

            do {
                std::cout << playerVector.at(j)->getName() << ", pick your action:" << std::endl;
                std::cin >> action;
                action = action - 1;
                if (notValidInput()) {
                    std::cout << "This is not a valid input" << std::endl;
                }
                if(onCooldown()){
                    std::cout << "This attack is on cooldown!" << std::endl;
                }

                //Input can't be greater than attack vector size, negative or on cooldown
            } while (notValidInput()|| onCooldown());

            damage = playerVector.at(j)->attackVector.at(action)->getDamage();
            playerVector.at(j)->attackVector.at(action)->setCooldown();

            std::cout << "Targets: " << std::endl;
            GameManager::getTargets(j);

            do{
                std::cout << playerVector.at(j)->getName() << ", pick your target:" << std::endl;
                std::cin >> target;
            }
            //Input can't be negative, greater than player array or same as current player number
            while(target > playerVector.size() || target < 0 || target == j+1);

            target = target - 1;
            playerVector.at(target)->hit(damage);

            turnAction = playerVector.at(j)->runTurn(
                    playerVector.at(j)->getName(),
                    playerVector.at(target)->getName(),
                    damage);
            turnActions.push_back(turnAction);
        }

        //Prints actions taken during current turn
        for (int i = 0; i < turnActions.size(); ++i) {
            std::cout << turnActions.at(i) << std::endl;
        }
        turnActions.clear();

        //Checks if anyone is dead - remove them from playerVector
        for (int i = 0; i < playerVector.size(); ++i) {
            playerObj = playerVector.at(i);
            if (playerObj->getCurrentHp() <= 0) {
                std::cout << playerObj->getName() << " has been defeated - better luck next time!" << std::endl;
                playerVector.erase(playerVector.begin() + i);
            }
        }

        //Decrement remaining player's attacks' cooldowns
        for (int i = 0; i < playerVector.size(); ++i) {
            playerObj = playerVector.at(i);
            playerObj->decrementCooldowns();
        }

        std::cout << "-------------------" << std::endl;
        roundCounter++;

    }
    std::cout << playerVector.at(0)->getName() << " WON!";
    std::cout << "Do you want to play again? [y/n]" << std::endl;
    std::cin >> newGame;
    if (newGame == 121){
        m_newGame = true;
        playerVector.clear();
    }
}


void GameManager::printStats() {
    for (int i = 0; i < playerVector.size(); ++i) {
        playerObj = playerVector.at(i);
        std::cout
                << ' '
                << playerObj->getName()
                << " (#" << i + 1
                << "): "
                << playerObj->getCurrentHp()
                << '/'
                << playerObj->getMaxHp()
                << "HP"
                << std::endl;
    }
}

void GameManager::getTargets(int current) {
    for (int i = 0; i < playerVector.size(); ++i) {
        //We dont want to print the current player as a target, therefore we skip
        if (i == current) {
            continue;
        }
        playerObj = playerVector.at(i);
        std::cout
                << " "
                << i + 1
                << " - "
                << playerObj->getName()
                << std::endl;
    }
}

bool GameManager::getGameState(){
    return m_newGame;
}

bool GameManager::onCooldown() {
    return playerVector.at(j)->attackVector.at(action)->getCurrentCooldown() > 0;
}

bool GameManager::notValidInput(){
    return action >= playerVector.at(j)->attackVector.size()||action < 0;
}