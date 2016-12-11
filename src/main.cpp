/*=============================================================================
 |  Final Project:  Spaceship Battle Game
 |
 |         Author:  Siyuan Hu (Kelvin)
 |       Language:  C++11
 |         To Run:  Build in Xcode with essential frameworks added to Build Phases
 |
 |          Class:  Introduction to Game Programming
 |     Instructor:  John Sterling
 |
 +-----------------------------------------------------------------------------
 |    Description: An adorable astral arcade game that you will love to play!
 |
 *===========================================================================*/


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "Leader.hpp"
#include "HealthBar.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "BonusEntity.hpp"
#include "BonusBulletEnhance.hpp"
#include "BonusBulletAmmunition.hpp"
#include "Gravity.hpp"
#include "Interface.hpp"



#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
int ACTUAL_WINDOW_WIDTH = 0;
int ACTUAL_WINDOW_HEIGHT = 0;
const int HEALTH_BAR_HEIGHT = 40;

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

const string BASE_DIR = "/Users/Kelvin/Desktop/Game_Programming/SpaceshipBattleGame/";
const string LEADER_DIR = BASE_DIR + "img/battle-plane/";
const string ENTITY_DIR = BASE_DIR + "img/entity-plane/";
const string BULLET_DIR  = BASE_DIR + "img/laser-bullet/";
const string BONUS_DIR = BASE_DIR + "img/bonus/";
const string HEALTH_BAR_DIR = BASE_DIR + "img/health-bar/";
const string BACKGROUND_PATH = BASE_DIR + "img/background/purple.png";
const string GRAVITY_PATH = BASE_DIR + "img/black-hole/meteor.png";

const string INTERFACE_PATH = BASE_DIR + "img/interface/interface_start.png";
const string LIGHTBEAM_PATH = BASE_DIR + "img/interface/lightBeam.png";
const string LIGHTBEAM_PATH_FLIP = BASE_DIR + "img/interface/lightBeam_flip.png";
const string CHOOSEPLANE_PATH = BASE_DIR + "img/interface/interface_choose_plane.png";
const string WORD_PATH = BASE_DIR + "img/interface/word.png";
const string INSTRUCTION_PATH = BASE_DIR + "img/interface/instruction.png";

Leader* leader1;
Leader* leader2;

HealthBar* leader1HealthBar;
HealthBar* leader2HealthBar;
LTexture* leader1HealthBarFrame;
LTexture* leader2HealthBarFrame;

vector<Entity*> leader1Entities;
vector<Entity*> leader2Entities;

vector<Bullet*> leader1Bullets;
vector<Bullet*> leader1EntityBullets;
vector<Bullet*> leader2Bullets;
vector<Bullet*> leader2EntityBullets;

vector<BonusEntity*> bonus_entity_objects;
vector<BonusBulletEnhance*> bonus_bullet_enhance_objects;
vector<BonusBulletAmmunition*> bonus_bullet_ammunition_objects;

vector<Gravity*> gravity_objects;
const int NUM_GRAVITY_OBJECTS = 2;


bool init();
bool loadMedia();
void enable2D(int width, int height);
void draw_rect(int x, int y, int width, int height);
Vector2 generate_random_position(float left, float right, float top, float down);
int generate_random_int(int min, int max);

int main(int argc, const char * argv[])
{
    
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        Vector2 interface_init_position(0, 0);
        Interface it(interface_init_position, WORD_PATH);
        it.loadFromFile(INTERFACE_PATH, renderer);
        it.setActualWidth(ACTUAL_WINDOW_WIDTH);
        it.setActualHeight(ACTUAL_WINDOW_HEIGHT);
        it.update(LIGHTBEAM_PATH, LIGHTBEAM_PATH_FLIP, renderer);
        LTexture background(1);
        background.loadFromFile(BACKGROUND_PATH, renderer);

        BonusEntity::setGlobalThreshold(5);
        BonusEntity::setMaxNumObjects(3);
        BonusBulletAmmunition::setGlobalThreshold(7);
        BonusBulletAmmunition::setMaxNumObjects(3);
        BonusBulletEnhance::setGlobalThreshold(9);
        BonusBulletEnhance::setMaxNumObjects(1);
        
        for (int i = 1; i <= NUM_GRAVITY_OBJECTS; i++)
        {
            Vector2 gravity_position = generate_random_position(150 * i, ACTUAL_WINDOW_WIDTH - 150 * i, 150 * i, ACTUAL_WINDOW_HEIGHT - 150 * i);
            Gravity* tempGravity = new Gravity(gravity_position, 1);
            tempGravity->loadFromFile(GRAVITY_PATH, renderer);
            tempGravity->setActualWidth(150);
            tempGravity->setActualHeight(150);
            tempGravity->updateCenter();
            gravity_objects.push_back(tempGravity);
        }
        
        
        Vector2 leader1HealthBar_init_position(0, 10);
        leader1HealthBar = new HealthBar(leader1HealthBar_init_position);
        leader1HealthBar->loadFromFile(HEALTH_BAR_DIR + "healthBar_left.png", renderer);
        leader1HealthBar->setActualWidth(ACTUAL_WINDOW_WIDTH/2 - 10);
        leader1HealthBar->setActualHeight(HEALTH_BAR_HEIGHT);
        leader1HealthBar->setClipDimensions(0, 0, leader1HealthBar->getActualWidth(), leader1HealthBar->getActualHeight());
        
        Vector2 leader2HealthBar_init_position(ACTUAL_WINDOW_WIDTH/2 + 10, 10);
        leader2HealthBar = new HealthBar(leader2HealthBar_init_position);
        leader2HealthBar->loadFromFile(HEALTH_BAR_DIR + "healthBar_right.png", renderer);
        leader2HealthBar->setActualWidth(ACTUAL_WINDOW_WIDTH/2 - 10);
        leader2HealthBar->setActualHeight(HEALTH_BAR_HEIGHT);
        leader2HealthBar->setClipDimensions(0, 0, leader2HealthBar->getActualWidth(), leader2HealthBar->getActualHeight());
        
        leader1HealthBarFrame = new LTexture(1);
        leader1HealthBarFrame->loadFromFile(HEALTH_BAR_DIR + "healthBarFrame.png", renderer);
        leader1HealthBarFrame->setActualWidth(ACTUAL_WINDOW_WIDTH/2 - 10);
        leader1HealthBarFrame->setActualHeight(HEALTH_BAR_HEIGHT);
        
        leader2HealthBarFrame = new LTexture(1);
        leader2HealthBarFrame->loadFromFile(HEALTH_BAR_DIR + "healthBarFrame.png", renderer);
        leader2HealthBarFrame->setActualWidth(ACTUAL_WINDOW_WIDTH/2 - 10);
        leader2HealthBarFrame->setActualHeight(HEALTH_BAR_HEIGHT);
        
        
        SDL_Event event;
        bool done = false;
        bool gameOver = true;
        bool notPressed = true;
        float currentFrameTime = 0;
        float previousFrameTime = 0;
        float elapsedTime = 0;
        float pressTick = 0;

        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || KEYS[SDL_SCANCODE_ESCAPE])
                {
                    done = true;
                }
                
            }
            currentFrameTime = (float) SDL_GetTicks() / 1000.0f;
            elapsedTime = currentFrameTime - previousFrameTime;
            previousFrameTime = currentFrameTime;
            
    
            if (!gameOver)
            {
       
                // Draw the background
                background.render(0, 0, NULL, renderer);
                
                for (Gravity* g : gravity_objects)
                {
                    g->render(g->position.x, g->position.y, NULL, renderer);
                    g->update(elapsedTime);
                    g->update(leader1, elapsedTime);
                    g->update(leader2, elapsedTime);
                }
                
                BonusEntity::globalCounter = currentFrameTime - BonusEntity::globalPrevious;
                if (bonus_entity_objects.size() >= BonusEntity::maxNumObjects)
                {
                    BonusEntity::globalCounter = 0;
                }
                if (BonusEntity::globalCounter > BonusEntity::globalThreshold && bonus_entity_objects.size() < BonusEntity::maxNumObjects)
                {
                    Vector2 pos = generate_random_position(0, ACTUAL_WINDOW_WIDTH - 60, 0, ACTUAL_WINDOW_HEIGHT - 60);
                    BonusEntity* tempBonusEntity = new BonusEntity(pos.x, pos.y);
                    int index = generate_random_int(0, 3);
                    tempBonusEntity->loadFromFile(BONUS_DIR + BonusEntity::bonusFileArray[index], renderer);
                    tempBonusEntity->setColor(BonusEntity::colorArray[index]);
                    tempBonusEntity->setActualWidth(60);
                    tempBonusEntity->setActualHeight(60);
                    bonus_entity_objects.push_back(tempBonusEntity);
                    BonusEntity::globalPrevious = currentFrameTime;
                    BonusEntity::globalCounter = 0;
                }
                for (vector<BonusEntity*>::iterator it = bonus_entity_objects.begin(); it != bonus_entity_objects.end();)
                {
                    BonusEntity* b = *it;
                    if (b->detectCollision(leader1->position.x, leader1->position.y, leader1->getActualWidth(), leader1->getActualHeight()))
                    {
                        if (leader1->numEntities < leader1->maxNumEntities)
                        {
                            string color = b->getColor();
                            Vector2 init_position = b->position;
                            Entity* tempEntity = new Entity(init_position);
                            tempEntity->loadFromFile(ENTITY_DIR + BonusEntity::entityFileMap[color], renderer);
                            tempEntity->setThreshold(30);
                            tempEntity->setActualWidth(60);
                            tempEntity->setActualHeight(60);
                            tempEntity->setSpeed(1);
                            tempEntity->setBulletThreshold(1);
                            tempEntity->setBulletType("entity_" + color);
                            leader1Entities.push_back(tempEntity);
                            leader1->numEntities++;
                        }
                        bonus_entity_objects.erase(it);
                        delete b;
                        
                    }
                    else if (b->detectCollision(leader2->position.x, leader2->position.y, leader2->getActualWidth(), leader2->getActualHeight()))
                    {
                        if (leader2->numEntities < leader2->maxNumEntities)
                        {
                            string color = b->getColor();
                            Vector2 init_position = b->position;
                            Entity* tempEntity = new Entity(init_position);
                            tempEntity->loadFromFile(ENTITY_DIR + BonusEntity::entityFileMap[color], renderer);
                            tempEntity->setThreshold(30);
                            tempEntity->setActualWidth(60);
                            tempEntity->setActualHeight(60);
                            tempEntity->setSpeed(1);
                            tempEntity->setBulletThreshold(1);
                            tempEntity->setBulletType("entity_" + color);
                            leader2Entities.push_back(tempEntity);
                            leader2->numEntities++;
                        }
                        bonus_entity_objects.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updateAngle();
                        it++;
                    }
                }
                

                BonusBulletEnhance::globalCounter = currentFrameTime - BonusBulletEnhance::globalPrevious;
                if (bonus_bullet_enhance_objects.size() > BonusBulletEnhance::maxNumObjects)
                {
                    BonusBulletEnhance::globalCounter = 0;
                }
                if (BonusBulletEnhance::globalCounter > BonusBulletEnhance::globalThreshold &&
                    bonus_bullet_enhance_objects.size() < BonusBulletEnhance::maxNumObjects)
                {
                    Vector2 pos = generate_random_position(0, ACTUAL_WINDOW_WIDTH - 20, 0, ACTUAL_WINDOW_HEIGHT - 30);
                    BonusBulletEnhance* tempBonusBulletEnhance = new BonusBulletEnhance(pos.x, pos.y);
                    tempBonusBulletEnhance->loadFromFile(BONUS_DIR + "level-up.png", renderer);
                    tempBonusBulletEnhance->setActualWidth(40);
                    tempBonusBulletEnhance->setActualHeight(60);
                    bonus_bullet_enhance_objects.push_back(tempBonusBulletEnhance);
                    BonusBulletEnhance::globalPrevious = currentFrameTime;
                    BonusBulletEnhance::globalCounter = 0;
                }
                for (vector<BonusBulletEnhance*>::iterator it = bonus_bullet_enhance_objects.begin(); it != bonus_bullet_enhance_objects.end();)
                {
                    BonusBulletEnhance* b = *it;
                    if (b->detectCollision(leader1->position.x, leader1->position.y, leader1->getActualWidth(), leader1->getActualHeight()))
                    {
                        if (leader1->bulletLevel < 4)
                        {
                            leader1->bulletLevel++;
                        }
                        bonus_bullet_enhance_objects.erase(it);
                        delete b;
                        
                    }
                    else if (b->detectCollision(leader2->position.x, leader2->position.y, leader2->getActualWidth(), leader2->getActualHeight()))
                    {
                        if (leader2->bulletLevel < 4)
                        {
                            leader2->bulletLevel++;
                        }
                        bonus_bullet_enhance_objects.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updateAngle();
                        it++;
                    }
                }
                
                BonusBulletAmmunition::globalCounter = currentFrameTime - BonusBulletAmmunition::globalPrevious;
                if (bonus_bullet_ammunition_objects.size() > BonusBulletAmmunition::maxNumObjects)
                {
                    BonusBulletAmmunition::globalCounter = 0;
                }
                if (BonusBulletAmmunition::globalCounter > BonusBulletAmmunition::globalThreshold &&
                    bonus_bullet_ammunition_objects.size() < BonusBulletAmmunition::maxNumObjects)
                {
                    Vector2 pos = generate_random_position(0, ACTUAL_WINDOW_WIDTH - 20, 0, ACTUAL_WINDOW_HEIGHT - 20);
                    BonusBulletAmmunition* tempBonusBulletAmmunition = new BonusBulletAmmunition(pos.x, pos.y);
                    tempBonusBulletAmmunition->loadFromFile(BONUS_DIR + "bullet-double.png", renderer);
                    tempBonusBulletAmmunition->setActualWidth(50);
                    tempBonusBulletAmmunition->setActualHeight(50);
                    bonus_bullet_ammunition_objects.push_back(tempBonusBulletAmmunition);
                    BonusBulletAmmunition::globalPrevious = currentFrameTime;
                    BonusBulletAmmunition::globalCounter = 0;
                }
                for (vector<BonusBulletAmmunition*>::iterator it = bonus_bullet_ammunition_objects.begin(); it != bonus_bullet_ammunition_objects.end();)
                {
                    BonusBulletAmmunition* b = *it;
                    if (b->detectCollision(leader1->position.x, leader1->position.y, leader1->getActualWidth(), leader1->getActualHeight()))
                    {
                        leader1->maxNumBulletsPerPress *= 2;
                        bonus_bullet_ammunition_objects.erase(it);
                        delete b;
                        
                    }
                    else if (b->detectCollision(leader2->position.x, leader2->position.y, leader2->getActualWidth(), leader2->getActualHeight()))
                    {
                        leader2->maxNumBulletsPerPress *= 2;
                        bonus_bullet_ammunition_objects.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updateAngle();
                        it++;
                    }
                }
                
                for (vector<Bullet*>::iterator it = leader1Bullets.begin(); it != leader1Bullets.end();)
                {
                    Bullet* b = *it;
                    if (b->offScreen(ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT))
                    {
                        leader1Bullets.erase(it);
                        delete b;
                    }
                    else if (leader2->detectCollision(b->position.x, b->position.y, b->getActualWidth(), b->getActualHeight()))
                    {
                        leader2->loseHealth(b->bulletName);
                        leader1Bullets.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updatePosition(elapsedTime);
                        it++;
                    }
                }
                
                for (vector<Bullet*>::iterator it = leader2Bullets.begin(); it != leader2Bullets.end();)
                {
                    Bullet* b = *it;
                    if (b->offScreen(ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT))
                    {
                        leader2Bullets.erase(it);
                        delete b;
                    }
                    else if (leader1->detectCollision(b->position.x, b->position.y, b->getActualWidth(), b->getActualHeight()))
                    {
                        leader1->loseHealth(b->bulletName);
                        
                        leader2Bullets.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updatePosition(elapsedTime);
                        it++;
                    }
                }
                
                for (vector<Bullet*>::iterator it = leader1EntityBullets.begin(); it != leader1EntityBullets.end();)
                {
                    Bullet* b = *it;
                    if (b->offScreen(ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT))
                    {
                        leader1EntityBullets.erase(it);
                        delete b;
                    }
                    else if (leader2->detectCollision(b->position.x, b->position.y, b->getActualWidth(), b->getActualHeight()))
                    {
                        leader2->loseHealth(b->bulletName);
                        leader1EntityBullets.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updatePosition(elapsedTime);
                        it++;
                    }
                }
                
                for (vector<Bullet*>::iterator it = leader2EntityBullets.begin(); it != leader2EntityBullets.end();)
                {
                    Bullet* b = *it;
                    if (b->offScreen(ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT))
                    {
                        leader2EntityBullets.erase(it);
                        delete b;
                    }
                    else if (leader1->detectCollision(b->position.x, b->position.y, b->getActualWidth(), b->getActualHeight()))
                    {
                        leader1->loseHealth(b->bulletName);
                        leader2EntityBullets.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updatePosition(elapsedTime);
                        it++;
                    }
                }
                
                
                // Draw the first player
                leader1->render(leader1->position.x, leader1->position.y, NULL, renderer);
                leader1->updateCenter();
                leader1->updateAvgRotation();
                
                
                // Draw the second player
                leader2->render(leader2->position.x, leader2->position.y, NULL, renderer);
                leader2->updateCenter();
                leader2->updateAvgRotation();

                
                // Draw and update position of the first player's entities
                int counter = 0;
                for (vector<Entity*>::iterator it = leader1Entities.begin(); it != leader1Entities.end();)
                {
                    Entity* e = *it;
                    if (!e->checkIfDisappear())
                    {
                        e->updateCenter();
                        e->updateCounter(elapsedTime);
                        e->updateBulletCounter(elapsedTime);
                        e->updatePosition();
                        e->updateTargetPosition(leader1);
                        Vector2 target = leader2->center - e->position;
                        float angle = atan2f(target.y, target.x) * 180 / PI;
                        e->setAngle(angle);
                        e->render(e->position.x, e->position.y, NULL, renderer);
                        if (counter > 0)
                        {
                            float rotationShouldHave = leader1Entities[0]->rotation + leader1->avgRotation * counter;
                            if (leader1Entities[counter]->rotation < rotationShouldHave)
                                leader1Entities[counter]->rotation = rotationShouldHave;
                        }
                        if (e->checkIfFireBullet())
                        {
                            Vector2 position = e->center;
                            Bullet* tempBullet = new Bullet(position, e->angle, e->bulletType);
                            tempBullet->loadFromFile(BULLET_DIR + e->bulletType + ".png", renderer);
                            tempBullet->setPosition(position);
                            leader1EntityBullets.push_back(tempBullet);
                        }
                        counter++;
                        it++;
                    }
                    else
                    {
                        leader1->numEntities--;
                        leader1Entities.erase(it);
                        delete e;
                    }
                }
                
                // Draw and update position of the second player's entities
                counter = 0;
                for (vector<Entity*>::iterator it = leader2Entities.begin(); it != leader2Entities.end();)
                {
                    Entity* e = *it;
                    if (!e->checkIfDisappear())
                    {
                        e->updateCenter();
                        e->updateCounter(elapsedTime);
                        e->updateBulletCounter(elapsedTime);
                        e->updateTargetPosition(leader2);
                        e->updatePosition();
                        Vector2 target = leader1->center - e->position;
                        float angle = atan2f(target.y, target.x) * 180 / PI;
                        e->setAngle(angle);
                        e->render(e->position.x, e->position.y, NULL, renderer);
                        if (counter > 0)
                        {
                            float rotationShouldHave = leader2Entities[0]->rotation + leader2->avgRotation * counter;
                            if (leader2Entities[counter]->rotation < rotationShouldHave)
                                leader2Entities[counter]->rotation = rotationShouldHave;
                        }
                        if (e->checkIfFireBullet())
                        {
                            Vector2 position = e->center;
                            Bullet* tempBullet = new Bullet(position, e->angle, e->bulletType);
                            tempBullet->loadFromFile(BULLET_DIR + e->bulletType + ".png", renderer);
                            tempBullet->setPosition(position);
                            leader2EntityBullets.push_back(tempBullet);
                        }
                        counter++;
                        it++;
                    }
                    else
                    {
                        leader2->numEntities--;
                        leader2Entities.erase(it);
                        delete e;
                    }
                }

                // Leader 1 Controller
                leader1->updatePosition(elapsedTime);
                leader1->updateAmmunitionCounter(elapsedTime);
                leader1->speedDown(elapsedTime);
                if (KEYS[SDL_SCANCODE_W]) {
                    leader1->updateSpeed(1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_S]) {
                    leader1->updateSpeed(-1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_A])
                {
                    // rotate plane left
                    leader1->updateAngle(-1);
                }
                
                if (KEYS[SDL_SCANCODE_D])
                {
                    // rotate plane right
                    leader1->updateAngle(1);
                }

                if (KEYS[SDL_SCANCODE_LSHIFT] && leader1->numBulletsPerPress > 0)
                {
                    Vector2 position = leader1->center;
                    Bullet* tempBullet = new Bullet(position, leader1->angle, leader1->bulletType + "_" + to_string(leader1->bulletLevel));
                    tempBullet->loadFromFile(BULLET_DIR + leader1->bulletType + "_" + to_string(leader1->bulletLevel) + ".png", renderer);
                    tempBullet->setPosition(position);
                    tempBullet->setInitialSpeed(leader1->speed);
                    tempBullet->setAcceleration(leader1->acceleration);
                    leader1Bullets.push_back(tempBullet);
                    --leader1->numBulletsPerPress;
                }
                
                if (!KEYS[SDL_SCANCODE_LSHIFT])
                {
                    leader1->numBulletsPerPress = leader1->maxNumBulletsPerPress;
                }
                
                if (leader1->ammunitionCounter > leader1->ammunitionThreshold)
                {
                    leader1->halveAmmunition();
                    leader1->ammunitionCounter = 0;
                }
                
                

                // Leader 2 Controller
                leader2->updatePosition(elapsedTime);
                leader2->speedDown(elapsedTime);
                leader2->updateAmmunitionCounter(elapsedTime);
                if (KEYS[SDL_SCANCODE_UP]) {
                    leader2->updateSpeed(1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_DOWN]) {
                    leader2->updateSpeed(-1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_LEFT])
                {
                    // rotate plane left
                    leader2->updateAngle(-1);
                }
                
                if (KEYS[SDL_SCANCODE_RIGHT])
                {
                    // rotate plane right
                    leader2->updateAngle(1);
                }

                if (KEYS[SDL_SCANCODE_SPACE] && leader2->numBulletsPerPress > 0)
                {
                    Vector2 position = leader2->center;
                    Bullet* tempBullet = new Bullet(position, leader2->angle, leader2->bulletType + "_" + to_string(leader2->bulletLevel));
                    tempBullet->loadFromFile(BULLET_DIR + leader2->bulletType + "_" + to_string(leader2->bulletLevel) + ".png", renderer);
                    tempBullet->setPosition(position);
                    tempBullet->setInitialSpeed(leader2->speed);
                    tempBullet->setAcceleration(leader2->acceleration);
                    leader2Bullets.push_back(tempBullet);
                    --leader2->numBulletsPerPress;
                }
                
                if (!KEYS[SDL_SCANCODE_SPACE])
                {
                    leader2->numBulletsPerPress = leader2->maxNumBulletsPerPress;
                }
                
                if (leader2->ammunitionCounter > leader2->ammunitionThreshold)
                {
                    leader2->halveAmmunition();
                    leader2->ammunitionCounter = 0;
                }
                
                // Draw the health bars for both players
                leader1HealthBar->render(leader1HealthBar->position.x, leader1HealthBar->position.y, &leader1HealthBar->rect, renderer);
                leader1HealthBar->updateHealthBarLength(leader1->health/leader1->fullHealth, "left");
                leader2HealthBar->render(leader2HealthBar->position.x + (1 - leader2->health/leader2->fullHealth) * leader2HealthBar->getActualWidth(), leader2HealthBar->position.y, &leader2HealthBar->rect, renderer);
                leader2HealthBar->updateHealthBarLength(leader2->health/leader2->fullHealth, "right");
              
                
                leader1HealthBarFrame->render(leader1HealthBar->position.x, leader1HealthBar->position.y, NULL, renderer);
                leader2HealthBarFrame->render(leader2HealthBar->position.x, leader2HealthBar->position.y, NULL, renderer);
            }
            else
            {
                if (KEYS[SDL_SCANCODE_UP] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.rightmovement(1);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_DOWN] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.rightmovement(-1);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_W] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.leftmovement(1);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_S] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.leftmovement(-1);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_SPACE] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.click(gameOver, 2, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT,CHOOSEPLANE_PATH, INSTRUCTION_PATH,renderer);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_LSHIFT] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.click(gameOver, 1, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT,CHOOSEPLANE_PATH, INSTRUCTION_PATH, renderer);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_A] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.back(ACTUAL_WINDOW_WIDTH,ACTUAL_WINDOW_HEIGHT,INTERFACE_PATH, renderer);
                    notPressed = false;
                }
                else if (KEYS[SDL_SCANCODE_LEFT] && notPressed)
                {
                    pressTick = currentFrameTime;
                    it.back(ACTUAL_WINDOW_WIDTH,ACTUAL_WINDOW_HEIGHT,INTERFACE_PATH, renderer);
                    notPressed = false;
                }
                else if (currentFrameTime - pressTick > 0.2)
                {
                    notPressed = true;
                }
                
                if (it.finishChoosing())
                {
                    
                    Vector2 leader1_init_position = generate_random_position(0, ACTUAL_WINDOW_WIDTH/3, 0, ACTUAL_WINDOW_HEIGHT/2);
                    leader1 = new Leader(leader1_init_position, 0, ACTUAL_WINDOW_WIDTH, 0, ACTUAL_WINDOW_HEIGHT);
                    
                    Vector2 leader2_init_position = generate_random_position(ACTUAL_WINDOW_WIDTH/2, ACTUAL_WINDOW_WIDTH*2/3, 0, ACTUAL_WINDOW_HEIGHT/3);
                    leader2 = new Leader(leader2_init_position, 0, ACTUAL_WINDOW_WIDTH, 0, ACTUAL_WINDOW_HEIGHT);
                    
                    int leftIndex  = it.leftType - 1;
                    int rightIndex = it.rightType - 1;
                    
                    // Set attributes for player 1
                    leader1->setPlaneType(it.leftTypeArray[leftIndex]);
                    leader1->loadFromFile(LEADER_DIR + leader1->planeType + ".png", renderer);
                    
                    leader1->setInitialSpeed(it.initialSpeedArray[rightIndex]);
                    leader1->setMaxSpeed(it.maxSpeedArray[rightIndex]);
                    leader1->setAcceleration(it.accelerationArray[rightIndex]);
                    leader1->setDeacceleration(it.deaccelerationArray[rightIndex]);
                    leader1->setFriction(it.frictionArray[rightIndex]);
                    
                    leader1->setBulletLevel(1);
                    leader1->setBulletType(it.leftBulletArray[leftIndex]);
                    leader1->setMaxNumBulletsPerPress(it.powerArray[rightIndex]);
                    
                    leader1->setFullHealth(it.healthArray[rightIndex]);
                    leader1->setAngle(0);
                    leader1->setMaxEntityNumber(10);
                    leader1->setAmmunitionThreshold(10);
                    
                    // Set attributes for player 2
                    leader2->setPlaneType(it.rightTypeArray[rightIndex]);
                    leader2->loadFromFile(LEADER_DIR + leader2->planeType + ".png", renderer);

                    leader2->setInitialSpeed(it.initialSpeedArray[rightIndex]);
                    leader2->setMaxSpeed(it.maxSpeedArray[rightIndex]);
                    leader2->setAcceleration(it.accelerationArray[rightIndex]);
                    leader2->setDeacceleration(it.deaccelerationArray[rightIndex]);
                    leader2->setFriction(it.frictionArray[rightIndex]);

                    leader2->setBulletLevel(1);
                    leader2->setBulletType(it.rightBulletArray[rightIndex]);
                    leader2->setMaxNumBulletsPerPress(it.powerArray[rightIndex]);

                    leader2->setFullHealth(it.healthArray[rightIndex]);
                    leader2->setAngle(180);
                    leader2->setMaxEntityNumber(10);
                    leader2->setAmmunitionThreshold(10);
                }
                
                
                it.render(it.position.x, it.position.y, NULL, renderer);
                it.updateLine(elapsedTime, renderer);
            }
            SDL_RenderPresent(renderer);
        }
    
    }
    
    return 0;
}




bool init()
{
    // Initialization flag
    bool success = true;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        
        // Create window
        window = SDL_CreateWindow("Spaceship Battle Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window != NULL)
        {
            // Create an OpenGL context for use with an OpenGL window
            SDL_GLContext context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, context);
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    // Create vsynced renderer for window
            if (renderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            ACTUAL_WINDOW_WIDTH  = WINDOW_WIDTH;
            ACTUAL_WINDOW_HEIGHT = WINDOW_HEIGHT;
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_DisplayMode display_mode;
            SDL_GetCurrentDisplayMode(0, &display_mode);
            ACTUAL_WINDOW_WIDTH = display_mode.w;
            ACTUAL_WINDOW_HEIGHT = display_mode.h;
        }
        else
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
    }
    return success;
}



void close()
{
    
    for (Entity* e : leader1Entities)
    {
        delete e;
        e = nullptr;
    }
    
    for (Entity* e : leader2Entities)
    {
        delete e;
        e = nullptr;
    }
    
    for (Bullet* b : leader1Bullets)
    {
        delete b;
        b = nullptr;
    }
    
    for (Bullet* b : leader1EntityBullets)
    {
        delete b;
        b = nullptr;
    }
    
    for (Bullet* b : leader2EntityBullets)
    {
        delete b;
        b = nullptr;
    }
    
    for (BonusEntity* b :bonus_entity_objects)
    {
        delete b;
        b = nullptr;
    }
    
    for (BonusBulletEnhance* b : bonus_bullet_enhance_objects)
    {
        delete b;
        b = nullptr;
    }
    
    for (BonusBulletAmmunition* b : bonus_bullet_ammunition_objects)
    {
        delete b;
        b = nullptr;
    }
    
    for (Gravity* g : gravity_objects)
    {
        delete g;
        g = nullptr;
    }
    
    delete leader1;
    delete leader2;
    delete leader1HealthBar;
    delete leader2HealthBar;
    delete leader1HealthBarFrame;
    delete leader2HealthBarFrame;

    
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window =  nullptr;
    renderer = nullptr;
    
    // Quit SDL environment
    IMG_Quit();
    SDL_Quit();

}

void enable2D(int width, int height)
{
    // Set the viewport within the window in pixels
    glViewport(0, 0, width, height);
    
    // Specify which matrix stack is the target for subsequent matrix operations
    // GL_PROJECTION matrix defines the properties of camera that views the objects in the
    // world coordinate frame, which typically include the zoom factor, aspect ratio,
    // and the near and far clipping planes
    glMatrixMode(GL_PROJECTION);
    
    // Replace the current matrix with the identity matrix
    glLoadIdentity();
    
    // Multiply the current matrix (M) by an orthographic matrix (O),
    // so M is replaced by M • O
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    
    // GL_MODELVIEW matrix defines how objects are transformed, which typically
    // include translation, rotation and scaling in the world coordinate frame
    glMatrixMode(GL_MODELVIEW);
    
    // Load the identity matrix as the current matrix
    glLoadIdentity();
    
    // Clear buffer data
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Specify clear values for the color buffers
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void draw_rect(int x, int y, int width, int height)
{
    
    SDL_Rect rect = {  x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}


Vector2 generate_random_position(float xMin, float xMax, float yMin, float yMax)
{
    srand((unsigned int)clock());
    float x = xMin + ((float) rand() / (float) RAND_MAX) * (xMax - xMin);
    float y = yMin + ((float) rand() / (float) RAND_MAX) * (yMax - yMin);
    return Vector2(x, y);
}

