

#ifndef CONSOLE_RPG_NPCCHARACTER_H
#define CONSOLE_RPG_NPCCHARACTER_H


#include <string>
#include "Character.h"

class NPCCharacter : public Character {
public:
    NPCCharacter(std::string name, int maxHp, int ac, bool isPlayer);

    NPCCharacter(std::string name, int maxHp, bool isPlayer);

    bool isPlayer() override;

private:
    bool m_isPlayer;
};


#endif //CONSOLE_RPG_NPCCHARACTER_H
