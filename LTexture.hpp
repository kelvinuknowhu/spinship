//
//  LTexture.h
//  SpaceInvader
//
//  Created by Siyuan Hu on 10/14/16.
//  Copyright © 2016 Siyuan Hu. All rights reserved.
//

#ifndef LTexture_h
#define LTexture_h

#include <string>
#include <assert.h>
#include <iostream>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>



class LTexture {
public:
    
    float angle;
    
    LTexture(int nframes);
    ~LTexture();
    
    bool loadFromFile(std::string pathEntity, SDL_Renderer* renderer);
    
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    
    void render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer, int endWidth = 0, int endHeight = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getTextureWidth()
    {
        return entityTextureWidth;
    }
    int getTextureHeight()
    {
        return entityTextureHeight;
    }
    
    SDL_Texture* getTexture()
    {
        return entityTexture;
    }
    
    int getFrames()
    {
        return nframes;
    }
private:
    SDL_Texture* entityTexture;
    int entityTextureWidth;
    int entityTextureHeight;
    int nframes;
};



LTexture::LTexture(int nframes)
{
    this->entityTexture = NULL;
    this->entityTextureWidth = 0;
    this->entityTextureHeight = 0;
    this->nframes = nframes;
    this->angle = 0;
}

LTexture::~LTexture()
{
    free();
}


bool LTexture::loadFromFile(std::string pathEntity, SDL_Renderer* renderer)
{
    SDL_Texture* newTextureEntity = NULL;

    
    // Load image at specified path
    SDL_Surface* loadedSurfaceEntity = IMG_Load(pathEntity.c_str());
    if (loadedSurfaceEntity == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", pathEntity.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurfaceEntity, SDL_TRUE, SDL_MapRGB(loadedSurfaceEntity->format, 0xFF, 0xFF, 0xFF));
        
        // Create texture from surface pixels
        newTextureEntity = SDL_CreateTextureFromSurface(renderer, loadedSurfaceEntity);
        if (newTextureEntity == NULL) {
            printf("Unable to create texture from %s! SDL_image Error: %s\n", pathEntity.c_str(), IMG_GetError());
        } else {
            // Get image dimensions
            this->entityTextureWidth  = loadedSurfaceEntity->w;
            this->entityTextureHeight = loadedSurfaceEntity->h;
        }
        // Get rid of loaded surface
        SDL_FreeSurface(loadedSurfaceEntity);
    }
    this->entityTexture = newTextureEntity;
    return (entityTexture != NULL);
}


void LTexture::free()
{
    if (entityTexture != NULL)
    {
        SDL_DestroyTexture(entityTexture);
        entityTexture = NULL;
    }

}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate the exisiting texture rgb
    // More specifically, the function set an additional color value
    // multiplied into render copy operations
    SDL_SetTextureColorMod(entityTexture, red, green, blue);

}


void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(entityTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(entityTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer, int endWidth, int endHeight, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space, by default pass in texture width and height
    if (endWidth == 0 && endHeight == 0){
        SDL_Rect entityRenderQuad = {x, y, this->entityTextureWidth, this->entityTextureHeight};
        if (clip != NULL) {
            entityRenderQuad.w = clip->w;
        }
        
        assert(renderer != NULL);
        assert(entityTexture != NULL);

        // SDL_RenderCopy(renderer, texture, clip, &renderQuad);
        SDL_RenderCopyEx(renderer, entityTexture, clip, &entityRenderQuad, this->angle, center, flip);
    }else{
        SDL_Rect entityRenderQuad = {x, y, endWidth, endHeight};
        if (clip != NULL) {
            entityRenderQuad.w = clip->w;
        }
        
        assert(renderer != NULL);
        assert(entityTexture != NULL);

        // SDL_RenderCopy(renderer, texture, clip, &renderQuad);
        SDL_RenderCopyEx(renderer, entityTexture, clip, &entityRenderQuad, this->angle, center, flip);
    }
    
    // Set clip dimensions of rendering if there is a clip
    
}





#endif /* LTexture_h */
