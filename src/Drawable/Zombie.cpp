#include "Zombie.h"
#include "cmath"
Zombie::Zombie(int line, int col): Character(line,col,25,0.025)
{
    setMaxUpdateFollowCount(100);
}

void Zombie::update()
{
    if(getPathSize()==0)
        m_state = NORMAL;
    else
        m_state = MOVE;
    if(getMode() == Entity::FOLLOW)
    {
        sdaa::VectInt targetPos = getTargetPosInMetric();
        sdaa::VectInt pos = getPositionInMetric();
        if(sqrt(pow(pos.line-targetPos.line,2)+pow(pos.col-targetPos.col,2))==1)
        {
            m_state = HIT;
            if(targetPos.line-pos.line<0)
                m_dir = Character::UP;
            else if(targetPos.line-pos.line>0)
                m_dir = Character::DOWN;
            else if(targetPos.col - pos.col <0)
                m_dir = Character::RIGHT;
            else
                m_dir = Character::LEFT;
        }
    }


    subUpdate();

}

void Zombie::animation()
{
    int maxAnimTime;
    switch(m_state)
    {
        case NORMAL:
            maxAnimTime= 0;
            break;
        case MOVE:
            maxAnimTime =500;
            break;
        case HIT:
            maxAnimTime = 500;
            break;
        default :
            maxAnimTime = 0;
            break;
    }
    float time = m_animClock.getElapsedTime().asMilliseconds();
    if(time > maxAnimTime)
        m_animClock.restart();
    int posX;
    int posY;
    bool turn = false;
    switch(m_state)
    {
        case NORMAL :
            if(m_dir == LEFT)
            {
                posY = 1;
                turn = true;
            }
            else if(m_dir == RIGHT)
            {
                posY = 1;
            }
            else if(m_dir == UP)
            {
                posY= 2;
            }
            else if(m_dir == DOWN)
            {
                posY= 0;
            }
            posX =0;
            break;
        case MOVE :
            if(m_dir == LEFT)
            {
                posY = 1;
                turn = true;
            }
            else if(m_dir == RIGHT)
            {
                posY = 1;
            }
            else if(m_dir == UP)
            {
                posY= 2;
            }
            else if(m_dir == DOWN)
            {
                posY= 0;
            }
            if(time<maxAnimTime/4.f)
            {
                posX=0;
            }
            else if(time < maxAnimTime*2/4.f)
            {
                posX = 1;
            }
            else if(time < maxAnimTime*3/4.f)
            {
                posX=2;
            }
            else
            {
                posX = 3;
            }
            break;

        case HIT:
            if(m_dir == LEFT)
            {
                posY = 4;
                if(time<maxAnimTime/2.f)
                    posX = 0;
                else
                    posX = 1;
                turn = true;
            }
            else if(m_dir == RIGHT)
            {
                posY = 4;
                if(time<maxAnimTime/2.f)
                    posX = 0;
                else
                    posX = 1;
            }
            else if(m_dir == UP)
            {
                if(time<maxAnimTime/2.f)
                    posX = 2;
                else
                    posX = 3;
                posY= 3;
            }
            else if(m_dir == DOWN)
            {
                if(time<maxAnimTime/2.f)
                    posX = 0;
                else
                    posX = 1;
                posY= 3;
            }
            break;
    }

    setTextureRect(posX,posY,turn);

}

bool Zombie::collide(Bullets const& bullet)
{
    sdaa::VectFloat pos = getFullPosition();
    int s = getSquareSize();
    sf::FloatRect rect = bullet.getGlobalBounds();
    if(pos.x+s<rect.left)
        return false;
    else if(pos.x>rect.left+rect.width)
        return false;
    else if(pos.y+s<rect.top)
        return false;
    else if(pos.y>rect.top+rect.height)
        return false;
    return true;

}
