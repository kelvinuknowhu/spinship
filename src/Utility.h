
//
//  Utility.h
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/2/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#define PI 3.14159265

inline float angleToRadian(float angle)
{
    return (float) angle * PI / 180.0f;
}

inline int generate_random_int(int min, int max)
{
    srand((unsigned int)clock());
    int num = min + (rand() % (max - min));
    return num;
}

#endif /* Utility_h */
