//
//  Interface.cpp
//  Spaceship Battle Game
//
//  Created by Kelvin Hu on 12/4/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "Interface.hpp"

void Interface::leftmovement(int direction)
{
    if (level == 1)
    {
        if (direction > 0 && level1 < 2)
        {
            level1+=1;
            left->changePosition(Vector2(level1Position[level1*2], level1Position[level1*2+1]));
        }
        else if (direction < 0 && level1 > 0)
        {
            level1-=1;
            left->changePosition(Vector2(level1Position[level1*2], level1Position[level1*2+1]));
        }
    }
    else if(leftType==0)
    {
        if (direction > 0 && level2left < 3)
        {
            level2left+=1;
            left->changePosition(Vector2(level2LPosition[level2left*2], level2LPosition[level2left*2+1]));
        }
        else if (direction < 0 && level2left > 0)
        {
            level2left-=1;
            left->changePosition(Vector2(level2LPosition[level2left*2], level2LPosition[level2left*2+1]));
        }
    }
}

void Interface::rightmovement(int direction)
{
    if (level == 1)
    {
        if (direction > 0 && level1 < 2)
        {
            level1+=1;
            left->changePosition(Vector2(level1Position[level1*2], level1Position[level1*2+1]));
        }
        else if (direction < 0 && level1 > 0)
        {
            level1-=1;
            left->changePosition(Vector2(level1Position[level1*2], level1Position[level1*2+1]));
        }
    }
    else if (rightType==0)
    {
        if (direction > 0 && level2right < 3)
        {
            level2right+=1;
            right->changePosition(Vector2(level2RPosition[level2right*2], level2RPosition[level2right*2+1]));
        }
        else if (direction < 0 && level2right > 0)
        {
            level2right-=1;
            right->changePosition(Vector2(level2RPosition[level2right*2], level2RPosition[level2right*2+1]));
        }
    }
}

void Interface::updateLine(float ticks, SDL_Renderer* renderer){
    if (level == 1){
        left->changeRect(ticks);
        left->render(left->position.x, left->position.y, &(left->rect), renderer);
    }else if(level == 2){
        left->changeRect(ticks);
        left->render(left->position.x, left->position.y, &(left->rect), renderer);
        right->changeRect(ticks);
        right->render(right->position.x, right->position.y, &(right->rect), renderer);
        if (leftType == 0){
            SDL_Rect rect = {0,0,200,50};
            word->render(250, 750, &rect, renderer);
        }else{
            SDL_Rect rect = {400,0,125,50};
            word->render(275, 750, &rect, renderer);
        }if(rightType == 0){
            SDL_Rect rect = {200,0,200,50};
            word->render(950, 750, &rect, renderer);
        }else{
            SDL_Rect rect = {525,0,125,50};
            word->render(975, 750, &rect,renderer);
        }
    }
}

void Interface::click(bool &gameOver, int player, int width, int height, std::string choosePlane, std::string instruction, SDL_Renderer* renderer){
    if (level == 1 && level1 == 2){
        level = 2;
        this->loadFromFile(choosePlane, renderer);
        this->setActualHeight(height);
        this->setActualWidth(width);
        this->word->loadFromFile(wordpath, renderer);
        left->changePosition(Vector2(level2LPosition[level2left*2], level2LPosition[level2left*2+1]));
    }else if (level == 2){
        if (player == 1 && leftType == 0){
            leftType = level2left+1;
        }else if (player == 2 && rightType == 0){
            rightType = level2right+1;
        }if (leftType != 0 && rightType != 0){
            gameOver = false;
        }
    }else if (level == 1 && level1 == 1){
        this->loadFromFile(instruction, renderer);
        this->setActualHeight(height);
        this->setActualWidth(width);
        level = 3;
    }
}

void Interface::update(std::string leftPath, std::string rightPath, SDL_Renderer* renderer)
{
    left->loadFromFile(leftPath, renderer);
    right->loadFromFile(rightPath, renderer);
    left->updateVa();
    right->updateVa();
}

void Interface::back(int width, int height, std::string path, SDL_Renderer* renderer){
    if (level == 2){
        this->loadFromFile(path, renderer);
        this->setActualHeight(height);
        this->setActualWidth(width);
        level = 1;
        level1 = 2;
        level2left = 3;
        level2right = 3;
        leftType = 0;
        rightType = 0;
        left->changePosition(Vector2(level1Position[level1*2], level1Position[level1*2+1]));
        right->changePosition(Vector2(level2RPosition[level2right*2], level2RPosition[level2right*2+1]));
    }else if (level == 3){
        this->loadFromFile(path, renderer);
        this->setActualHeight(height);
        this->setActualWidth(width);
        level = 1;
    }
}

bool Interface::finishChoosing()
{
    if (leftType != 0 && rightType != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

