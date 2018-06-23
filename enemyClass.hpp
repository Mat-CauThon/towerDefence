//
//  enemyClass.hpp
//  lab4
//
//  Created by Roman Mishchenko on 07.04.2018.
//  Copyright © 2018 Roman Mishchenko. All rights reserved.
//

#pragma once
#include <iostream>
#include <array>
#include <list>
#include "mapClass.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class enemyClass
{
public:
    
    sf::Sprite model;
    int xVelocity;
    int yVelocity;
    int x;
    int y;
    bool isAlive = true;
    
    ~enemyClass()
    {
       
        cout << "Тут сработал деструктор \n";
    }
    
};

void placeVelToEnemy(enemyClass& enemy, xAy& point, int numberEnemy, gameMapClass mapObject);
void enemyMove(int finalPoint, enemyClass& enemy, xAy& point, int numberEnemy, gameMapClass mapObject);
