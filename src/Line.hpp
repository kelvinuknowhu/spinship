//
//  Line.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "LTexture.hpp"
#include "Vector2.hpp"

class Line : public LTexture
{
public:
    Line(Vector2 initPosition = Vector2(0,0), int direction = 1, int nframe = 1):LTexture(nframe){
        position = initPosition;
        this->direction = direction;
        speed = 500.0f;
        initX = initPosition.x;
    }
    int direction;
    Vector2 position;
    SDL_Rect rect = {0,0,0,0};
    int width;
    int height;
    int initX;
    void changeRect(float ticks);
    void changePosition(Vector2 newPos);
    void updateVa();
    
private:
    float speed;
};


#endif /* Line_hpp */
