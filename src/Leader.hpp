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
#include <string>
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
    float ammunitionCounter = 0;
    float ammunitionThreshold = 0;
    Vector2 velocity = Vector2(0, 0);
    Vector2 center = Vector2(0, 0);
    int numEntities = 0;
    int maxNumEntities = 0;
    float health = 0;
    float fullHealth = 0;
    int maxNumBulletsPerPress = 0;
    int numBulletsPerPress = 0;
    std::string planeType;
    std::string bulletType;
    int bulletLevel = 1;
    Vector2 position;
    SDL_Rect boundingRectangle;
    
    Leader(Vector2 _position, int xMin, int xMax, int yMin, int yMax) : LTexture(1)
    {
        this->position = _position;
        this->boundingRectangle = { xMin, yMin, xMax - xMin, yMax - yMin };
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
            speed = 0;
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
    
    void setFullHealth(float _health)
    {
        this->fullHealth = _health;
        this->health = fullHealth;
    }
    
    void setPlaneType(std::string _type)
    {
        planeType = _type;
    }
    
    void setBulletType(std::string _type)
    {
        bulletType = _type;
    }
    
    void setBulletLevel(int _level)
    {
        bulletLevel = _level;
    }
    
    void setMaxNumBulletsPerPress(int _num)
    {
        maxNumBulletsPerPress = _num;
        numBulletsPerPress = maxNumBulletsPerPress;
    }
    
    void setAmmunitionCounter(float _time)
    {
        ammunitionCounter = _time;
    }
    
    void setAmmunitionThreshold(float _time)
    {
        ammunitionThreshold = _time;
    }
    
    void loseHealth(std::string _type)
    {
        std::string to_check = _type.substr(_type.find("_"));
        if (to_check == "_1")
        {
            health -= 0.1;
        }
        else if (to_check == "_2")
        {
            health -= 0.2;
        }
        else if (to_check == "_3")
        {
            health -= 0.4;
        }
        else if (to_check == "_4")
        {
            health -= 0.4;
            speed -= 1;
            if (speed <= 0)
                speed = 0;
        }
        else if (_type == "entity_blue" || _type == "entity_green" || _type == "entity_red")
        {
            health -= 0.1;
        }
        
        if (health <= 0)
        {
            health = 0;
        }
    }
    
    void gainHealth(std::string _type)
    {
        if (health >= fullHealth)
        {
            health = fullHealth;
        }
    }
    

};

#endif /* Leader_hpp */
