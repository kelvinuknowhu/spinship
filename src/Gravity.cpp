//
//  Gravity.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "Gravity.hpp"

void Gravity::updateCenter()
{
    int width = this->getActualWidth();
    int height = this->getActualHeight();
    center += Vector2(width/2, height/2);
}

void Gravity::update(Leader *element, float ticks = 1)
{
    float distance = center.Distance(element->center)/distance_discount;
    Vector2 temp = center - element->center;
    if (temp.Length()>distance_tolerance)
    {
        element->position += temp * (gravity_level / (distance * distance)) * ticks * 0.5;
    }
}

void Gravity::update(Bullet *element, float ticks = 1)
{
    float distance = center.Distance(element->position)/distance_discount;
    Vector2 temp = center - element->position;
    if (temp.Length() > distance_tolerance)
    {
        element->position += temp * (gravity_level / (distance * distance)) * ticks;
    }
}

void Gravity::update(float ticks = 1)
{
    angle -= ticks * angle_coefficient * 1000;
}