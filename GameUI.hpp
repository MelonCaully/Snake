#pragma once
#include <SDL2/SDL.h>
#include "Assets.hpp"

class GameUI {
public:
    void HandleEvent(SDL_Event& E) {}
    void Tick(Uint32 DeltaTime) {}
    void Render(SDL_Surface* Surface) {}

private:
    Assets Assets;
};