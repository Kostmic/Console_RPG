#include "HP.h"
HP HP::operator -= (const HP& h, damage) const{
    HP result(m_HP-(damage-m_AC), m_AC);
    return result;
}