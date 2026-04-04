#ifndef CHIP_8_LTEXTURE_H
#define CHIP_8_LTEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

class LTexture {
public:
    LTexture();
    ~LTexture();

    LTexture(const LTexture&) = delete;
    LTexture& operator=(const LTexture&) = delete;
    LTexture(LTexture&&) = delete;
    LTexture& operator=(LTexture&&) = delete;

    bool loadFromFile(const std::string& path);
    void destroy();
    void render(float x, float y);

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] bool isLoaded() const;

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif // CHIP_8_LTEXTURE_H
