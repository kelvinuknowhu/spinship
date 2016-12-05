//
//  Line.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "Line.hpp"

void Line::updateVa()
{
    width  = this->getTextureWidth();
    height = this->getTextureHeight();
    if (direction > 0)
    {
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = height;
    }
    else
    {
        rect.x = width;
        rect.y = 0;
        rect.w = 0;
        rect.h = height;
        position.x += width;
    }
}

void Line::changePosition(Vector2 newPos){
    position = newPos;
    if (direction > 0)
    {
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = height;
    }
    else
    {
        rect.x = width;
        rect.y = 0;
        rect.w = 0;
        rect.h = height;
        position.x += width;
    }
}

void Line::changeRect(float ticks){
    if (direction>0)
    {
        rect.w += ticks * speed;
        if(rect.w>=width)
        {
            rect.w=width;
        }
    }
    else
    {
        int temp = rect.x;
        rect.x -= ticks * speed;
        if (rect.x <= 0)
        {
            rect.x = 0;
        }
        
        position.x -= temp - rect.x;
        if (position.x <= initX)
        {
            position.x = initX;
        }
        
        rect.w = initX + width - position.x;
        if(rect.w >= width)
        {
            rect.w = width;
        }
    }
}

