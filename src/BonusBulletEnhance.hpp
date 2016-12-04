//
//  BonusBulletEnhance.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef BonusBulletEnhance_hpp
#define BonusBulletEnhance_hpp

#include <stdio.h>
#include "Bonus.hpp"

class BonusBulletEnhance : public Bonus
{
public:
    static float globalCounter;
    static float globalPrevious;
    static float globalThreshold;
    static int maxNumObjects;
    
    BonusBulletEnhance(float x, float y) : Bonus(x, y) {}
    
    static void setMaxNumObjects(int _num);
    static void setGlobalThreshold(float _time);
};




#endif /* BonusBulletEnhance_hpp */
