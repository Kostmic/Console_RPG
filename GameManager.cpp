

#include <iostream>
#include "GameManager.h"
#include <string>
#include <random>
#include "Character.h"
#include "NPCCharacter.h"
#include "PlayerCharacter.h"

void GameManager::startGame() {
    do {
        std::cout << "Enter number of players:";
        std::cin >> players;
        if (players > 20) {
            std::cout << "Do you seriously have this many friends? (20 players max)" << std::endl;
        }
    } while (players < 0 || players > 20);
    do {
        std::cout << "Enter number of CPUs:";
        std::cin >> autoPlayers;
        if (players > 20) {
            std::cout << "Why would you ever need this many CPUs? (20 CPUs max";
        }
    } while (players < 0 || players > 20);

    std::cout << std::endl << "Initializing " << players + autoPlayers << " players..." << '\n' << std::endl;


    GameManager::initializePlayers();
    if (autoPlayers > 0) {
        GameManager::initializeNPCs();
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
            std::cout << playerVector.at(j)->getName() << "'s Actions:  (Damage|Cooldown) (Remaining cooldown) "
                      << std::endl;
            playerVector.at(j)->getAttacks();

            if (playerVector.at(j)->isPlayer()) {
                do {
                    std::cout << playerVector.at(j)->getName() << ", pick your action:" << std::endl;
                    std::cin >> action;
                    action = action - 1;
                    if (notValidInput()) {
                        std::cout << "This is not a valid input" << std::endl;
                    }
                    if (onCooldown()) {
                        std::cout << "This attack is on cooldown!" << std::endl;
                    }

                    //Input can't be greater than attack vector size, negative or on cooldown
                } while (notValidInput() || onCooldown());
                //CPU picking target, this is done by generating a random number. If attack is on cooldown new number is generated
            } else {
                std::cout << playerVector.at(j)->getName() << ", pick your action:" << std::endl;
                std::random_device rd;
                std::mt19937 mt(rd());
                do {
                    std::uniform_real_distribution<double> dist(0.0, playerVector.at(j)->attackVector.size());
                    action = dist(mt);
                } while (onCooldown());
                std::cout << action + 1 << std::endl;
            }

            damage = playerVector.at(j)->attackVector.at(action)->getDamage();
            playerVector.at(j)->attackVector.at(action)->setCooldown();

            std::cout << "Targets: " << std::endl;
            //If it's a heal we only want to print the current player as a target
            if (damage < 0) {
                playerObj = playerVector.at(j);
                std::cout
                        << " "
                        << j + 1
                        << " - "
                        << playerObj->getName()
                        << std::endl;;
            } else {
                GameManager::getTargets(j);
            }

            //if it's a player we want to check input
            if (playerVector.at(j)->isPlayer()) {
                do {
                    std::cout << playerVector.at(j)->getName() << ", pick your target:" << std::endl;
                    std::cin >> target;
                    target = target - 1;
                }
                    //Input can't be negative, greater than player array or same as current player number(target yourself)
                    //if damage < 0 (heal) we only want to be able to target ourself
                while ((damage > 0 && (target > playerVector.size() || target < 0 || target == j)) ||
                       (damage < 0 && target != j));
            }
                //If it's a cpu we dont need check. Generate a random number
            else {
                std::cout << playerVector.at(j)->getName() << ", pick your target:" << std::endl;
                std::random_device rd;
                std::mt19937 mt(rd());
                //if cpu generates number to target itself we want to generate a new number(if it isn't a heal)
                do {
                    std::uniform_real_distribution<double> dist(0.0, playerVector.size());
                    target = dist(mt);
                } while ((damage > 0 && target == j) || (damage < 0 && target != j));
                std::cout << target + 1 << std::endl;
            }

            damage = playerVector.at(target)->hit(damage);

            turnAction = playerVector.at(j)->printTurn(
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

        std::cout << "----------------------------------------" << std::endl;
        roundCounter++;

    }
    std::cout << playerVector.at(0)->getName() << " WON!" << std::endl;
    std::cout << "Do you want to play again? [y/n]" << std::endl;
    std::cin >> newGame;
    if (newGame == 121) {
        m_newGame = true;
        playerVector.clear();
    }
}


void GameManager::initializePlayers() {
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
                playerObj->Character::addAttack("Fireball", 20, 0);
                playerObj->Character::addAttack("Arcane Torrent", 50, 3);
                break;
            }
                //Creating a Warrior
            case 2: {
                playerObj = new PlayerCharacter(playerName, 450, 3);
                playerObj->Character::addAttack("Slash", 15, 0);
                playerObj->Character::addAttack("Crippling strike", 40, 2);
                break;
            }
                //Creating a Druid
            case 3: {
                playerObj = new PlayerCharacter(playerName, 300, 0);
                playerObj->Character::addAttack("Wrath", 25, 0);
                playerObj->Character::addAttack("Mighty Bash", 50, 2);
                playerObj->Character::addAttack("Healing Touch", -15, 0);
                break;
            }


        }
        playerVector.push_back(playerObj);

    }
}

void GameManager::initializeNPCs() {
    for (int i = 1; i <= autoPlayers; ++i) {
        std::cout << "Player Classes:\n"
                  << "1.Wizard\n"
                  << "2.Warrior\n"
                  << "3.Druid"
                  << std::endl;
        do {
            std::cout << "Pick NPC " << i << "'s class:" << std::endl;
            std::cin >> playerClass;
        } while (playerClass < 1 || playerClass > 3);

        std::cout << "Write NPC " << i << "'s name:" << std::endl;
        std::cin.get();
        getline(std::cin, playerName);

        switch (playerClass) {
            //Creating a Wizard
            case 1: {
                playerObj = new NPCCharacter(playerName, 250, false);
                playerObj->NPCCharacter::addAttack("Fireball", 20, 0);
                playerObj->NPCCharacter::addAttack("Arcane Torrent", 50, 3);
                break;
            }
                //Creating a Warrior
            case 2: {
                playerObj = new NPCCharacter(playerName, 450, 5, false);
                playerObj->NPCCharacter::addAttack("Slash", 15, 0);
                playerObj->NPCCharacter::addAttack("Crippling strike", 40, 2);
                break;
            }
                //Creating a Druid
            case 3: {
                playerObj = new NPCCharacter(playerName, 300, 0, false);
                playerObj->NPCCharacter::addAttack("Wrath", 25, 0);
                playerObj->NPCCharacter::addAttack("Mighty Bash", 50, 2);
                playerObj->Character::addAttack("Healing Touch", -15, 0);
                break;
            }


        }
        playerVector.push_back(playerObj);

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
                << "HP";
        if (playerVector.at(i)->isPlayer() == false) {
            std::cout << " [CPU]";
        }
        std::cout << std::endl;
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


bool GameManager::getGameState() {
    return m_newGame;
}

bool GameManager::onCooldown() {
    return playerVector.at(j)->attackVector.at(action)->getCurrentCooldown() > 0;
}

bool GameManager::notValidInput() {
    return action > playerVector.at(j)->attackVector.size() || action < 0;
}