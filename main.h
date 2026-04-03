//
// Created by tdela on 3/4/2026.
//

#ifndef CHIP_8_MAIN_H
#define CHIP_8_MAIN_H

#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>


class LTexture {
public:
    LTexture();

    ~LTexture();

    bool loadFromFile( const std::string& path );

    void destroy();

    void render( float x, float y );

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] bool isLoaded() const;

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

#endif //CHIP_8_MAIN_H