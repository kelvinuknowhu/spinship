//
//  LTexture.cpp
//  SpaceInvader
//
//  Created by Siyuan Hu on 10/14/16.
//  Copyright © 2016 Siyuan Hu. All rights reserved.
//

#include "LTexture.hpp"


LTexture::LTexture(int nframes)
{
    this->texture = NULL;
    this->textureWidth = 0;
    this->textureHeight = 0;
    this->actualWidth = 0;
    this->actualHeight = 0;
    this->nframes = nframes;
    this->angle = 0;
}

LTexture::~LTexture()
{
    free();
}


bool LTexture::loadFromFile(std::string pathEntity, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(pathEntity.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", pathEntity.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL_image Error: %s\n", pathEntity.c_str(), IMG_GetError());
        }
        else
        {
            // Get image dimensions
            this->textureWidth  = loadedSurface->w;
            this->textureHeight = loadedSurface->h;
            this->actualWidth = textureWidth;
            this->actualHeight = textureHeight;
        }
        // Get rid of loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    this->texture = newTexture;
    return (texture != NULL);
}


void LTexture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate the exisiting texture rgb
    // More specifically, the function set an additional color value
    // multiplied into render copy operations
    SDL_SetTextureColorMod(texture, red, green, blue);

}


void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(texture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer, SDL_Point* center, SDL_RendererFlip flip)
{
    assert(actualWidth  > 0);
    assert(actualHeight > 0);
    
    // Set rendering space, by default pass in texture width and height
    SDL_Rect renderQuad = { x, y, this->actualWidth, this->actualHeight };

    
    // Set clip dimensions of rendering if there is a clip
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    assert(renderer != NULL);
    assert(texture != NULL);

    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, this->angle, center, flip);
}

int LTexture::getTextureWidth()
{
    return textureWidth;
}

int LTexture::getTextureHeight()
{
    return textureHeight;
}

int LTexture::getActualWidth()
{
    return actualWidth;
}

int LTexture::getActualHeight()
{
    return actualHeight;
}

void LTexture::setActualWidth(int _width)
{
    actualWidth = _width;
}

void LTexture::setActualHeight(int _height)
{
    actualHeight = _height;
}

SDL_Texture* LTexture::getTexture()
{
    return texture;
}

int LTexture::getFrames()
{
    return nframes;
}





