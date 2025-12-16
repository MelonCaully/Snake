#pragma once
#include <SDL2/SDL.h>
#include "Engine/Text.hpp"
#include "GameConfig.hpp"

class RestartButton {
public:
    void Render(SDL_Surface* Surface) {
        SDL_FillRect(Surface, &ButtonRect,
            SDL_MapRGB(
                Surface->format,
                ButtonColor.r,
                ButtonColor.g,
                ButtonColor.b
            ));
        Text.Render(Surface, &TextRect);        
    }

    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        if (E.type == SDL_MOUSEBUTTONDOWN) {
            HandleClick(E.button);       
        }
    }

private:
    void HandleClick(SDL_MouseButtonEvent& E) {
        using namespace UserEvents;
        if (
            E.x >= ButtonRect.x &&
            E.x <= ButtonRect.x + ButtonRect.w &&
            E.y >= ButtonRect.y &&
            E.y <= ButtonRect.y + ButtonRect.h
        ) {
            SDL_Event RestartEvent{ RESTART_GAME };
            SDL_PushEvent(&RestartEvent);
        }
    }

    Text Text{ "RESTART", 20 };
    SDL_Color ButtonColor{ Config::BUTTON_COLOR };
    SDL_Rect ButtonRect{
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
    };
    SDL_Rect TextRect{
        ButtonRect.x + Config::PADDING * 5,
        ButtonRect.y + Config::PADDING * 3,
        0, 0
    };
};