/*=============================================================================
 |   Assignment:  1/2 Way Deliverable
 |
 |       Author:  Siyuan Hu (Kelvin)
 |     Language:  C++11
 |       To Run:  Build in Xcode with essential frameworks added to Build Phases
 |
 |        Class:  Introduction to Game Programming
 |   Instructor:  John Sterling
 |     Due Date:  Nov 11, 2016 11:55 pm
 |
 +-----------------------------------------------------------------------------
 |  Description:
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

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

const string BASE_DIRECTORY = "/Users/Kelvin/Desktop/Game_Programming/SpaceshipBattleGame/";
const string LEADER_PATH = BASE_DIRECTORY + "img/minimalistic-plane/leader-in-area.png";
const string ENEMY_PATH = BASE_DIRECTORY + "img/minimalistic-plane/enemy-in-area.png";
const string LEADER_ENTITY_PATH = BASE_DIRECTORY + "img/minimalistic-plane/leader-entity.png";
const string ENEMY_ENTITY_PATH = BASE_DIRECTORY + "img/minimalistic-plane/enemy-entity.png";
const string BULLET_PATH  = BASE_DIRECTORY + "img/minimalistic-plane/bullet.png";


const int LEADER_ANIMATION_FRAMES = 1;
SDL_Rect leaderClips[LEADER_ANIMATION_FRAMES];
Leader* leader1;
Leader* leader2;




const int LEADER_ENTITY_ANIMATION_FRAMES = 1;
const int ENTITY_MAX_NUM = 5;
SDL_Rect leaderEntityClips[LEADER_ENTITY_ANIMATION_FRAMES];
vector<Entity*> leader1Entities;
vector<Entity*> leader2Entities;



const int BULLET_WIDTH  = 36;
const int BULLET_HEIGHT = 70;
const int BULLET_ANIMATION_FRAMES = 4;
SDL_Rect bulletClips[BULLET_ANIMATION_FRAMES];
vector<Bullet*> bullets;


bool init();
bool loadMedia();
void enable2D(int width, int height);
void draw_rect(int x, int y, int width, int height);


int main(int argc, const char * argv[]) {
    
    
    Vector2 leader1_init_position = Vector2(200, WINDOW_HEIGHT/2 - 125);
    Vector2 leader2_init_position = Vector2(800, WINDOW_HEIGHT/2 - 125);
    
    const int MAX_NUM_ENTITIES = 10;
    leader1 = new Leader(leader1_init_position, 1.0, 0, 150, 50, MAX_NUM_ENTITIES, LEADER_ENTITY_ANIMATION_FRAMES, WINDOW_WIDTH, WINDOW_HEIGHT);
    leader2 = new Leader(leader2_init_position, 1.0, 180, 150, 50, MAX_NUM_ENTITIES, LEADER_ENTITY_ANIMATION_FRAMES, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (int i = 0; i < ENTITY_MAX_NUM; i++) {
        Vector2 init_position = Vector2(100, 100 + 50*i);
        float speed = 1.0;
        float max_speed = 5.0;
        float rotation = 360 * i / ENTITY_MAX_NUM;
        leader1Entities.push_back(new Entity(init_position, speed, max_speed, 1, rotation, WINDOW_WIDTH, WINDOW_HEIGHT));
    }
    
    for (int i = 0; i < ENTITY_MAX_NUM; i++) {
        float speed = 1.0;
        float max_speed = 5.0;
        float rotation = 360 * i / ENTITY_MAX_NUM;
        Vector2 init_position = Vector2(700, 100 + 50*i);
        leader2Entities.push_back(new Entity(init_position, speed, max_speed, 1, rotation, WINDOW_WIDTH, WINDOW_HEIGHT));
    }

    
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        
        if (!loadMedia()) {
            printf("Failed to load media\n");
        } else {
            
            
            bool done = false;
            SDL_Event event;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int NUM_BULLETS_LIMIT = 1;
            float previousFrameTime = 0;

            bool gameOver = false;
            while (!done) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                        done = true;
                    }
                    
                }
                
                float currentTime = (float) SDL_GetTicks() / 1000.0f;
                previousFrameTime = currentTime;
                
                
                if (!gameOver) {
                    
                    // Draw the background
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                    SDL_RenderClear(renderer);
                    
                    // Draw the first player
                    leader1->render(leader1->position.x, leader1->position.y, NULL, renderer);
                    leader1->updateCenter();
//                    draw_rect((int)leader1->center.x, (int)leader1->center.y, 5, 5);
                    
                    
                    // Draw the second player
                    leader2->render(leader2->position.x, leader2->position.y, NULL, renderer);
                    leader2->updateCenter();
//                    draw_rect((int)leader2->center.x, (int)leader2->center.y, 5, 5);

                    
                    // Update position for each entity
                    for (Entity* e : leader1Entities) {
                        e->updateCenter();
                        e->render(e->position.x, e->position.y, NULL, renderer);
                        e->setAngle(leader1->angle);
                        e->updateTargetPosition(leader1);
                        e->updatePosition(leader1);
                    }
                    
                    for (Entity* e : leader2Entities) {
                        e->updateCenter();
                        e->render(e->position.x, e->position.y, NULL, renderer);
                        e->setAngle(leader2->angle);
                        e->updateTargetPosition(leader2);
                        e->updatePosition(leader2);
                    }
                
                    
                    // Leader 1 Controller
                    if (KEYS[SDL_SCANCODE_UP]) {
                        leader1->updatePosition(1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_DOWN]) {
                        leader1->updatePosition(-1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_LEFT])
                    {   // rotate plane right
                        leader1->updateAngle(1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_RIGHT])
                    {   // rotate plane right
                        leader1->updateAngle(-1);
                    }
                    
                    
                    SDL_PollEvent(&event);
                    if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYUP && NUM_BULLETS_LIMIT > 0) {
                        
                        Vector2 position = leader1->center;
                        Bullet* tempBullet = new Bullet(position, leader1->angle, BULLET_ANIMATION_FRAMES);
                        tempBullet->loadFromFile(BULLET_PATH, renderer);
                        bullets.push_back(tempBullet);
                        --NUM_BULLETS_LIMIT;
                    }
                    
                    if (event.key.keysym.sym != SDLK_SPACE)
                        NUM_BULLETS_LIMIT = 1;
                    
                    
                    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();) {
                        Bullet* b = *it;
                        if (b->offScreen(WINDOW_WIDTH, WINDOW_HEIGHT)) {
                            bullets.erase(it);
                            delete b;
                        }
                        else {
                            SDL_Rect* currentClip = &bulletClips[b->currentFrame];
                            b->render(b->position.x, b->position.y, currentClip, renderer);
                            b->updatePosition();
                            ++it;
                        }
                    }
                    
                    
                    // Leader 2 Controller
                    if (KEYS[SDL_SCANCODE_W]) {
                        leader2->updatePosition(1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_S]) {
                        leader2->updatePosition(-1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_A])
                    {   // rotate plane right
                        leader2->updateAngle(1);
                    }
                    
                    if (KEYS[SDL_SCANCODE_D])
                    {   // rotate plane right
                        leader2->updateAngle(-1);
                    }
                    
                  
                } else {
                    
                }
                
                SDL_RenderPresent(renderer);
                for (Bullet* b : bullets) {
                    if (currentTime - b->lastFrameTime > 0.1) {
                        b->lastFrameTime = currentTime;
                        b->currentFrame++;
                    
                        if (b->currentFrame >= BULLET_ANIMATION_FRAMES)
                            b->currentFrame = 0;
                    }
                }
                
            
               
            }
        
        }
    
    }
    
    return 0;
}




bool init()
{
    // Initialization flag
    bool success = true;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        
        // Create window
        window = SDL_CreateWindow("Spaceship Battle Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window != NULL) {
            // Create an OpenGL context for use with an OpenGL window
            SDL_GLContext context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, context);
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    // Create vsynced renderer for window
            if (renderer == NULL) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
        } else {
            
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
            
        }
    }
    return success;
}


bool loadMedia()
{
    // Loading success flag
    bool success = true;
    
    
    bool IMGloaded = true;
    if (!leader1->loadFromFile(LEADER_PATH, renderer)) {
        IMGloaded = false;
    }
    
    if (!leader2->loadFromFile(ENEMY_PATH, renderer)) {
        IMGloaded = false;
    }
    
    for (Entity* e : leader1Entities) {
        if (!e->loadFromFile(LEADER_ENTITY_PATH, renderer)) {
            IMGloaded = false;
        }
    }
    
    for (Entity* e : leader2Entities) {
        if (!e->loadFromFile(ENEMY_ENTITY_PATH, renderer)) {
            IMGloaded = false;
        }
    }
    
    
    if (!IMGloaded) {
        printf("Failed to load walking sprite texture!\n");
        success = false;
    }
    
    
    if (success) {
        // Set rectangle dimensions for each bullet animation clip
        for (int i = 0; i < BULLET_ANIMATION_FRAMES; i++) {
            SDL_Rect* r = &bulletClips[i];
            r->x = i * BULLET_WIDTH;
            r->y = 0;
            r->w = BULLET_WIDTH;
            r->h = BULLET_HEIGHT;
        }
    }
    

    return success;
}

void close() {
    
    delete leader1;
    leader1 = NULL;
    
    for (Entity* e : leader1Entities) {
        delete e;
        e = NULL;
    }
    
    delete leader2;
    leader2 = NULL;
    
    for (Entity* e : leader2Entities) {
        delete e;
        e = NULL;
    }
    
    for (Bullet* b : bullets) {
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
    
    // Specify clear values for the color buffers
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void draw_rect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 75);
    SDL_Rect rect = {  x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

