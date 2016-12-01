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

class Bullet : public LTexture {
    
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float maxSpeed;
    float velocityAngle;
    int numBulletsMax;
    
    
    Bullet(Vector2 _pos, float _angle) : LTexture(1) {
        this->position = _pos;
        this->angle = _angle;
        this->velocityAngle = _angle - 90;
        this->velocity.x = cos(angleToRadian(velocityAngle));
        this->velocity.y = sin(angleToRadian(velocityAngle));
        this->acceleration = Vector2(velocity.x, velocity.y);
        this->maxSpeed = 10;
        this->numBulletsMax = 1;
    }
    
    void setPosition(Vector2 _pos)
    {
        this->position.x = position.x;
        this->position.y = position.y - getTextureHeight()/2;
    }
    
    void updatePosition()
    {
        velocity += acceleration;
        position += velocity;
        if (velocity.x > maxSpeed || velocity.y > maxSpeed) {
            acceleration.x = 0;
            acceleration.y = 0;
        }
    }
    
    bool offScreen(int screenWidth, int screenHeight)
    {
        if (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight)
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
    
    float angleToRadian(float angle)
    {
        return (float) angle * PI / 180.0f;
    }
    
    
};









#endif /* Bullet_hpp */
