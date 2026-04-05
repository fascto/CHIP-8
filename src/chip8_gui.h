//
// Created by tdela on 5/4/2026.
//

#ifndef CHIP_8_CHIP8_GUI_H
#define CHIP_8_CHIP8_GUI_H
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "chip8.h"

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

class Chip8Gui {

private:
    Chip8* chip8{};

    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};
    SDL_Texture *gTexture{nullptr};

    uint32_t kScreenWidth = 640;
    uint32_t kScreenHeight = 480;

public:

    Chip8Gui(Chip8* chip8);

    ~Chip8Gui();

    Chip8Gui(const Chip8Gui &) = delete;
    Chip8Gui &operator=(const Chip8Gui &) = delete;

    bool init();
    void update();
    bool processInput(const SDL_Event &e) const;
    void render() const;
    void close();

};

#endif //CHIP_8_CHIP8_GUI_H