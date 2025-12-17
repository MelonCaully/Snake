#pragma once
#include <SDL2/SDL.h>

#include "Assets.hpp"
#include "Grid.hpp"
#include "RestartButton.hpp"
#include "ScoreCounter.hpp"

class GameUI {
public:
    GameUI() : Grid{ Assets }, ScoreCounter{ Assets } {}

    void HandleEvent(SDL_Event& E) {
        Grid.HandleEvent(E);
        ScoreCounter.HandleEvent(E);
        RestartButton.HandleEvent(E);
    }
    
    void Tick(Uint32 DeltaTime) {
        Grid.Tick(DeltaTime);
    }
    
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
        ScoreCounter.Render(Surface);
        RestartButton.Render(Surface);
    }

private:
    Grid Grid;
    RestartButton RestartButton;
    ScoreCounter ScoreCounter;
    Assets Assets;
};