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

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 720

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const Uint8* KEYS = SDL_GetKeyboardState(NULL);

const string LEADER_PATH = "/Users/Kelvin/Desktop/Game_Programming/Flocking\ Spaceships/Flocking\ Spaceships/img/leader-in-area.png";
const string ENEMY_PATH = "/Users/Kelvin/Desktop/Game_Programming/Flocking\ Spaceships/Flocking\ Spaceships/img/enemy-in-area.png";

const int LEADER_ANIMATION_FRAMES = 1;
SDL_Rect leaderClips[LEADER_ANIMATION_FRAMES];
Leader* leader1;
Leader* leader2;


const string LEADER_ENTITY_PATH = "/Users/Kelvin/Desktop/Game_Programming/Flocking\ Spaceships/Flocking\ Spaceships/img/enemy-entity.png";
const string ENEMY_ENTITY_PATH = "/Users/Kelvin/Desktop/Game_Programming/Flocking\ Spaceships/Flocking\ Spaceships/img/enemy-entity.png";

const int LEADER_ENTITY_ANIMATION_FRAMES = 1;
SDL_Rect leaderEntityClips[LEADER_ENTITY_ANIMATION_FRAMES];
vector<Entity*> leader1Entities;
vector<Entity*> leader2Entities;



bool init();
bool loadMedia();
void enable2D(int width, int height);

int main(int argc, const char * argv[]) {
    
    
    Vector2 leader1_init_position = Vector2(200, WINDOW_HEIGHT/2);
    Vector2 leader2_init_position = Vector2(600, WINDOW_HEIGHT/2);

    leader1 = new Leader(leader1_init_position, 1.0, 0, 1.0, 150, 50, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    leader2 = new Leader(leader2_init_position, 1.0, 0, 1.0, 150, 50, 1, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (int i = 0; i < 10; i++) {
        Vector2 init_position = Vector2(100, 100+50*i);
        leader1Entities.push_back(new Entity(init_position, 1.0, 2.0, 0.0, 1, WINDOW_WIDTH, WINDOW_HEIGHT));
    }
    
    for (int i = 0; i < 10; i++) {
        Vector2 init_position = Vector2(700, 100+50*i);
        leader2Entities.push_back(new Entity(init_position, 1.0, 2.0, 0.0, 1, WINDOW_WIDTH, WINDOW_HEIGHT));
    }

    
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        
        enable2D(WINDOW_WIDTH, WINDOW_HEIGHT);

        if (!loadMedia()) {
            printf("Failed to load media\n");
        } else {
            
            
            bool done = false;
            SDL_Event event;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float lastFrameTicks = 0.0f;

            
            
            bool gameOver = false;
//            bool gameWin = false;
            while (!done) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                        done = true;
                    }
                    
                }
                
                if (!gameOver) {
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                    SDL_RenderClear(renderer);
                
                
                    leader1->render(leader1->position.x, leader1->position.y, NULL);
                    leader2->render(leader2->position.x, leader2->position.y, NULL);


                    float ticks = (float) SDL_GetTicks() / 1000.0f;
                    float elapsed = ticks - lastFrameTicks;
                    lastFrameTicks = ticks;
                    
                    for (Entity* e : leader1Entities) {
                        e->render(e->position.x, e->position.y, NULL);
                        e->setAngle(leader1->angle);
                        Vector2 sep = e->separateEntites(leader1Entities);
                        e->applyForce(sep);
                        e->updatePosition(elapsed, leader1);

                    }
                    
                    for (Entity* e : leader2Entities) {
                        e->render(e->position.x, e->position.y, NULL);
                        e->setAngle(leader2->angle);
                        Vector2 sep = e->separateEntites(leader2Entities);
                        e->applyForce(sep);
                        e->updatePosition(elapsed, leader2);
                        
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
        window = SDL_CreateWindow("Flocking Spaceships", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window != NULL) {
            // Create an OpenGL context for use with an OpenGL window
            SDL_GLContext context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, context);
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    // Create vsynced renderer for window
            if (renderer != NULL) {
                leader1->setRenderer(renderer);
                leader2->setRenderer(renderer);

                for (Entity* e : leader1Entities) {
                    e->setRenderer(renderer);
                }
                for (Entity* e : leader2Entities) {
                    e->setRenderer(renderer);
                }
                
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //Initialize renderer color
                
            } else {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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
    if (!leader1->loadFromFile(LEADER_PATH)) {
        IMGloaded = false;
    }
    
    if (!leader2->loadFromFile(ENEMY_PATH)) {
        IMGloaded = false;
    }
    
    for (Entity* e : leader1Entities) {
        if (!e->loadFromFile(LEADER_ENTITY_PATH)) {
            IMGloaded = false;
        }
    }
    
    for (Entity* e : leader2Entities) {
        if (!e->loadFromFile(ENEMY_ENTITY_PATH)) {
            IMGloaded = false;
        }
    }
    
    
    if (!IMGloaded) {
        printf("Failed to load walking sprite texture!\n");
        success = false;
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


