//
// Created by Michael Kosther on 29/01/2020.
//

#ifndef RPG_LES02_ATTACK_H
#define RPG_LES02_ATTACK_H
#include <string>
#include <vector>

class Attack {
public:
    Attack(std::string name, int damage, int cooldown);
    std::string getName();
    int getDamage();
    int getMaxCooldown();
    bool isReady();
    int getCurrentCooldown();
    void decrementCooldown();
    void setCooldown();

    private:
    std::string m_name;
    int m_damage;
    int m_maxCooldown;
    int m_currentCooldown = 0;
};


#endif //RPG_LES02_ATTACK_H
