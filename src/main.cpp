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
 |    Description:
 |
 *===========================================================================*/


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "Leader.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "BonusEntity.hpp"


#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
int ACTUAL_WINDOW_WIDTH = 0;
int ACTUAL_WINDOW_HEIGHT = 0;

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

const string BASE_DIRECTORY = "/Users/Kelvin/Desktop/Game_Programming/SpaceshipBattleGame/";
const string LEADER_DIR = BASE_DIRECTORY + "img/battle-plane/";
const string ENTITY_DIR = BASE_DIRECTORY + "img/entity-plane/";
const string BULLET_DIR  = BASE_DIRECTORY + "img/laser-bullet/";
const string BONUS_ENTITY_DIR = BASE_DIRECTORY + "img/entity-plane/";
const string BACKGROUND_PATH = BASE_DIRECTORY + "img/background/purple.png";

Leader* leader1;
Leader* leader2;


vector<Entity*> leader1Entities;
vector<Entity*> leader2Entities;

vector<Bullet*> leader1Bullets;
vector<Bullet*> leader2Bullets;

vector<BonusEntity*> bonus_entity_objects;


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
        Vector2 leader1_init_position = generate_random_position(ACTUAL_WINDOW_WIDTH/2, ACTUAL_WINDOW_WIDTH/3, ACTUAL_WINDOW_HEIGHT/2, ACTUAL_WINDOW_HEIGHT*2/3);
        leader1 = new Leader(leader1_init_position, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT);
        leader1->setPlaneType("playerShip1_red");
        leader1->setBulletType("laserRed");
        leader1->setBulletLevel("_1");
        leader1->loadFromFile(LEADER_DIR + leader1->planeType + ".png", renderer);
        leader1->setInitialSpeed(100);
        leader1->setMaxSpeed(750);
        leader1->setAngle(0);
        leader1->setAcceleration(200);
        leader1->setDeacceleration(600);
        leader1->setFriction(0);
        leader1->setMaxEntityNumber(10);
        leader1->setMaxNumBulletsPerPress(15);
        

        Vector2 leader2_init_position = generate_random_position(ACTUAL_WINDOW_WIDTH/3, ACTUAL_WINDOW_WIDTH/2, 0, ACTUAL_WINDOW_HEIGHT/3);
        leader2 = new Leader(leader2_init_position, WINDOW_WIDTH, WINDOW_HEIGHT);
        leader2->setPlaneType("playerShip3_green");
        leader2->setBulletType("laserGreen");
        leader2->setBulletLevel("_1");
        leader2->loadFromFile(LEADER_DIR + leader2->planeType + ".png", renderer);
        leader2->setInitialSpeed(100);
        leader2->setMaxSpeed(500);
        leader2->setAngle(180);
        leader2->setAcceleration(100);
        leader2->setDeacceleration(300);
        leader2->setFriction(0);
        leader2->setMaxEntityNumber(10);
        leader2->setMaxNumBulletsPerPress(10);

        
        LTexture background(1);
        background.loadFromFile(BACKGROUND_PATH, renderer);

        
        BonusEntity::setGlobalThreshold(1);
        BonusEntity::setMaxNumObjects(1);
        
        
        float currentFrameTime = 0;
        float previousFrameTime = 0;
        float elapsedTime = 0;

        SDL_Event event;
        bool done = false;
        bool gameOver = false;
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
                    tempBonusEntity->loadFromFile(BONUS_ENTITY_DIR + BonusEntity::bonusFileArray[index], renderer);
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
                            Entity* tempEntity = new Entity(init_position, WINDOW_WIDTH, WINDOW_HEIGHT);
                            tempEntity->loadFromFile(ENTITY_DIR + BonusEntity::entityFileMap[color], renderer);
                            tempEntity->setThreshold(30);
                            tempEntity->setActualWidth(60);
                            tempEntity->setActualHeight(60);
                            tempEntity->setSpeed(1);
                            leader1Entities.push_back(tempEntity);
                            leader1->numEntities++;
                        }
                        bonus_entity_objects.erase(it);
                        delete b;
                        
                    }
                    else if (b->detectCollision(leader2->position.x, leader2->position.y, leader2->getActualWidth(), leader2->getActualHeight()))
                    {
                        bonus_entity_objects.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updateAngle();
                        ++it;
                    }
                }
                
                
                
                for (vector<Bullet*>::iterator it = leader1Bullets.begin(); it != leader1Bullets.end();)
                {
                    Bullet* b = *it;
                    if (b->offScreen(WINDOW_WIDTH, WINDOW_HEIGHT))
                    {
                        leader1Bullets.erase(it);
                        delete b;
                    }
                    else if (leader2->detectCollision(b->position.x, b->position.y, b->getActualWidth(), b->getActualHeight()))
                    {
                        leader1Bullets.erase(it);
                        delete b;
                    }
                    else
                    {
                        b->render(b->position.x, b->position.y, NULL, renderer);
                        b->updatePosition(elapsedTime);
                        ++it;
                    }
                }
                
                // Draw the first player
                leader1->render(leader1->position.x, leader1->position.y, NULL, renderer);
                leader1->updateCenter();
                leader1->updateAvgRotation();
                
                
                // Draw the second player
                leader2->render(leader2->position.x, leader2->position.y, NULL, renderer);
                leader2->updateCenter();

                
                // Update position for each entity
                int counter = 0;
                for (vector<Entity*>::iterator it = leader1Entities.begin(); it != leader1Entities.end();)
                {
                    Entity* e = *it;
                    if (!e->checkIfCounterDone())
                    {
                        e->updateCenter();
                        e->updateCounter(elapsedTime);
                        e->render(e->position.x, e->position.y, NULL, renderer);
                        Vector2 target = leader2->center - e->position;
                        float angle = atan2f(target.y, target.x) * 180 / PI;
                        e->setAngle(angle);
                        e->updateTargetPosition(leader1);
                        if (counter > 0)
                        {
                            float rotationShouldHave = leader1Entities[0]->rotation + leader1->avgRotation * counter;
                            if (leader1Entities[counter]->rotation < rotationShouldHave)
                            {
                                leader1Entities[counter]->rotation = rotationShouldHave;
                            }
                        }
                        e->updatePosition(leader1);
                        ++counter;
                        ++it;
                    }
                    else
                    {
                        leader1Entities.erase(it);
                        delete e;
                    }
                }
                
                for (Entity* e : leader2Entities)
                {
                    e->updateCenter();
                    e->render(e->position.x, e->position.y, NULL, renderer);
                    Vector2 target = leader1->center - e->position;
                    float angle = atan2f(target.y, target.x) * 180 / PI;
                    e->setAngle(angle);
                    e->updateTargetPosition(leader2);
                    e->updatePosition(leader2);
                }
            
                leader1->updatePosition(elapsedTime);
                
                // Leader 1 Controller
                if (KEYS[SDL_SCANCODE_UP]) {
                    leader1->updateSpeed(1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_DOWN]) {
                    leader1->updateSpeed(-1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_LEFT])
                {   // rotate plane left
                    leader1->updateAngle(-1);
                }
                
                if (KEYS[SDL_SCANCODE_RIGHT])
                {   // rotate plane right
                    leader1->updateAngle(1);
                }
                

                if (KEYS[SDL_SCANCODE_SPACE] && leader1->numBulletsPerPress > 0)
                {
                    Vector2 position = leader1->center;
                    Bullet* tempBullet = new Bullet(position, leader1->angle);
                    tempBullet->loadFromFile(BULLET_DIR + leader1->bulletType + leader1->bulletLevel + ".png", renderer);
                    tempBullet->setPosition(position);
                    leader1Bullets.push_back(tempBullet);
                    --leader1->numBulletsPerPress;
                }
                
                if (!KEYS[SDL_SCANCODE_SPACE])
                {
                    leader1->numBulletsPerPress = leader1->maxNumBulletsPerPress;
                }
                
                
                
                
                leader2->updatePosition(elapsedTime);

                // Leader 2 Controller
                if (KEYS[SDL_SCANCODE_W]) {
                    leader2->updateSpeed(1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_S]) {
                    leader2->updateSpeed(-1, elapsedTime);
                }
                
                if (KEYS[SDL_SCANCODE_A])
                {   // rotate plane right
                    leader2->updateAngle(1);
                }
                
                if (KEYS[SDL_SCANCODE_D])
                {   // rotate plane right
                    leader2->updateAngle(-1);
                }
                
              
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
//            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_DisplayMode display_mode;
            SDL_GetCurrentDisplayMode(0, &display_mode);
            ACTUAL_WINDOW_WIDTH = display_mode.w;
            ACTUAL_WINDOW_HEIGHT = display_mode.h;
            cout << ACTUAL_WINDOW_WIDTH << ", " << ACTUAL_WINDOW_HEIGHT << endl;
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
    
    delete leader1;
    leader1 = NULL;
    
    for (Entity* e : leader1Entities)
    {
        delete e;
        e = NULL;
    }
    
    delete leader2;
    leader2 = NULL;
    
    for (Entity* e : leader2Entities)
    {
        delete e;
        e = NULL;
    }
    
    for (Bullet* b : leader1Bullets)
    {
        delete b;
        b = NULL;
    }
    
    for (BonusEntity* b :bonus_entity_objects)
    {
        delete b;
        b = NULL;
    }
    
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    
    // Quit SDL environment
    IMG_Quit();
    SDL_Quit();

}

void enable2D(int width, int height) {
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

