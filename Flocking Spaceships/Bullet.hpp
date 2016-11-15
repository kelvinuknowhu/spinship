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
    float lastFrameTime;
    int currentFrame;
    int numBulletsMax;
    
    
    Bullet(Vector2 position, float angle, int nframes) : LTexture(nframes) {
        this->position = position;
        this->angle = angle + 90;
        this->velocityAngle = angle;
        this->velocity.x = cos(velocityAngle * PI / 180);
        this->velocity.y = sin(velocityAngle * PI / 180);
        this->acceleration = Vector2(velocity.x, velocity.y);
        this->maxSpeed = 10.0;
        this->currentFrame = 0;
        this->lastFrameTime = 0;
        this->numBulletsMax = 1;
    }
    
    void updatePosition() {
        velocity += acceleration;
        position += velocity;
        if (velocity.x > maxSpeed || velocity.y > maxSpeed) {
            acceleration.x = 0;
            acceleration.y = 0;
        }
    }
    
    bool offScreen(int screenWidth, int screenHeight) {
        if (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight)
            return true;
        return false;
    }
    
    void setAngle(float angle) {
        this->angle = angle;
    }
    
    void setVelocityAngle(float angle) {
        this->velocityAngle = angle;
    }
    
    
    
    
};









#endif /* Bullet_hpp */
