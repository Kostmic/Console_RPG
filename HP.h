

#ifndef CONSOLE_RPG_HP_H
#define CONSOLE_RPG_HP_H


class HP {
public:
    HP(int HP);
    HP(int hp, int ac);


    HP operator +=(int const &obj);

    HP operator += (HP const &obj);
private:
    int m_HP;
    int m_maxHP;
    int m_AC;

};


#endif //CONSOLE_RPG_HP_H
