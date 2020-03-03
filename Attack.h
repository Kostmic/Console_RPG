#ifndef RPG_LES02_ATTACK_H
#define RPG_LES02_ATTACK_H

#include <string>

class Attack {
public:
    Attack(std::string name, int damage, int cooldown);

    std::string getName();

    int getDamage();

    int getMaxCooldown();

    int getCurrentCooldown();

    void decrementCooldown();

    void setCooldown();

private:
    std::string m_name;
    int m_damage;
    int m_maxCooldown;
    int m_currentCooldown;
};


#endif //RPG_LES02_ATTACK_H
