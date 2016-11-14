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
    float separationDistance;
    float detectionDistanceSquared;
    float separationDistanceSquared;
    float detectionAreaScale;
    float seperationAreaScale;
    bool inFlock;
    bool tooCloseToLeader;
    bool tooFarToLeader;
    bool movingAway;
    Vector2 velocity;
    Vector2 position;
    Vector2 center;
    Vector2 acceleration = Vector2(0, 0);
    float distance;
    float previous_distance;

    
    SDL_Rect boundingRectangle;

    Entity(Vector2 position, float speed, float maxSpeed,
           float rotationRadians,
           int nframes, int screenWidth, int screenHeight) : LTexture(nframes)
    {
        this->position = position;
        this->speed = speed;
        this->maxSpeed = maxSpeed;
        this->rotation = rotationRadians;
        this->detectionDistance = 300;
        this->detectionDistanceSquared = detectionDistance * detectionDistance;
        this->separationDistance = 50;
        this->separationDistanceSquared = separationDistance * separationDistance;
        this->velocity = Vector2(0, 0);
        this->boundingRectangle = { 0, 0, screenWidth, screenHeight };
        this->center.x = position.x + getTextureWidth() / 2;
        this->center.y = position.y + getTextureHeight() / 2;
        this->inFlock = true;
        this->tooCloseToLeader = false;
        this->tooFarToLeader = false;
    }

    

    
    void setAngle(float angle) {
        this->angle = angle;
    }
    
     
        
        
        
        
    
    
    void updatePosition(float elapsedTimeSeconds, Leader* leader)
    {
        this->center.x = position.x + getTextureWidth() / 2;
        this->center.y = position.y + getTextureHeight() / 2;
        
        
        if (distance < leader->separationDistanceSquared)
        {
            tooCloseToLeader = true;
        }
        
        
    
        if (tooCloseToLeader) {
            velocity.x = 0;
            velocity.y = 0;
        }
        
        
        
      
        velocity = leader->position - this->position;
        velocity += this->acceleration;
        velocity.Normalize();
        velocity.Limit(maxSpeed);
        position += velocity;
        this->acceleration *= 0;
        
    }
    
    Vector2 separateEntites(std::vector<Entity*>& entities) {
        int count = 0;
        Vector2 steer = Vector2(0, 0);
        
        for (int i = 0; i < entities.size(); i++) {
            if (this != entities[i]) {
                
                Vector2 hv = this->position - entities[i]->position;
                float scale = hv.Length() / this->separationDistance;
                hv.Normalize();
                hv /= scale;
                steer += hv;
            }
            
        }
        
        if (count > 0) {
            steer /= count;
        }
        
        if (steer.LengthSquared() > 0) {
            steer.Normalize();
            steer *= maxSpeed;
        }
        
        return steer;
        
    }
    
    void applyForce(Vector2& force) {
        this->acceleration += force;
    }
        

};





#endif /* Entity2_hpp */
