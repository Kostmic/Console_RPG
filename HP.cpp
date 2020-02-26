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

