#include "ltexture.h"

LTexture::LTexture() : mTexture{nullptr}, mWidth{0}, mHeight{0} {}

LTexture::~LTexture() {
    destroy();
}

bool LTexture::loadFromFile(const std::string& path) {
    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
    } else {
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr) {
            SDL_Log("Unable to create texture from %s! SDL error: %s\n", path.c_str(), SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_DestroySurface(loadedSurface);
    }

    return mTexture != nullptr;
}

void LTexture::destroy() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    mWidth = 0;
    mHeight = 0;
}

void LTexture::render(float x, float y) {
    const SDL_FRect dstRect = {x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};
    SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth() const { return mWidth; }
int LTexture::getHeight() const { return mHeight; }
bool LTexture::isLoaded() const { return mTexture != nullptr; }
