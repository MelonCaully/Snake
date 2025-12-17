#pragma once
#include <SDL2/SDL.h>
#include "Assets.hpp"
#include "GameConfig.hpp"
#include "Engine/Text.hpp"

class ScoreCounter {
public:
    ScoreCounter(Assets& Assets) : Assets{ Assets } {}

    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        if (E.type == APPLE_EATEN) {
            ++CurrentScore;
            Text.SetText(GetScoreString());
        } else if (E.type == RESTART_GAME) {
            CurrentScore = 0;
            Text.SetText(GetScoreString());
        }
    }
    void Render(SDL_Surface* Surface) {
        using namespace Config;
        SDL_FillRect(Surface, &BackgroundRect,
            SDL_MapRGB(Surface->format,
                SCORE_BACKGROUND_COLOR.r,
                SCORE_BACKGROUND_COLOR.g,
                SCORE_BACKGROUND_COLOR.b
            ));
        Assets.Apple.Render(Surface, &AppleRect);
        Text.Render(Surface, &TextRect);
    }

private:
    std::string GetScoreString() { return std::to_string(CurrentScore) + "/" + std::to_string(MaxScore); }

    Assets& Assets;
    int CurrentScore{ 0 };
    int MaxScore{ Config::MAX_LENGTH - 2 };
    Text Text{ GetScoreString(), 40 };
    SDL_Rect BackgroundRect{
        Config::PADDING,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        MaxScore > 99 ? 250 : 190,
        Config::FOOTER_HEIGHT - Config::PADDING        
    };
    SDL_Rect AppleRect{
        BackgroundRect.x + Config::PADDING,
        BackgroundRect.y + Config::PADDING,
        BackgroundRect.h - Config::PADDING * 2,
        BackgroundRect.h - Config::PADDING * 2
    };
    SDL_Rect TextRect{
        AppleRect.x + AppleRect.w + Config::PADDING,
        AppleRect.y, 0, 0
    };
};