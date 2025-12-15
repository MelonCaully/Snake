#pragma once
#include <SDL2/SDL.h>
#include "Assets.hpp"
#include "Grid.hpp"

class GameUI {
public:
    GameUI() : Grid{ Assets } {}

    void HandleEvent(SDL_Event& E) {
        Grid.HandleEvent(E);
    }
    void Tick(Uint32 DeltaTime) {
        Grid.Tick(DeltaTime);
    }
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
    }

private:
    Grid Grid;
    Assets Assets;
};