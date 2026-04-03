
#include "./main.h"

bool init();

bool loadMedia();

void close();

// GLOBAL VARIABLES
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

SDL_Window* gWindow = {nullptr};

SDL_Surface* gScreenSurface = {nullptr};

SDL_Surface* gHelloWorld{ nullptr };

bool init() {

    bool success{true};

    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError() );

        success = false;
    } else {

        if (gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0 ); gWindow == nullptr ) {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia() {

    bool success{true};

    const std::string imagePath = { "../../hello-sdl3.bmp" };

    if ( gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr ) {

        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load BMP: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {

    SDL_DestroySurface( gScreenSurface );
    gHelloWorld = nullptr;

    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}

SDL_Renderer* gRenderer{ nullptr };
SDL_Texture* gTexture{ nullptr };
LTexture gPngTexture;

LTexture::LTexture() : mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 } { }

LTexture::~LTexture() {
    this->destroy();
}

bool LTexture::loadFromFile( const std::string& path ) {

    constexpr bool success { true };

    if(SDL_Surface *loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr ) {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    } else {
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); gTexture == nullptr ) {
            SDL_Log("Unable to create texture ");
        }
    }

    return success;

}

void LTexture::destroy() {
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;

    mWidth = 0;
    mHeight = 0;
}

//Draws texture
void render( float x, float y );

//Gets texture attributes
int LTexture::getWidth();
int getHeight();
bool isLoaded() { return true; }



int main( int argc, char* args[] )
{
    int exitCode{ 0 };

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
                SDL_FillSurfaceRect( gScreenSurface, nullptr, SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF ) );

                SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr );

                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    close();

    return exitCode;
}


