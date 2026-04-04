//
// Created by tdela on 3/4/2026.
//

#include "../keys_capture.h"
#include "../ltexture.h"


SDL_Renderer* gRenderer{nullptr};
SDL_Window* gWindow{nullptr};

constexpr int kScreenWidth{800};
constexpr int kScreenHeight{600};

LTexture gUpTexture, gDownTexture, gLeftTexture, gRightTexture;

bool init() {

    bool success{true};

    if (!SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    } else {

        if( SDL_CreateWindowAndRenderer( "SDL3 Tutorial: Textures and Extension Libraries", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer ) == false ) {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}


bool loadMedia() {

    bool success{true};

    if (!gUpTexture.loadFromFile("../../up.png")) {
        SDL_Log("Unable to load up image");
        success = false;
    }
    if (!gDownTexture.loadFromFile("../../down.png")) {
        SDL_Log("Unable to load down image");
        success = false;
    }
    if (!gRightTexture.loadFromFile("../../right.png")) {
        SDL_Log("Unable to load right image");
        success = false;
    }
    if (!gLeftTexture.loadFromFile("../../left.png")) {
        SDL_Log("Unable to load left image");
        success = false;
    }

    return success;
}

void close() {
    gUpTexture.destroy();
    gDownTexture.destroy();
    gLeftTexture.destroy();
    gRightTexture.destroy();

    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    SDL_Quit();
}



int main(int argc, char* args[])
{
    int exitCode{0};

    if (init() == false)
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        if (loadMedia() == false)
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        else
        {
            bool quit{false};
            SDL_Event e;
            SDL_zero(e);

            LTexture* currentTexture = &gUpTexture;
            SDL_Color bgColor{0xFF, 0xFF, 0xFF, 0xFF};

            while (quit == false)
            {
                while (SDL_PollEvent(&e) == true)
                {
                    if (e.type == SDL_EVENT_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_EVENT_KEY_DOWN)
                    {
                        if (e.key.key == SDLK_UP)
                        {
                            currentTexture = &gUpTexture;
                        }
                        else if (e.key.key == SDLK_DOWN)
                        {
                            currentTexture = &gDownTexture;
                        }
                        else if (e.key.key == SDLK_LEFT)
                        {
                            currentTexture = &gLeftTexture;
                        }
                        else if (e.key.key == SDLK_RIGHT)
                        {
                            currentTexture = &gRightTexture;
                        }
                    }
                }

                bgColor.r = 0xFF;
                bgColor.g = 0xFF;
                bgColor.b = 0xFF;

                const bool* keyStates = SDL_GetKeyboardState(nullptr);
                if (keyStates[SDL_SCANCODE_UP] == true)
                {
                    bgColor.r = 0xFF;
                    bgColor.g = 0x00;
                    bgColor.b = 0x00;
                }
                else if (keyStates[SDL_SCANCODE_DOWN] == true)
                {
                    bgColor.r = 0x00;
                    bgColor.g = 0xFF;
                    bgColor.b = 0x00;
                }
                else if (keyStates[SDL_SCANCODE_LEFT] == true)
                {
                    bgColor.r = 0xFF;
                    bgColor.g = 0xFF;
                    bgColor.b = 0x00;
                }
                else if (keyStates[SDL_SCANCODE_RIGHT] == true)
                {
                    bgColor.r = 0x00;
                    bgColor.g = 0x00;
                    bgColor.b = 0xFF;
                }

                SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
                SDL_RenderClear(gRenderer);

                currentTexture->render(
                    (static_cast<float>(kScreenWidth) - static_cast<float>(currentTexture->getWidth())) / 2.f,
                    (static_cast<float>(kScreenHeight) - static_cast<float>(currentTexture->getHeight())) / 2.f
                );

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();
    return exitCode;
}
