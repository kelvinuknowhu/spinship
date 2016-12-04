//
//  Bullet.hpp
//  Flocking Spaceships
//
//  Created by Kelvin Hu on 11/14/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp
#define PI 3.14159265
#include <stdio.h>
#include "Leader.hpp"
#include "Vector2.hpp"
#include "Utility.h"

class Bullet : public LTexture
{
    
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 maxSpeed;
    float velocityAngle;
    int numBulletsMax;
    
    
    Bullet(Vector2 _pos, float _angle) : LTexture(1)
    {
        this->position = _pos;
        this->angle = _angle + 90;
        this->velocityAngle = _angle;
        this->velocity.x = 250 * cos(angleToRadian(velocityAngle));
        this->velocity.y = 250 * sin(angleToRadian(velocityAngle));
        this->acceleration = velocity;
        this->maxSpeed = Vector2(1500, 1500);
        this->numBulletsMax = 1;
    }
    
    void setPosition(Vector2 _pos)
    {
        this->position.x = position.x;
        this->position.y = position.y - getActualHeight()/2;
    }
    
    void updatePosition(float ticks)
    {
        position += velocity * ticks;
        velocity += acceleration * ticks;
        if (velocity.x > maxSpeed.x || velocity.y > maxSpeed.y)
        {
            acceleration = 0;
        }
    }
    
    bool offScreen(int screenWidth, int screenHeight)
    {
        if (position.x + getActualWidth() < 0 || position.x > screenWidth || position.y + getActualHeight() < 0 || position.y > screenHeight)
            return true;
        return false;
    }
    
    void setAngle(float angle)
    {
        this->angle = angle;
    }
    
    void setVelocityAngle(float angle)
    {
        this->velocityAngle = angle - 90;
    }
    
    
};









#endif /* Bullet_hpp */
