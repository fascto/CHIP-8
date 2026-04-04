//
// Created by tdela on 3/4/2026.
//

#include "main.h"

#include "chip8.h"

SDL_Window* window{nullptr};
SDL_Renderer* gRenderer{nullptr};

uint16_t gWidth{640};
uint16_t gHeight{320};

bool init() {

    bool success{true};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error in SDL initialization: ", SDL_GetError());
        success = false;
    } else {
        if (!SDL_CreateWindowAndRenderer("CHIP8 Emulator", gWidth, gHeight, 0, &window, &gRenderer)) {
            SDL_Log("Error in SDL creation: ", SDL_GetError());
            success = false;
        }
    }

    return success;
}

int main( int argc, char* args[] ) {

    std::cout << "CHIP8 EMULATOR!" << std::endl;

    int exitCode{0};

    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        exitCode = 1;
    } else {

        bool quit{false};

        SDL_Event event;
        SDL_zero( event );


        // Prueba
        Chip8 *chip8 = new Chip8();

        chip8->loadProgram("dummy.ch8");

        // Game Loop
        while (!quit) {
            while (SDL_PollEvent(&event)) {

                if( event.type == SDL_EVENT_QUIT )
                {
                    quit = true;
                }

            }
        }

    }


    return exitCode;
}
