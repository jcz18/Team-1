#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include <queue>
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship : public Sprite
{
    private:
        int hull;
        string sprite;
        vector<int> position;
        int velocity;
        float rotation;
        int weaponType;
        bool damageTaken;
        int maxVelocity;
        string currKey;
        int mass;

        float speedX;
        float speedY;
        int hp;

        //ai
        std::queue<pair<int,int>>* path;
        vector<int> destination;
        bool isUser;
        bool isAlly;
        bool pathComplete;

    public:
        Ship();
        Ship(SDL_Rect dBox, SDL_Texture* aTex);
        Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim);
        Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass);
        ~Ship();
        
        void setSprite(string newSprite);
        string getSprite();
        void checkPhysics();
        //integrate BasicMovementFPSlimit.cpp

        void setSpeedX(float speed);
        void setSpeedY(float speed);
        void updateMovement();
        void checkAction(/*stream*/);
        void updateHull(int newHull);
        void setPosition(vector<int> newPosition);
        vector<int> getPosition();
        void setPath(queue<pair<int, int>>* thePath);
        //ai follows path assigned to it by ai class
        void followPath(Sprite& entity);
        bool getPathComplete();
        vector<int> getDestination();
        int getMaxVelocity();
        void setDestination(vector<int> newDestination);
        int getMass();
        void setHp(int newHp);
        int getHp();
}; 

class Hero:Ship{};

class Fighter:Ship{};

class Cruiser:Ship{};

class Capital:Ship{};
