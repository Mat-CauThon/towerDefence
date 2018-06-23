//
//  gameMapClass.hpp
//  lab4
//
//  Created by Roman Mishchenko on 07.04.2018.
//  Copyright © 2018 Roman Mishchenko. All rights reserved.
//

#pragma once
#include <iostream>
#include <queue>
#include <list>
#include <fstream>
#include <array>
#include <vector>

const int scale = 84;
const int enemyNumber = 3;
const int mapSize = 20;
const int preferedNumber = 10;
const int finalPoint = 1512;

using namespace std;
struct xAy
{
    int x;
    int y;
    char object;
};

class gameMapClass
{
private:
    bool checkWall (int x, int y, char gameMapArray[mapSize][mapSize]);
    array<xAy, preferedNumber> preferPointSearch(array<list<xAy>, enemyNumber> array);
    void find_path(int n, int row, int col, char** lab, int** visited, int** path, queue<int>& plan);
    array<list<xAy>, enemyNumber> find();
public:
    array<list<xAy>, enemyNumber> enemyWay = gameMapClass::find();
    array<xAy, preferedNumber> preferPoint = gameMapClass::preferPointSearch(enemyWay);

};
