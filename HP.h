#ifndef CONSOLE_RPG_HP_H
#define CONSOLE_RPG_HP_H


class HP {
public:
    HP(int HP);

    HP(int hp, int ac);

    int getCurrentHp();

    int getMaxHp();


    HP operator-=(int &damage);

    HP operator+=(int &damage);

private:
    int m_HP;
    int m_maxHP;
    int m_AC;

};


#endif //CONSOLE_RPG_HP_H