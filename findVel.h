//
//  findVel.h
//  
//
//  Created by Roman Mishchenko on 15.04.2018.
//

#pragma once
#include <iostream>
#include "mapClass.hpp"
const int objectsVel = 4;

array<int, 4> findVelocity(int x, int y, array<list<xAy>, 3> way, int enemyNumber);
