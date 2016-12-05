//
//  Gravity.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Gravity_hpp
#define Gravity_hpp

#include <stdio.h>
#include <math.h>
#include "Vector2.hpp"
#include "LTexture.hpp"
#include "Leader.hpp"
#include "Bullet.hpp"
#define PI 3.14159265


class Gravity : public LTexture
{
private:
    int size;
    int gravity_level;
    int distance_discount;
    int distance_tolerance;
    float angle_coefficient;
    
    
public:
    Vector2 position;
    Vector2 center;
    
    
    Gravity(Vector2 position, int size, int nframes = 1) : LTexture(1)
    {
        this->position = position;
        this->size = size;
        this->gravity_level = 10 * size;
        this->angle_coefficient = PI / 180.0f;
        this->angle = 0;
        this->distance_discount = 30;
        this->distance_tolerance = 10; 
    }
    void updateCenter();
    void update(Leader *element, float ticks);
    void update(Bullet *element, float ticks);
    void update(float ticks);
    
};


#endif /* Gravity_hpp */
