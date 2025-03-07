
#ifndef RPG_LES02_PLAYERCHARACTER_H
#define RPG_LES02_PLAYERCHARACTER_H

#include <string>
#include <vector>

#include "Attack.h"
#include "HP.h"

class Character {

public:
    Character(std::string name, int maxHp, int ac);

    Character(std::string name, int maxHp);

    std::vector<Attack *> attackVector;
    Attack *attackObj;
    HP *playerHP;

    void addAttack(std::string name, int damage, int cooldown);

    std::string getName();

    int getMaxHp();

    void getAttacks();

    int getCurrentHp();

    int hit(int damage);

    void decrementCooldowns();

    std::string printTurn(std::string playerTarget, std::string playerAction, int damage);

    virtual bool isPlayer();


private:
    std::string m_name;
};


#endif //RPG_LES02_PLAYERCHARACTER_H
