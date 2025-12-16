#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../GameConfig.hpp"

class Text {
public:
    Text(const std::string& InitialText, int FontSize) : Content{ InitialText }, Font{ nullptr }, TextSurface{ nullptr } {
        Font = TTF_OpenFont(Config::FONT.c_str(), FontSize);
        CheckSDLError("Opening Font");

        SetText(InitialText);
    }

    void Render(SDL_Surface* Surface, SDL_Rect* Rect) {
        if (TextSurface) {
            SDL_BlitSurface(TextSurface, nullptr, Surface, Rect);
        }
    }

    void SetText(const std::string& NewText) {
        Content = NewText;

        if (TextSurface) {
            SDL_FreeSurface(TextSurface);
        }
        TextSurface = TTF_RenderText_Blended(Font, Content.c_str(), Config::FONT_COLOR);
        CheckSDLError("Creating Text Surface");
    }

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

    ~Text() {
        if (TextSurface) {
            SDL_FreeSurface(TextSurface);
        }
        if (Font) {
            TTF_CloseFont(Font);
        }
    }

private: 
    std::string Content;
    TTF_Font* Font;
    SDL_Surface* TextSurface;
};