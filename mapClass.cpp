//
//  mapClass.cpp
//  lab4
//
//  Created by Roman Mishchenko on 18.04.2018.
//  Copyright © 2018 Roman Mishchenko. All rights reserved.
//

#include <iostream>
#include <queue>
#include <list>
#include <fstream>
#include <array>
#include <vector>
#include "mapClass.hpp"

using namespace std;


array<list<xAy>, enemyNumber> pushWay(array<list<xAy>, enemyNumber> enemyWay, int x, int y, int p)
{
    xAy wayPoint;
    wayPoint.x = y * scale;
    wayPoint.y = x * scale;
    enemyWay[p].push_back(wayPoint);
    return enemyWay;
}


void gameMapClass::find_path(int n, int row, int col, char** lab, int** visited, int** path, queue<int>& plan)
{
    if(!visited[row][col]){
        /* проверяем не вышли ли мы за границы лабиринта, есть ли клетка
         в массиве посещенных и можно ли через нее пройти*/
        if ((row+1) < n && (row+1) >= 0 && !visited[row+1][col] &&
            (lab[row+1][col] == '.' || lab[row+1][col] == 'X'))
        {
            path[row+1][col] = path[row][col] + 1;
            plan.push(row+1);
            plan.push(col);
        }
        if((row-1) < n && (row-1) >= 0 && !visited[row-1][col] &&
           (lab[row-1][col] == '.' || lab[row-1][col] == 'X'))
        {
            path[row-1][col] = path[row][col] + 1;
            plan.push(row-1);
            plan.push(col);
        }
        if((col + 1) < n && (col + 1) >= 0 && !visited[row][col+1] &&
           (lab[row][col+1] == '.' || lab[row][col+1] == 'X'))
        {
            path[row][col+1] = path[row][col] + 1;
            plan.push(row);
            plan.push(col+1);
        }
        if((col - 1) < n && (col - 1) >= 0 && !visited[row][col-1] &&
           (lab[row][col-1] == '.' || lab[row][col-1] == 'X'))
        {
            path[row][col-1] = path[row][col] + 1;
            plan.push(row);
            plan.push(col-1);
        }
        visited[row][col] = 1; /* отмечаем клетку в которой побывали */
    }
}
array<list<xAy>, enemyNumber> gameMapClass::find()
{
    std::fstream file;
    file.open("array.txt");
    //gameMap gameMapArray;
    char gameMap[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize; j++)
        {
            file >> gameMap[i][j];
        }
    }
    file.close();
    
    int n = mapSize, x_start, y_start, x_end = 0, y_end = 0, x, y;
    queue <int> plan;
   
    char** lab = new char* [n];
    int** visited = new int * [n];
    int** path = new int * [n];
    
    array<list<xAy>, enemyNumber> enemyWay; //way for *enemyNumber(3)* enemy
    
        for(int p = 0; p < enemyNumber; p++)
        {
            if (p == 0)
            {
                gameMap[1][1] = 'X';
            }
            else if ( p == 1)
            {
                gameMap[1][1] = '.';
                gameMap[0][18] = 'X';
            }
            else if( p == 2)
            {
                gameMap[0][18] = '.';
                gameMap[18][1] = 'X';
            }
            
            
            
            for(int i = 0; i < n; i++)
            {
                lab[i] = new char [n];   /* массив для хранения лабиринта */
                visited[i] = new int [n]; /* массив для хранения информации о посещении клеток*/
                path[i] = new int [n];  /* массив для хранения найденных путей */
                for(int j=0; j<n; j++)
                {
                    visited[i][j] = 0;
                    path[i][j] = -1;
                    lab[i][j] = gameMap[i][j];
                    if (lab[i][j] == '@')
                    { /* находим начало пути*/
                        x_start = i;
                        y_start = j;
                        plan.push(i);  /* заносим начальную клетку */
                        plan.push(j);  /* в план посещения */
                        path[i][j] = 1;
                    }
                    else if (lab[i][j] == 'X')
                    { /* находим конечную точку */
                        x_end = i;
                        y_end = j;
                        //cout << x_end << " " << y_end << "\n";
                    }
                }
            }
            while(!plan.empty())
            { /* пока очередь посещения клеток непустая*/
                x=plan.front();
                plan.pop();
                y=plan.front();
                plan.pop();
                find_path(n, x, y, lab, visited, path, plan); /* продолжаем поиск пути*/
            }
            if(!visited[x_end][y_end])
            {
                cout << "ERROR: Way not found :( \n";
            }
            else
            {
                x = x_end;
                y = y_end;
                lab[x][y] = '+';
                while (path[x][y] != 1)
                { /* восстановление пути*/
                    if ((x-1) >= 0 && (x-1) < n && (path[x-1][y] == path[x][y] - 1))
                    {
                        enemyWay = pushWay(enemyWay, x, y, p);
                        x = x-1;
                    }
                    else if ((x+1) >= 0 && (x+1) < n && (path[x+1][y] == path[x][y] - 1))
                    {
                        enemyWay = pushWay(enemyWay, x, y, p);
                        x = x+1;
                    }
                    else if ((y-1) >= 0 && (y-1) < n && (path[x][y-1] == path[x][y] - 1))
                    {
                        enemyWay = pushWay(enemyWay, x, y, p);
                        y = y-1;
                    }
                    else if ((y+1) >= 0 && (y+1) < n && (path[x][y+1] == path[x][y] - 1))
                    {
                        enemyWay = pushWay(enemyWay, x, y, p);
                        y = y+1;
                    }
                }
            }
           
            enemyWay = pushWay(enemyWay, 17, 18, p); //заносить в путь Ячейку базы
            
            
            for (int i = 0; i < n; i++)
            {
                delete [] lab[i];
                delete [] visited[i];
                delete [] path[i];
            }
           
            
        }
    
        return enemyWay;
    }



bool gameMapClass::checkWall (int x, int y, char gameMapArray[mapSize][mapSize])
{
    
    if (gameMapArray[x][y] == '0')
    {
        return true;
    }
    return false;
}
array<xAy, preferedNumber> gameMapClass::preferPointSearch(array<list<xAy>, enemyNumber> array)
{
    
    std::fstream file;
    file.open("array.txt");
   
    char gameMapArray[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize; j++)
        {
            file >> gameMapArray[i][j];
        }
    }
    file.close();
    
    
    std::array<std::array<int, mapSize>, mapSize> value;
    int numbers = 0;
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            for(int i = 0; i < enemyNumber; i++)
            {
                
                for (xAy point : array[i])
                {
                    // std::cout << "point x-" << point.x << " y-" << point.y << "\n";
                    if ((x-1 == point.y/scale && y-1 == point.x/scale) || (x == point.y/scale && y-1 == point.x/scale) || (x-1 == point.y/scale && y == point.x/scale) || (x+1 == point.y/scale && y+1 == point.x/scale) || (x == point.y/scale && y+1 == point.x/scale) || (x+1 == point.y/scale && y == point.x/scale) || (x-1 == point.y/scale && y+1 == point.x/scale) || (x+1 == point.y/scale && y-1 == point.x/scale))
                    {
                        if(checkWall(x, y, gameMapArray))
                        {
                            numbers++;
                        }
                    }
                }
            }
            
            value[x][y] = numbers;
            numbers = 0;
        }
    }
    
    std::array<xAy, preferedNumber> arrayTenPoint;
    int max = 0;
    int I = 0;
    int J = 0;
    for (int i = 0; i < preferedNumber; i++)
    {
        for (int x = 0; x < mapSize; x++)
        {
            for (int y = 0; y < mapSize; y++)
            {
                if(value[x][y] > max)
                {
                    max = value[x][y];
                    I = x;
                    J = y;
                }
            }
        }
        arrayTenPoint[i].x = J * scale;
        arrayTenPoint[i].y = I * scale;
        value[I][J] = 0;
        max = 0;
    }
    return arrayTenPoint;
}


