//
//  BonusEntity.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/3/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "BonusEntity.hpp"
#include <string>
#include <map>

using namespace std;
float BonusEntity::globalPrevious = 0;
float BonusEntity::globalCounter = 0;
float BonusEntity::globalThreshold = 10;
int BonusEntity::maxNumObjects = 1;

string BonusEntity::colorArray[3] = { "blue", "green", "red" };
string BonusEntity::bonusFileArray[3] = { "ufo_blue.png", "ufo_green.png", "ufo_red.png" };
map<string, string> makeEntityFileMap()
{
    map<string, string> map;
    map["blue"] = "entity_blue.png";
    map["green"] = "entity_green.png";
    map["red"] = "entity_red.png";
    return map;
}
map<string, string> BonusEntity::entityFileMap = makeEntityFileMap();


void BonusEntity::setMaxNumObjects(int _num)
{
    maxNumObjects = _num;
}

void BonusEntity::setGlobalThreshold(float _time)
{
    globalThreshold = _time;
}
