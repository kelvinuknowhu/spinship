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
#include <SDL2_image/SDL_image.h>



class LTexture {
    
private:
    SDL_Texture* texture;
    int textureWidth;
    int textureHeight;
    int actualWidth;
    int actualHeight;
    int nframes;
    
public:
    float angle;

    LTexture(int nframes);
    ~LTexture();
    void free();
    bool loadFromFile(std::string pathEntity, SDL_Renderer* renderer);
    void render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);

    int getTextureWidth()
    {
        return textureWidth;
    }
    
    int getTextureHeight()
    {
        return textureHeight;
    }
    
    int getActualWidth()
    {
        return actualWidth;
    }
    
    int getActualHeight()
    {
        return actualHeight;
    }
    
    void setActualWidth(int _width)
    {
        actualWidth = _width;
    }
    
    void setActualHeight(int _height)
    {
        actualHeight = _height;
    }
    
    SDL_Texture* getTexture()
    {
        return texture;
    }
    
    int getFrames()
    {
        return nframes;
    }

};




#endif /* LTexture_h */
