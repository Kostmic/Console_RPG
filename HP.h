

#ifndef CONSOLE_RPG_HP_H
#define CONSOLE_RPG_HP_H


class HP {
public:
    HP(int HP, int AC){
        m_maxHP = HP;
        m_HP = HP;
        m_AC = AC;
    };
    HP operator += (HP const &obj){
        HP res(m_MaxHP, m_AC);
        res.m_maxHP = m_maxHP + obj.m_maxHP;
        res.m_AC = m_AC + obj.m_AC;
        return res;
    }

    HP operator -=(int) (const HP& h) const;
    HP operator +=(int) (const HP& v) const;
    HP operator ==(int) (const HP& v) const;
private:
    int m_HP;
    int m_maxHP;
    int m_AC;

};


#endif //CONSOLE_RPG_HP_H
