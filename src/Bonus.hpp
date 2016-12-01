//
//  Bonus.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/1/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Bonus_hpp
#define Bonus_hpp

#include <stdio.h>
#include "LTexture.hpp"
#include "Vector2.hpp"


class Bonus : public LTexture
{
    
public:
    Vector2 position;
    
    Bonus(float x, float y) : LTexture(1)
    {
        this->position.x = x;
        this->position.y = y;
    }
    
    void updateAngle()
    {
        angle += 1;
    }
    
    bool detectCollision(int _xPos, int _yPos, int _width, int _height)  {
        int lowerBound = _yPos;
        int upperBound = _yPos + _height;
        int leftBound  = _xPos;
        int rightBound = _xPos + _width;
        
        if (position.x + getTextureWidth() > leftBound
            && position.x  < rightBound
            && position.y < upperBound
            && position.y + getTextureHeight() > lowerBound)
            return true;
        return false;
    }
    
    
};


#endif /* Bonus_hpp */
