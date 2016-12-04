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
    float counter = 0;
    float threshold = 0;


    
    Bonus(float x, float y) : LTexture(1)
    {
        this->position.x = x;
        this->position.y = y;
    }
    
    void updateAngle()
    {
        angle += 5;
    }
    
    bool detectCollision(float _xPos, float _yPos, float _width, float _height)  {
        float upperBound = _yPos;
        float lowerBound = _yPos + _height;
        float leftBound  = _xPos;
        float rightBound = _xPos + _width;

//        std::cout << position.x << "; "<< position.x + getActualWidth()  << "; " << position.y << "; "<< position.y + getActualHeight() << std::endl;
//        std::cout << rightBound << "; "<< leftBound  << "; " << lowerBound << "; "<< upperBound << std::endl;
        if (position.x + getActualWidth() > leftBound
            && position.x  < rightBound
            && position.y < lowerBound
            && position.y + getActualHeight() > upperBound)
            return true;
        return false;
    }
   
    
    
};

#endif /* Bonus_hpp */



