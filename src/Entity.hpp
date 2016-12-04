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
    float speed;
    float rotation;
    float detectionDistance;
    float detectionDistanceSquared;
    Vector2 velocity = Vector2(0, 0);
    Vector2 position;
    Vector2 center;
    Vector2 acceleration = Vector2(0, 0);
    Vector2 targetPosition = Vector2(0, 0);
 

    
    SDL_Rect boundingRectangle;

    Entity(Vector2 position, float rotation,
           int screenWidth, int screenHeight) : LTexture(1)
    {
        this->position = position;
        this->detectionDistanceSquared = detectionDistance * detectionDistance;
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
        this->center.x = position.x + getActualWidth()/2;
        this->center.y = position.y + getActualHeight()/2;
        this->rotation = rotation;
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
        this->center.x = position.x + getActualWidth() / 2;
        this->center.y = position.y + getActualHeight() / 2;
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
    
    void setAngle(float angle)
    {
        this->angle = angle;
    }
    
    
    void setSpeed(float _speed)
    {
        speed = _speed;
    }
    
    void setDetectionDistance(float _distance)
    {
        detectionDistance = _distance;
    }
};





#endif /* Entity2_hpp */
