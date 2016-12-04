//
//  BonusBulletAmmunition.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "BonusBulletAmmunition.hpp"
using namespace std;

float BonusBulletAmmunition::globalPrevious  = 0;
float BonusBulletAmmunition::globalCounter   = 0;
float BonusBulletAmmunition::globalThreshold = 1;
int   BonusBulletAmmunition::maxNumObjects   = 1;


void BonusBulletAmmunition::setMaxNumObjects(int _num)
{
    maxNumObjects = _num;
}

void BonusBulletAmmunition::setGlobalThreshold(float _time)
{
    globalThreshold = _time;
}