//
// Created by Michael Kosther on 29/01/2020.
//

#include "Attack.h"
#include <string>

Attack::Attack(std::string name, int damage, int cooldown) {
    m_name = name;
    m_damage = damage;
    m_maxCooldown = cooldown;
}

std::string Attack::getName() {
    return m_name;
}

int Attack::getDamage() {
    return m_damage;
}

int Attack::getMaxCooldown() {
    return m_maxCooldown;
}

int Attack::getCurrentCooldown() {
    return m_currentCooldown;
}

void Attack::decrementCooldown() {
    m_currentCooldown--;
}

void Attack::setCooldown() {
    m_currentCooldown = m_maxCooldown + 1;
}