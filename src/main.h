//
// Created by tdela on 3/4/2026.
//

#ifndef CHIP_8_MAIN_H
#define CHIP_8_MAIN_H


#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


constexpr uint16_t FPS = 60;
constexpr uint16_t THRESHOLD = 1 / FPS;

// Modern CHIP8 keymap - SDL Keys
constexpr uint8_t keymap[16] = {
    SDLK_X,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_Q,
    SDLK_W,
    SDLK_E,
    SDLK_A,
    SDLK_S,
    SDLK_D,
    SDLK_Z,
    SDLK_C,
    SDLK_4,
    SDLK_R,
    SDLK_F,
    SDLK_V,
};

bool init();

void processInput();

void update();

void render();

void close();

class main {
};


#endif //CHIP_8_MAIN_H