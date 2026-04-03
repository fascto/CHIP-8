
#include "./main.h"

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

SDL_Window* gWindow = {nullptr};
SDL_Renderer* gRenderer{ nullptr };


LTexture gPngTexture;

bool init() {

    bool success{true};

    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
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

    const std::string imagePath = { "../../loaded.png" };

    if ( gPngTexture.loadFromFile(imagePath) == false ) {

        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load BMP: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    gPngTexture.destroy();

    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Final exit code
    int exitCode{ 0 };

    //Initialize
    if( init() == false )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    }
    else
    {
        if( loadMedia() == false )
        {
            SDL_Log( "Unable to load media!\n" );
            exitCode = 2;
        }
        else
        {
            bool quit{ false };

            SDL_Event e;
            SDL_zero( e );

            while( quit == false )
            {
                while( SDL_PollEvent( &e ) == true )
                {
                    if( e.type == SDL_EVENT_QUIT )
                    {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                gPngTexture.render( 0.f, 0.f );

                SDL_RenderPresent( gRenderer );
            }
        }
    }

    close();

    return exitCode;
}
