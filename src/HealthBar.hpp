//
//  HealthBar.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef HealthBar_hpp
#define HealthBar_hpp

#include <stdio.h>
#include "LTexture.hpp"
#include "Vector2.hpp"

class HealthBar : public LTexture
{
public:
    Vector2 position = Vector2(0, 0);
    SDL_Rect rect = { 0, 0, 0, 0 };
    
    HealthBar(Vector2 initPosition) : LTexture(1)
    {
        position = initPosition;
    }
    void updateHealthBarLength(float percentage, std::string location);
    void setClipDimensions(int _x, int _y, int _w, int _h);
    void setHealthBarLength(int _length);
};





#endif /* HealthBar_hpp */
