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
    std::string bulletName;
    Vector2 position = Vector2(0,0);
    Vector2 velocity = Vector2(0,0);
    Vector2 acceleration = Vector2(0,0);
    Vector2 maxSpeed= Vector2(0,0);
    float velocityAngle = 0;
    float defaultSpeed = 500;
    float defaultAcceleration = 250;
    
    
    
    Bullet(Vector2 _pos, float _angle, std::string _name) : LTexture(1)
    {
        this->position = _pos;
        this->angle = _angle + 90;
        this->velocityAngle = _angle;
        this->velocity.x = defaultSpeed * cos(angleToRadian(velocityAngle));
        this->velocity.y = defaultSpeed * sin(angleToRadian(velocityAngle));
        this->acceleration.x = defaultAcceleration * cos(angleToRadian(velocityAngle));
        this->acceleration.y = defaultAcceleration * sin(angleToRadian(velocityAngle));
        this->maxSpeed = Vector2(1500, 1500);
        this->bulletName = _name;
    }
    
    void setPosition(Vector2 _pos)
    {
        position.x = position.x;
        position.y = position.y - getActualHeight()/2;
    }
    
    void setInitialSpeed(float _speed)
    {
        float speedDesired = 2 * _speed;
        if (speedDesired > defaultSpeed)
        {
            velocity.x = speedDesired * cos(angleToRadian(velocityAngle));
            velocity.y = speedDesired * sin(angleToRadian(velocityAngle));
        }
    }
    
    void setAcceleration(float _num)
    {
        if (_num > defaultAcceleration)
        {
            acceleration.x = _num * cos(angleToRadian(velocityAngle));
            acceleration.y = _num * sin(angleToRadian(velocityAngle));
        }
    }
    
    void setAngle(float _angle)
    {
        angle = _angle;
    }
    
    void setVelocityAngle(float angle)
    {
        velocityAngle = angle - 90;
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
    
    
    
    
};









#endif /* Bullet_hpp */
