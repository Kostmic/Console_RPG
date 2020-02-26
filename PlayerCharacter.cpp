
#include "PlayerCharacter.h"
#include <string>
#include <vector>

PlayerCharacter::PlayerCharacter(std::string name, int maxHp) {
    m_name = name;
    m_maxHp = maxHp;
    m_currentHp = maxHp;
}

void PlayerCharacter::addAttack(std::string name, int damage, int cooldown){
    attackObj = new Attack(name, damage, cooldown);
    attackVector.push_back(attackObj);
}

void PlayerCharacter::getAttacks() {
    for (int i = 0; i < attackVector.size(); ++i) {
        Attack* currentAttack = attackVector.at(i);
        std::cout
        << "  "
        << i+1
        << " - "
        << currentAttack->getName()
        << " (" << currentAttack->getDamage()
        << "/"
        << currentAttack->getMaxCooldown()
        <<")";
        if (currentAttack->getMaxCooldown()>0 && currentAttack->getCurrentCooldown() != 0){
            std::cout << " (" <<  currentAttack->getCurrentCooldown() << " - Turns remaining)";
        }
        std::cout << std::endl;
    }
}

int PlayerCharacter::getMaxHp() {
    return m_maxHp;
}

int PlayerCharacter::getCurrentHp() {
    return m_currentHp;
}

std::string  PlayerCharacter:: getName() {
    return m_name;
}

void PlayerCharacter::hit(int damage) {
    m_currentHp -= damage;

}

void PlayerCharacter::decrementCooldowns(){
    for (int i = 0; i < attackVector.size(); ++i) {
        attackObj = attackVector.at(i);
        if(attackObj->getCurrentCooldown() > 0){
            attackObj->decrementCooldown();
        }
    }
}

std::string PlayerCharacter::runTurn(std::string currentPlayer, std::string targetPlayer, int damage) {
    return currentPlayer+ " attacked " + targetPlayer + " for " + std::to_string(damage)+ " damage";
}

