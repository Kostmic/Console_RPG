
#include "Character.h"
#include <string>
#include <vector>

Character::Character(std::string name, int maxHp, int ac) {
    m_name = name;
    playerHP = new HP(maxHp, ac);
}

Character::Character(std::string name, int maxHp) {
    m_name = name;
    playerHP = new HP(maxHp);
}

void Character::addAttack(std::string name, int damage, int cooldown){
    attackObj = new Attack(name, damage, cooldown);
    attackVector.push_back(attackObj);
}

void Character::getAttacks() {
    for (int i = 0; i < attackVector.size(); ++i) {
        Attack* currentAttack = attackVector.at(i);
        std::cout
        << "  "
        << i+1
        << " - "
        << currentAttack->getName()
        << " ("
        << currentAttack->getDamage()
        << "|";
        if(currentAttack->getMaxCooldown()>0){
            std::cout << currentAttack->getMaxCooldown();
        }else{
            std::cout << "-";
        }

        std::cout
        <<")";
        if (currentAttack->getMaxCooldown()>0 && currentAttack->getCurrentCooldown() != 0){
            std::cout << " (CD " <<  currentAttack->getCurrentCooldown() << ")";
        }
        std::cout << std::endl;
    }
}

int Character::getMaxHp() {
    return playerHP->m_maxHP;
}

int Character::getCurrentHp() {
    return playerHP->m_HP;
}

std::string  Character:: getName() {
    return m_name;
}

void Character::hit(int damage) {
   playerHP->m_HP -= damage;

}

void Character::decrementCooldowns(){
    for (int i = 0; i < attackVector.size(); ++i) {
        attackObj = attackVector.at(i);
        if(attackObj->getCurrentCooldown() > 0){
            attackObj->decrementCooldown();
        }
    }
}

std::string Character::printTurn(std::string currentPlayer, std::string targetPlayer, int damage) {
    return currentPlayer+ " attacked " + targetPlayer + " for " + std::to_string(damage)+ " damage";
}

bool Character::isPlayer(){
    return true;
}