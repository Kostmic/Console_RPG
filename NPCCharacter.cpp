

#include "NPCCharacter.h"

NPCCharacter::NPCCharacter(std::string name, int maxHp, int ac, bool isPlayer) : Character{name, maxHp, ac} {
    m_isPlayer = isPlayer;
}

NPCCharacter::NPCCharacter(std::string name, int maxHp, bool isPlayer) : Character{name, maxHp}{
    m_isPlayer = isPlayer;
}

bool NPCCharacter::isPlayer(){
    return m_isPlayer;
}

