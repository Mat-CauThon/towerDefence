//
//  Singleton.hpp
//  lab5
//
//  Created by Roman Mishchenko on 04.06.2018.
//
//
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace sf;
using namespace std;
class Singleton
{
private:
    std::unordered_map<string,sf::Image> Cache;
    Singleton() {}  // конструктор недоступен
    ~Singleton() {} // и деструктор
    Singleton(Singleton const&) = delete;
    Singleton& operator= (Singleton const&) = delete;
public:
    void load(string name)
    {
        string namePNG = name + ".png";
        
        Image image;
        //std::cout << namePNG << "\n";
        if(!image.loadFromFile(namePNG))
        {
            std::cout<<"ERROR: Can't load texture :( \n";
        }
        Cache[name] = image;
    }
    
    Image getTexture(string name)
    {
        //     std::cout << Cache[name] << "\n";
        return Cache[name];
    }
    
    static Singleton& Instance()
    {
        // согласно стандарту, этот код потокобезопасный
        static Singleton s;
        return s;
    }
};

Singleton& instance = Singleton::Instance();


