#include "HP.h"

HP::HP(int hp) {
    m_maxHP = hp;
    m_HP = hp;
    m_AC = 0;
}

HP::HP(int hp, int ac) {
    m_maxHP = hp;
    m_HP = hp;
    m_AC = ac;
}

int HP::getCurrentHp() {
    return m_HP;
}

int HP::getMaxHp() {
    return m_maxHP;
}

HP HP::operator-=(int &damage) {
    damage -= m_AC;
    m_HP -= damage;
    return *this;
}

HP HP::operator+=(int &damage) {
    if ((m_HP - damage) <= m_maxHP) {
        m_HP -= damage;

    } else {
        damage = m_maxHP - m_HP;
        m_HP = m_maxHP;
    }
    return *this;
}
