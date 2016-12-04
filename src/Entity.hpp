//
//  Entity.hpp
//  Flocking Spaceships
//
//  Created by Kelvin Hu on 11/03/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#define PI 3.14159265

#include <stdio.h>
#include <math.h>
#include <vector>
#include "Vector2.hpp"
#include "Leader.hpp"
#include "LTexture.hpp"
#include "Utility.h"

class Entity : public LTexture
{
public:
    float speed = 0;
    float rotation = 0;
    float counter = 0;
    float threshold = 0;
    Vector2 velocity = Vector2(0, 0);
    Vector2 position = Vector2(0, 0);
    Vector2 center = Vector2(0, 0);
    Vector2 acceleration = Vector2(0, 0);
    Vector2 targetPosition = Vector2(0, 0);
    
    SDL_Rect boundingRectangle;

    Entity(Vector2 position, int screenWidth, int screenHeight) : LTexture(1)
    {
        this->position = position;
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
        this->center.x = position.x + getActualWidth()/2;
        this->center.y = position.y + getActualHeight()/2;
    }

    
    void updatePosition(Leader* leader)
    {
        float scale = 3.0;
        velocity = targetPosition - center;
        velocity.Normalize();
        position += velocity * scale;
        acceleration *= 0;
        
    }
    
    void updateCenter()
    {
        this->center.x = position.x + getActualWidth()/2;
        this->center.y = position.y + getActualHeight()/2;
    }
    
    void updateTargetPosition(Leader* leader)
    {
        float distance = 1.5 * (getActualWidth() + getActualHeight());
        float entityRadian = angleToRadian(rotation);
        Vector2 new_position = leader->center + Vector2(distance * cos(entityRadian), distance * sin(entityRadian));
        targetPosition = new_position;
        
        rotation += 1;
        if (rotation >= 360)
        {
            rotation = 0;
        }
    }
    
    void updateCounter(float ticks)
    {
        counter += ticks;
        std::cout << counter << std::endl;
    }
    
    
    void setAngle(float angle)
    {
        this->angle = angle;
    }
    
    
    void setSpeed(float _speed)
    {
        speed = _speed;
    }
    
    void setThreshold(float _time)
    {
        threshold = _time;
    }
    
    bool checkIfCounterDone()
    {
        if (counter > threshold)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    
};

#endif /* Entity2_hpp */
