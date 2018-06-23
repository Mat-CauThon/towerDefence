//
//  enemyClass.cpp
//  lab4
//
//  Created by Roman Mishchenko on 07.04.2018.
//  Copyright © 2018 Roman Mishchenko. All rights reserved.
//

#include "findVel.h"
#include "mapClass.hpp"



std::array<int, objectsVel> findVelocity(int x, int y, array<list<xAy>, enemyNumber> way, int enemyNumber)
{
    int velosity = 3;
        if(enemyNumber == 2)
        {
            velosity += 3;
        }
    array<int, objectsVel> vel;
    xAy point;
    bool b = false;
    
    for(xAy& pointer : way[enemyNumber])
    {
        if(b)
        {
            point.x = pointer.x;
            point.y = pointer.y;
            break;
        }
        if(x == pointer.x && y == pointer.y)
        {
            b = true;
        }
    }
    
    vel[2] = point.x;
    vel[3] = point.y;
    
    vel[0] = 0;
    vel[1] = 0;

  //  sf::Vector2i vel(0, 0);
    
    if(x + scale  == point.x)
    {
        vel[0] = velosity;
    }
    else if(x - scale == point.x )
    {
        vel[0] = -velosity;
    }
    else if( y + scale == point.y)
    {
        vel[1] = velosity;
    }
    else if(y - scale == point.y)
    {
        vel[1] = -velosity;
    }
    
    return vel;
}
