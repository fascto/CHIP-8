//
// Created by tdela on 3/4/2026.
//

#include "main.h"
#include <chrono>
#include "chip8.h"
#include "chip8_gui.h"

int main( int argc, char* args[] ) {

    std::cout << "CHIP8 EMULATOR!" << std::endl;

    int exit_code{0};

    // Prueba
    Chip8 chip8;
    Chip8Gui chip8_gui(&chip8);


    if (!chip8_gui.init()) {
        std::cout << "Failed to initialize!" << std::endl;
        exit_code = 1;
    } else {

        bool game_is_running{true};

        SDL_Event event;
        SDL_zero( event );

        chip8.loadProgram("dummy.ch8");

        constexpr float targetFreq = 1.0f / 60.0f;
        float acc = 0.0f;

        auto prevTime = std::chrono::high_resolution_clock::now();

        // Game Loop
        while (game_is_running) {

            chip8.LoopFDE();

            // TODO: Funcion de dibujar con SDL
            chip8_gui.render();

            // Loop eventos
            while (SDL_PollEvent(&event))
                if (!chip8_gui.processInput(event))
                    game_is_running = false;
            }

            // Mover a una funciona quizas
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = currentTime - prevTime;
            float deltaTime = elapsed.count();
            prevTime = currentTime;
            acc += deltaTime;

            while (acc >= targetFreq) {
                chip8.updateTimers();
                acc -= targetFreq;
            }
        }

    return exit_code;
}
