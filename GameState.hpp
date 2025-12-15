#pragma once
#include <SDL2/SDL.h>
#include "SnakeData.hpp"
#include "GameConfig.hpp"

class GameState {
public:
    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        if (E.type == SDL_KEYDOWN) {
            HandleKeyEvent(E.key);
        } else if (E.type == APPLE_EATEN) {
            Snake.Length++;
        }
    }
    void Tick(Uint32 DeltaTime) {
        ElapsedTime += DeltaTime;
        if (ElapsedTime >= Config::ADVANCE_INTERVAL) {
            ElapsedTime = 0;
            UpdateSnake();
        }
    }

private:
    void HandleKeyEvent(SDL_KeyboardEvent& E) {
        switch(E.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                if (Snake.Direction != Down) {
                    NextDirection = Up;
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                if (Snake.Direction != Up) {
                    NextDirection = Down;
                }
                break;
            case SDLK_LEFT:
            case SDLK_a:
                if (Snake.Direction != Right) {
                    NextDirection = Left;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                if (Snake.Direction != Left) {
                    NextDirection = Right;
                }
                break;
        }
    }

    void UpdateSnake() {
        Snake.Direction = NextDirection;
        switch(NextDirection) {
            case Up:
                Snake.HeadRow--;
                break;
            case Down:
                Snake.HeadRow++;
                break;
            case Left:
                Snake.HeadCol--;
                break;
            case Right:
                Snake.HeadCol++;
                break;
        }

        SDL_Event Event{ UserEvents::ADVANCE };
        Event.user.data1 = &Snake;
        SDL_PushEvent(&Event);
    }

    MovementDirection NextDirection{ Right };
    Uint32 ElapsedTime;
    SnakeData Snake{ Config::GRID_ROWS / 2, 3, 2, Right };
};