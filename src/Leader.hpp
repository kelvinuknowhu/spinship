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

#define PI 3.14159265

class Leader : public LTexture {
public:
    float speed;
    float maxSpeed;
    float radian;
    float detectionDistance;
    float separationDistance;
    float detectionDistanceSquared;
    float separationDistanceSquared;
    Vector2 velocity;
    Vector2 position;
    Vector2 center;
    SDL_Rect boundingRectangle;
    int numEntities;
    int numEntitiesMax;

    
    Leader(Vector2 position, float speed,
           float initialAngle,
           float detectionDistance, float separationDistance, int numEntitiesMax,
           int nframes, int screenWidth, int screenHeight) : LTexture(nframes)
    {
        this->position = position;
        this->speed = speed;
        this->angle = initialAngle;
        this->radian = angleToRadian(initialAngle - 90);
        this->detectionDistance = detectionDistance;
        this->detectionDistanceSquared = detectionDistance * detectionDistance;
        this->separationDistance = separationDistance;
        this->separationDistanceSquared = separationDistance * separationDistance;
        this->velocity = Vector2(0, 0); 
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
        this->numEntities = 0;
        this->numEntitiesMax = numEntitiesMax;

    }
    

    void updatePosition(int dir)
    {
        this->speed = 5.0;
        if (dir == 1)
        {
            radian = angleToRadian(angle - 90);
            velocity.x = (float) cos(radian);
            velocity.y = (float) sin(radian);
            position += velocity * speed;
        }
        else if (dir == -1)
        {
            radian = angleToRadian(angle - 90);
            velocity.x = (float) cos(radian);
            velocity.y = (float) sin(radian);
            position -= velocity * speed;
        }
        
        if (position.x < boundingRectangle.x)
            position.x = boundingRectangle.x + boundingRectangle.w;
        
        if (position.x > boundingRectangle.x + boundingRectangle.w)
            position.x = boundingRectangle.x;
        
        if (position.y < boundingRectangle.y)
            position.y = boundingRectangle.y + boundingRectangle.h;
        
        if (position.y > boundingRectangle.y + boundingRectangle.h)
            position.y = boundingRectangle.y;
        
        updateCenter();
        
    }
    
    
    void updateCenter()
    {
        this->center.x = position.x + getTextureWidth()/2;
        this->center.y = position.y + getTextureHeight()/2;

    }
    
    void updateAngle(int dir)
    {
        
        if (dir == 1)
        {
            angle += 5;
        }
        
        if (dir == -1) {
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
    
    
 
    
    
    float angleToRadian(float angle)
    {
        return (float) angle * PI / 180.0f;
    }
    

};

#endif /* Leader_hpp */
