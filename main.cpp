
#include "./main.h"

bool init();

bool loadMedia();

void close();

// GLOBAL VARIABLES
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

SDL_Window* gWindow = {nullptr};
SDL_Renderer* gRenderer{ nullptr };


LTexture gPngTexture;

LTexture::LTexture() : mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 } { }

LTexture::~LTexture() {
    this->destroy();
}

bool LTexture::loadFromFile( const std::string& path ) {

    if(SDL_Surface *loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr ) {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    } else {
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr ) {
            SDL_Log("Unable to create texture ");
        } else {
            SDL_Log("Created texture from surface ");
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_DestroySurface( loadedSurface );
    }

    return mTexture != nullptr;
}

void LTexture::destroy() {
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;

    mWidth = 0;
    mHeight = 0;
}

//Draws texture
void LTexture::render( float x, float y ) {
    const SDL_FRect dstReact = { x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    // Render the texture
    SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstReact);
}

//Gets texture attributes
int LTexture::getWidth() const { return mWidth; }
int LTexture::getHeight() const { return mHeight; }
bool LTexture::isLoaded() const { return mTexture != nullptr; }


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
        //Load media
        if( loadMedia() == false )
        {
            SDL_Log( "Unable to load media!\n" );
            exitCode = 2;
        }
        else
        {
            //The quit flag
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero( e );

            //The main loop
            while( quit == false )
            {
                //Get event data
                while( SDL_PollEvent( &e ) == true )
                {
                    //If event is quit type
                    if( e.type == SDL_EVENT_QUIT )
                    {
                        //End the main loop
                        quit = true;
                    }
                }

                //Fill the background white
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render image on screen
                gPngTexture.render( 0.f, 0.f );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    close();

    return exitCode;
}
