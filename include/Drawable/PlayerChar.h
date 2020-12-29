#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H

#include "Character.h"

class PlayerChar : public Character
{
    public:
        enum State {NORMAL,MOVE,SHOOT};
        PlayerChar(int line , int col);
        void animation();
        void update();
        State getState() const;
        void setState(State state);
        bool shoot();
    protected:

    private:
        long m_life;
        sf::Clock m_animClock;
        sf::Clock m_shootClock;
        State m_state;
};

#endif // PLAYERCHAR_H
