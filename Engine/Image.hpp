#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../GameConfig.hpp"

class Image {
public:
    Image(const std::string& Path) {
        ImageSurface = IMG_Load(Path.c_str());
        CheckSDLError("Creating Image Surface");
    }

    void Render(SDL_Surface* Surface, SDL_Rect* Rect) {
        SDL_BlitScaled(ImageSurface, nullptr, Surface, Rect);
    }

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    ~Image() {
        if (ImageSurface) {
            SDL_FreeSurface(ImageSurface);
        }
    }

private:
    SDL_Surface* ImageSurface;
};