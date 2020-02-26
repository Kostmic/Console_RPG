
#ifndef RPG_LES02_PLAYERCHARACTER_H
#define RPG_LES02_PLAYERCHARACTER_H
#include <string>
#include <vector>

#include "Attack.h"
#include <iostream>

class PlayerCharacter {

public:
    PlayerCharacter(std::string name, int maxHp);

    std::vector<Attack*> attackVector;
    Attack* attackObj;

    void addAttack(std::string name, int damage, int cooldown);
    std::string getName();
    int getMaxHp();
    void getAttacks();
    int getCurrentHp();
    void hit(int damage);
    void decrementCooldowns();
    std::string runTurn(std::string playerTarget, std::string playerAction, int damage);

private:
    int m_maxHp;
    std::string m_name;
    int m_currentHp;


};


#endif //RPG_LES02_PLAYERCHARACTER_H
