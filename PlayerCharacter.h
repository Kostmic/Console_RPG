#ifndef CONSOLE_RPG_PLAYERCHARACTER_H
#define CONSOLE_RPG_PLAYERCHARACTER_H


#include "Character.h"

class PlayerCharacter : public Character {
public:
    PlayerCharacter(std::string name, int maxHp, int ac);

    PlayerCharacter(std::string name, int maxHp);
};


#endif //CONSOLE_RPG_PLAYERCHARACTER_H