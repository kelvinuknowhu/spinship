//
//  BonusEntity.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/3/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef BonusEntity_hpp
#define BonusEntity_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Bonus.hpp"


class BonusEntity : public Bonus
{
public:
    static float globalCounter;
    static float globalPrevious;
    static float globalThreshold;
    static int maxNumObjects;
    static std::string colorArray[3];
    static std::string bonusFileArray[3];
    static std::map<std::string, std::string> entityFileMap;

    std::string color;

    BonusEntity(float x, float y) : Bonus(x, y) {}
    
    static void setMaxNumObjects(int _num);
    static void setGlobalThreshold(float _time);
    
    void setColor(std::string _color)
    {
        color = _color;
    }
    
    std::string getColor()
    {
        return color;
    }
};




#endif /* BonusEntity_hpp */
