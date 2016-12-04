//
//  HealthBar.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "HealthBar.hpp"
using namespace std;

void HealthBar::setClipDimensions(int _x, int _y, int _w, int _h)
{
    rect.x = _x;
    rect.y = _y;
    rect.w = _w;
    rect.h = _h;
}

void HealthBar::updateHealthBarLength(float percentage, string location)
{
    if (location == "left")
    {
        if (percentage > 0)
            rect.w = (int) (percentage * getActualWidth());
        else
            rect.w = 0;
    }
    else if (location == "right")
    {
        if (percentage > 0)
            rect.w = (int) (percentage * getActualWidth());
        else
            rect.w = 0;
    }
    
}
