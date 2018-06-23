//
//  enemyClass.cpp
//  lab4
//
//  Created by Roman Mishchenko on 15.05.2018.
//  Copyright © 2018 Roman Mishchenko. All rights reserved.
//

#include <stdio.h>
#include "enemyClass.hpp"
#include "findVel.h"

void placeVelToEnemy(enemyClass& enemy, xAy& point, int numberEnemy, gameMapClass mapObject)
{
    
    array<int, objectsVel> vel = findVelocity(enemy.x, enemy.y, mapObject.enemyWay, numberEnemy);
    enemy.xVelocity = vel[0];
    enemy.yVelocity = vel[1];
    point.x = vel[2];
    point.y = vel[3];
}

void enemyMove(int finalPoint, enemyClass& enemy, xAy& point, int numberEnemy, gameMapClass mapObject)
{
    
    array<int, objectsVel> vel;
    if((enemy.x != finalPoint) || (enemy.y != finalPoint))
    {
        
        if(point.x == enemy.x && point.y == enemy.y)
        {
            
            
            placeVelToEnemy(enemy, point, numberEnemy, mapObject);
            
        }
        enemy.x += (enemy.xVelocity);
        enemy.y += (enemy.yVelocity);
        enemy.model.setPosition(enemy.x, enemy.y);
    }
    else if(enemy.isAlive)
    {
        enemy.isAlive = false;
        enemy.~enemyClass();
    }
    
}
