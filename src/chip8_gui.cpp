//
// Created by tdela on 5/4/2026.
//

#include "chip8_gui.h"

#include "../vendored/SDL/src/render/SDL_sysrender.h"

Chip8Gui::Chip8Gui(Chip8* chip8) : chip8(chip8) { }

Chip8Gui::~Chip8Gui() {
    close();
}


bool Chip8Gui::init() {

    bool success{true};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error in SDL initialization: %s", SDL_GetError());
        success = false;
    } else {
        if (!SDL_CreateWindowAndRenderer("CHIP8 Emulator", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer)) {
            SDL_Log("Error in SDL creation: %s", SDL_GetError());
            success = false;
        }
    }

    return success;
}

void Chip8Gui::update() {

}


bool Chip8Gui::processInput(const SDL_Event &e) const {

    bool running{true};

    if (e.type == SDL_EVENT_QUIT) {
        running = false;
    }
    switch (e.type) {

        case SDL_EVENT_KEY_DOWN:

            for (int i = 0; i < 16; i++) {
                if (e.key.key == keymap[i])
                    chip8->setKeypress(i, 1);
            }
            break;

        case SDL_EVENT_KEY_UP:

            for (int i = 0; i < 16; i++) {
                if (e.key.key == keymap[i])
                    chip8->setKeypress(i, 0);
            }
            break;

        default: break;
    }

    return running;
}

void Chip8Gui::render() const {

    const float pixelWidth = kScreenWidth / 64.f;
    const float pixelHeight = kScreenHeight / 32.f;

    SDL_SetRenderDrawColor(gRenderer, 12, 12, 12, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);

    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 32; y++) {

            if ( chip8->isPixelOn(x, y )) {
                SDL_SetRenderDrawColor(gRenderer, 255,255,255,255);
                SDL_FRect pixel = {(x*pixelWidth),(y*pixelHeight), pixelWidth, pixelHeight};
                SDL_RenderFillRect(gRenderer, &pixel);
            }
        }
    }
    SDL_RenderPresent(gRenderer);
}

void Chip8Gui::close() {
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;

    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    SDL_Quit();
}

