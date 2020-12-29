#include "PlayerChar.h"
#include <cmath>
PlayerChar::PlayerChar(int line , int col): Character(line,col,25,0.05)
{
    m_state = NORMAL;
}

void PlayerChar::animation()
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
        case SHOOT:
            maxAnimTime = 500;
            break;
        default :
            maxAnimTime = 1000;
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

        case SHOOT:

            if(m_dir == LEFT)
            {
                posY = 3;
                turn = true;
                if(time<maxAnimTime/2.f)
                {
                    posX = 2;
                }
                else
                    posX = 3;
            }
            else if(m_dir == RIGHT)
            {
                posY = 3;
               if(time<maxAnimTime/2.f)
                {
                    posX = 2;
                }
                else
                    posX = 3;
            }
            else if(m_dir == UP)
            {
                posY= 4;
                if(time<maxAnimTime/2.f)
                {
                    posX = 0;
                }
                else
                    posX = 1;
            }
            else if(m_dir == DOWN)
            {
                posY= 3;
                if(time<maxAnimTime/2.f)
                {
                    posX = 0;
                }
                else
                    posX = 1;
            }

            break;
    }

    setTextureRect(posX,posY,turn);
}

void PlayerChar::update()
{
    subUpdate();
    if(getMode()==Entity::MOVE && m_state !=SHOOT)
        m_state = MOVE;
    else if(getMode() == Entity::WAIT && m_state != SHOOT )
        m_state = NORMAL;
    else if(getMode() == Entity::FOLLOW)
    {
        sdaa::VectInt targetPos = getTargetPosInMetric();
        sdaa::VectInt pos = getPositionInMetric();
        if(sqrt(pow(pos.col-targetPos.col,2)+pow(pos.line-targetPos.line,2))<6)
        {
            stopToFollow(true);
            m_state = SHOOT;
        }
        else
            m_state = MOVE;
    }
    if(m_state == SHOOT)
    {
        if(asATarget())
        {
            sdaa::VectInt targetPos = getTargetPosInMetric();
            sdaa::VectInt pos = getPositionInMetric();
            int deltaX = targetPos.col-pos.col;
            int deltaY = targetPos.line - pos.line;
            if(abs(deltaX)>abs(deltaY))
            {
                if(deltaX<0)
                {
                    m_dir = Character::RIGHT;
                }
                else if(deltaX>0)
                {
                    m_dir = Character::LEFT;
                }
            }
            else
            {
                if(deltaY<0)
                {
                    m_dir = Character::UP;
                }
                else if(deltaY>0)
                {
                    m_dir = Character::DOWN;
                }
            }
        }
        else
        {
            m_state = NORMAL;
        }
    }

}

PlayerChar::State PlayerChar::getState() const
{
    return m_state;
}

bool PlayerChar::shoot()
{
    if(m_shootClock.getElapsedTime().asMilliseconds()>500)
    {
        m_shootClock.restart();
        return true;
    }
    else
        return false;
}

void PlayerChar::setState(PlayerChar::State state)
{
    m_state = state;
}
