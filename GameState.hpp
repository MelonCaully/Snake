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
            if (Snake.Length == Config::MAX_LENGTH) {
                SDL_Event Event{ GAME_WON };
                SDL_PushEvent(&Event);
            }
        } else if (E.type == RESTART_GAME) {
            RestartGame();
        } else if (E.type == GAME_LOST) {
            isGameOver = true;
        }
    }
    void Tick(Uint32 DeltaTime) {
        if (isPaused || isGameOver) { return; }
        ElapsedTime += DeltaTime;
        if (ElapsedTime >= Config::ADVANCE_INTERVAL) {
            ElapsedTime = 0;
            UpdateSnake();
        }
    }

private:
    void HandleKeyEvent(SDL_KeyboardEvent& E) {
        if (isGameOver) { return; }
        switch(E.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                Unpause();
                if (Snake.Direction != Down) {
                    NextDirection = Up;
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                Unpause();
                if (Snake.Direction != Up) {
                    NextDirection = Down;
                }
                break;
            case SDLK_LEFT:
            case SDLK_a:
                Unpause();
                if (Snake.Direction != Right) {
                    NextDirection = Left;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                Unpause();
                if (Snake.Direction != Left) {
                    NextDirection = Right;
                }
                break;
            case SDLK_SPACE:
                if (!isPaused) { isPaused = true; }
        }
    }

    void Unpause() {
        if (isPaused) {
            isPaused = false;
            UpdateSnake();
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

        if (
            Snake.HeadRow < 0 ||
            Snake.HeadRow >= Config::GRID_ROWS ||
            Snake.HeadCol < 0 || 
            Snake.HeadCol >= Config::GRID_COLUMNS
        ) {
            SDL_Event Event{ UserEvents::GAME_LOST };
            SDL_PushEvent(&Event);
        } else {
            SDL_Event Event{ UserEvents::ADVANCE };
            Event.user.data1 = &Snake;
            SDL_PushEvent(&Event);
        }
    }

    void RestartGame() {
        isGameOver = false;
        isPaused = true;
        ElapsedTime = 0;
        Snake = { Config::GRID_ROWS / 2, 3, 2, Right };
        NextDirection = Right;
    }

    bool isPaused{ true };
    bool isGameOver{ false };
    Uint32 ElapsedTime{ 0 };
    MovementDirection NextDirection{ Right };
    SnakeData Snake{ Config::GRID_ROWS / 2, 3, 2 };
};