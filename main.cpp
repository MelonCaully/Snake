#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Engine/Window.hpp"
#include "GameUI.hpp"
#include "GameState.hpp"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    CheckSDLError("Initializing SDL");
    IMG_Init(IMG_INIT_PNG);
    CheckSDLError("Initializing SDL_image");
    TTF_Init();
    CheckSDLError("Initializing SDL_ttf");

    Window GameWindow{};
    GameUI UI{};
    GameState State;
    Uint32 PreviousTick{ SDL_GetTicks() };
    Uint32 CurrentTick;
    Uint32 DeltaTime;
    SDL_Event Event;

    while(true) {
        CurrentTick = SDL_GetTicks();
        DeltaTime = CurrentTick - PreviousTick;

        while(SDL_PollEvent(&Event)) {
            UI.HandleEvent(Event);
            State.HandleEvent(Event);
            if (Event.type == SDL_QUIT || Event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_Quit();
                IMG_Quit();
                return 0;
            }
        }

        State.Tick(DeltaTime);
        UI.Tick(DeltaTime);

        GameWindow.Render();
        UI.Render(GameWindow.GetSurface());

        GameWindow.Update();

        PreviousTick = CurrentTick;
    }
}