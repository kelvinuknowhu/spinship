//
//  BonusBulletEnhance.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "BonusBulletEnhance.hpp"
using namespace std;

float BonusBulletEnhance::globalPrevious  = 0;
float BonusBulletEnhance::globalCounter   = 0;
float BonusBulletEnhance::globalThreshold = 1;
int   BonusBulletEnhance::maxNumObjects   = 1;


void BonusBulletEnhance::setMaxNumObjects(int _num)
{
    maxNumObjects = _num;
}

void BonusBulletEnhance::setGlobalThreshold(float _time)
{
    globalThreshold = _time;
}