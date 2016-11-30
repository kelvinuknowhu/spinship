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

class Entity : public LTexture {
public:
    float speed;
    float maxSpeed;
    float rotation;
    float detectionDistance;
    float detectionDistanceSquared;
    float separationDistance;
    float separationDistanceSquared;
    Vector2 velocity = Vector2(0, 0);
    Vector2 position;
    Vector2 center;
    Vector2 acceleration = Vector2(0, 0);
    Vector2 targetPosition = Vector2(0, 0);
 

    
    SDL_Rect boundingRectangle;

    Entity(Vector2 position, float speed, float maxSpeed,
           int nframes, float rotation,
           int screenWidth, int screenHeight) : LTexture(nframes)
    {
        this->position = position;
        this->speed = speed;
        this->maxSpeed = maxSpeed;
        this->detectionDistance = 300.0f;
        this->detectionDistanceSquared = detectionDistance * detectionDistance;
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
        this->center.x = position.x + getTextureWidth()/2;
        this->center.y = position.y + getTextureHeight()/2;
        this->rotation = rotation;
    }

    

    
    void setAngle(float angle) {
        this->angle = angle;
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
        this->center.x = position.x + getTextureWidth() / 2;
        this->center.y = position.y + getTextureHeight() / 2;
    }
    
    void updateTargetPosition(Leader* leader) {
        float distance = 2 * getTextureHeight();
        float entityRadian = angleToRadian(rotation);
        Vector2 new_position = leader->center + Vector2(distance * cos(entityRadian), distance * sin(entityRadian));
        targetPosition = new_position;
        rotation += 1.0f;
        
        if (rotation >= 360)
        {
            rotation = 0.0f;
        }
    }
    
//    Vector2 separateEntites(std::vector<Entity*>& entities) {
//        int count = 0;
//        Vector2 steer = Vector2(0, 0);
//        
//        for (int i = 0; i < entities.size(); i++) {
//            if (this != entities[i]) {
//                Vector2 hv = this->position - entities[i]->position;
//                float scale = hv.Length() / this->separationDistance;
//                hv.Normalize();
//                hv /= scale;
//                steer += hv;
//            }
//        }
//        
//        if (count > 0) {
//            steer /= count;
//        }
//        
//        if (steer.LengthSquared() > 0) {
//            steer.Normalize();
//            steer *= maxSpeed;
//        }
//        
//        return steer;
//        
//    }
    
//    void applyForce(Vector2& force)
//    {
//        this->acceleration += force;
//    }
    
    float angleToRadian(float angle)
    {
        return (float) angle * PI / 180.0f;
    }

};





#endif /* Entity2_hpp */
