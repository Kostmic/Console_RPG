
#include "Character.h"
#include <string>
#include <iostream>


Character::Character(std::string name, int maxHp, int ac) {
    m_name = name;
    playerHP = new HP(maxHp, ac);
}

Character::Character(std::string name, int maxHp) {
    m_name = name;
    playerHP = new HP(maxHp);
}

void Character::addAttack(std::string name, int damage, int cooldown) {
    attackObj = new Attack(name, damage, cooldown);
    attackVector.push_back(attackObj);
}

void Character::getAttacks() {
    for (int i = 0; i < attackVector.size(); ++i) {
        Attack *currentAttack = attackVector.at(i);
        std::cout
                << "  "
                << i + 1
                << " - "
                << currentAttack->getName()
                << " (";
        if (currentAttack->getDamage() < 0) {
            std::cout << "+" << currentAttack->getDamage() * -1;
        } else {
            std::cout
                    << currentAttack->getDamage();
        }
        std::cout
                << "|";
        if (currentAttack->getMaxCooldown() > 0) {
            std::cout << currentAttack->getMaxCooldown();
        } else {
            std::cout << "-";
        }

        std::cout
                << ")";
        if (currentAttack->getMaxCooldown() > 0 && currentAttack->getCurrentCooldown() != 0) {
            std::cout << " (CD " << currentAttack->getCurrentCooldown() << ")";
        }
        std::cout << std::endl;
    }
}

int Character::getMaxHp() {
    return playerHP->getMaxHp();
}

int Character::getCurrentHp() {
    return playerHP->getCurrentHp();
}

std::string Character::getName() {
    return m_name;
}

int Character::hit(int damage) {
    if (damage < 0) {
        *playerHP += damage;
    } else {
        *playerHP -= damage;
    }
    return damage;
}

void Character::decrementCooldowns() {
    for (int i = 0; i < attackVector.size(); ++i) {
        attackObj = attackVector.at(i);
        if (attackObj->getCurrentCooldown() > 0) {
            attackObj->decrementCooldown();
        }
    }
}

//We need to multiply our heal by -1 to print it as a positive value. if statement checks for negative values, since heals are negative
std::string Character::printTurn(std::string currentPlayer, std::string targetPlayer, int damage) {
    if (damage > 0) {
        return currentPlayer + " attacked " + targetPlayer + " for " + std::to_string(damage) + " damage";
    } else {
        return currentPlayer + " healed " + targetPlayer + " for " + std::to_string(damage * -1) + " health";
    }
}

bool Character::isPlayer(){
    return true;
}