//
// Created by tdela on 5/4/2026.
//

#ifndef CHIP_8_CHIP8_GUI_H
#define CHIP_8_CHIP8_GUI_H
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

class Chip8Gui {

private:

    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    SDL_Texture *gTexture;

    uint32_t kScreenWidth = 640;
    uint32_t kScreenHeight = 480;

public:

    Chip8Gui();
    ~Chip8Gui();

    Chip8Gui(const Chip8Gui &) = delete;
    Chip8Gui &operator=(const Chip8Gui &) = delete;

    bool init();
    void update();
    void processInput();
    void render();
    void close();

};

#endif //CHIP_8_CHIP8_GUI_H