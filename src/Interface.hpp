//
//  Interface.hpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

#include <stdio.h>
#include "LTexture.hpp"
#include "Line.hpp"

class Interface : public LTexture
{
public:
    
    int level;
    int level1;
    int level2left;
    int level2right;
    int level1Position[6];
    int level2LPosition[8];
    int level2RPosition[8];
    int leftType;
    int rightType;
    std::string wordpath;
    std::string leftTypeArray[4]    = { "playerShip2_red", "playerShip1_red", "playerShip3_orange", "playerShip4_orange" };
    std::string leftBulletArray[4]  = { "laserRed", "laserRed", "laserOrange", "laserOrange" };
    std::string rightTypeArray[4]   = { "playerShip2_green", "playerShip1_green", "playerShip3_black", "playerShip4_black" };
    std::string rightBulletArray[4] = { "laserGreen", "laserGreen", "laserBlack", "laserBlack" };
    float initialSpeedArray[4]      = { 90, 30, 150, 60 };
    float maxSpeedArray[4]          = { 900, 300, 1500, 600 };
    float accelerationArray[4]      = { 180, 60, 300, 120 };
    float decelerationArray[4]    = { 540, 180, 900, 360 };
    float frictionArray[4]          = { 36, 12, 60, 24 };
    float healthArray[4]            = { 150, 250, 50, 100 };
    int powerArray[4]               = { 3, 5, 1, 2 };
    Line *left;
    Line *right;
    LTexture *word;
    Vector2 position;
    
    Interface(Vector2 position, std::string word) : LTexture(1)
    {
        this->position = position;
        level = 1;
        level1 = 2;
        level2left = 3;
        level2right = 3;
        leftType = 0;
        rightType = 0;
        this->wordpath = word;
        float temp_level1Position[6]  = {700 * 1.2, 450 * 1.2857, 700*1.2, 350 *1.2857, 700*1.2, 250*1.2857};
        float temp_level2LPosition[8] = {70*1.2, 560*1.2857, 70*1.2, 440*1.2857, 70*1.2, 320*1.2857, 70*1.2, 200*1.2857};
        float temp_level2RPosition[8] = {700*1.2, 560*1.2857, 700*1.2, 440*1.2857, 700*1.2, 320*1.2857, 700*1.2, 200*1.2857};
        for (int i = 0; i < 6; i++)
        {
            level1Position[i] = temp_level1Position[i];
        }
        for (int i = 0; i < 8; i++)
        {
            level2LPosition[i] = temp_level2LPosition[i];
            level2RPosition[i] = temp_level2RPosition[i];
        }
        this->word = new LTexture(1);
        this->left = new Line(Vector2(level1Position[level1*2], level1Position[level1*2+1]),1);
        this->right = new Line(Vector2(level2RPosition[level2right*2], level2RPosition[level2right*2+1]),-1);
    }
    
    ~Interface()
    {
        delete left;
        delete right;
        delete word;
        left = NULL;
        right = NULL;
        word = NULL;
    }
    
    void leftmovement(int direction);
    void rightmovement(int direction);
    void updateLine(float ticks, SDL_Renderer* renderer);
    void click(bool &gameOver, int player, int width, int height, std::string choosePlane,std::string instruction, SDL_Renderer* renderer = NULL);
    void update(std::string leftPath, std::string rightPath, SDL_Renderer* renderer);
    void back(int width, int height, std::string path, SDL_Renderer* renderer);
    bool finishChoosing();
    
};



#endif /* Interface_hpp */
