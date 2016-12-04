//
//  Leader.hpp
//  Flocking Spaceships
//
//  Created by Kelvin Hu on 11/03/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Leader_hpp
#define Leader_hpp


#include <stdio.h>
#include <math.h>
#include <vector>
#include "Vector2.hpp"
#include "LTexture.hpp"
#include "Utility.h"

#define PI 3.14159265


class Leader : public LTexture
{
public:
    float speed = 0;
    float initialSpeed = 0;
    float acceleration = 0;
    float deacceleration = 0;
    float friction = 0;
    float maxSpeed = 0;
    float radian = 0;
    float avgRotation = 0;
    float detectionDistance = 0;
    float detectionDistanceSquared = 0;
    Vector2 velocity = Vector2(0, 0);
    Vector2 center = Vector2(0, 0);
    int numEntities = 0;
    int maxNumEntities = 0;
    float health = 100;
    int maxNumBulletsPerPress = 0;
    int numBulletsPerPress = 0;
    std::string planeType;
    std::string bulletType;
    std::string bulletLevel;
    Vector2 position;
    SDL_Rect boundingRectangle;
    
    Leader(Vector2 position,
           int screenWidth, int screenHeight) : LTexture(1)
    {
        this->position = position;
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
    }
    
    bool detectCollision(float _xPos, float _yPos, float _width, float _height)
    {
        float upperBound = _yPos;
        float lowerBound = _yPos + _height;
        float leftBound  = _xPos;
        float rightBound = _xPos + _width;
        
        if (position.x + getActualWidth() > leftBound
            && position.x  < rightBound
            && position.y < lowerBound
            && position.y + getActualHeight() > upperBound)
            return true;
        return false;
    }
    
    void speedDown(float ticks)
    {
        speed -= friction * ticks;
        
        if (speed < 0)
        {
            speed = 0;
        }
        
    }


    void updatePosition(float ticks)
    {
        radian = angleToRadian(angle);
        velocity.x = (float) cos(radian);
        velocity.y = (float) sin(radian);
        position += velocity * speed * ticks;
        
        if (position.x + getActualWidth() < boundingRectangle.x)
            position.x = boundingRectangle.x + boundingRectangle.w;
        
        if (position.x > boundingRectangle.x + boundingRectangle.w)
            position.x = boundingRectangle.x;
        
        if (position.y + getActualHeight() < boundingRectangle.y)
            position.y = boundingRectangle.y + boundingRectangle.h;
        
        if (position.y > boundingRectangle.y + boundingRectangle.h)
            position.y = boundingRectangle.y;
        
        updateCenter();
        
    }
    
    void updateSpeed(int dir, float ticks)
    {
        
        if (dir == 1)
        {
            this->speed += acceleration * ticks;
        }
        else if (dir == -1)
        {
            this->speed -= deacceleration * ticks;
        }
        
        if (this->speed > maxSpeed)
        {
            this->speed = maxSpeed;
        }
        
        if (this->speed < 0)
        {
            this->speed = 0;
        }
    }
    
    
    void updateCenter()
    {
        this->center.x = position.x + getActualWidth()/2;
        this->center.y = position.y + getActualHeight()/2;

    }
    
    void updateAngle(int dir)
    {
        
        if (dir == 1)
        {
            angle += 5;
        }
        
        if (dir == -1)
        {
            angle -= 5;
        }
        
        if (angle <= 0)
        {
            angle += 360;
        }
        
        if (angle >= 360)
        {
            angle -= 360;
        }
        
    }
    
    void updateAvgRotation()
    {
        if (numEntities > 0)
            avgRotation = 360 / numEntities;
    }
    
    
    void setAngle(float _angle)
    {
        this->angle = _angle;
    }
    
    void setInitialSpeed(float _speed)
    {
        this->initialSpeed =_speed;
        this->speed = initialSpeed;
    }
    
    void setMaxSpeed(float _maxSpeed)
    {
        this->maxSpeed = _maxSpeed;
    }
    
    void setAcceleration(float _acceleration)
    {
        this->acceleration = _acceleration;
    }
    
    void setDeacceleration(float _deacceleration)
    {
        this->deacceleration = _deacceleration;
    }
    
    void setFriction(float _friction)
    {
        this->friction = _friction;
    }
    
    void setMaxEntityNumber(int _maxNumEntities)
    {
        this->maxNumEntities = _maxNumEntities;
    }
    
    void setHealth(float _health)
    {
        this->health = _health;
    }
    
    void setPlaneType(std::string _type)
    {
        planeType = _type;
    }
    
    void setBulletType(std::string _type)
    {
        bulletType = _type;
    }
    
    void setBulletLevel(std::string _level)
    {
        bulletLevel = _level;
    }
    
    void setMaxNumBulletsPerPress(int _num)
    {
        maxNumBulletsPerPress = _num;
        numBulletsPerPress = maxNumBulletsPerPress;
    }
    
    void loseHealth(std::string _type)
    {
        if (_type == "laserBlue_1" || _type == "laserGreen_1" || _type == "laserRed_1")
        {
            health -= 1;
        }
        else if (_type == "laserBlue_2" || _type == "laserGreen_2" || _type == "laserRed_2")
        {
            health -= 2;
        }
        else if (_type == "laserBlue_3" || _type == "laserGreen_3" || _type == "laserRed_3")
        {
            health -= 3;
        }
    }
    
    void gainHealth(std::string _type)
    {
        
    }
    

};

#endif /* Leader_hpp */
