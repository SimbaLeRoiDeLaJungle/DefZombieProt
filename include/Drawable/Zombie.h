#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Character.h"
#include "Bullets.h"

class Zombie : public Character
{
    public:
        enum State {NORMAL,MOVE,HIT};
        Zombie(int line, int col);
        void update();
        void animation();
        bool collide(Bullets const& bullet);
    protected:

    private:
        State m_state;
        sf::Clock m_animClock;

};

#endif // ZOMBIE_H
