#pragma once
#include <SDL2/SDL.h>

#include "Assets.hpp"
#include "GameConfig.hpp"
#include "SnakeData.hpp"

enum CellState {
    Snake,
    Apple,
    Empty
};

class Cell {
public:
    Cell(int Row, int Col, Assets& Assets) : Row{ Row }, Col{ Col }, Assets{ Assets } {
        Initialize();
    }

    void HandleEvent(SDL_Event& E) {
        using namespace UserEvents;
        if (E.type == ADVANCE) {
            Advance(E.user);
        } else if (E.type == APPLE_EATEN) {
            if (CellState == Snake) {
                ++SnakeDuration;
            }
        } else if (E.type == RESTART_GAME) {
            Initialize();
        }
    }
    void Tick(Uint32 DeltaTime) {}

    void Render(SDL_Surface* Surface) {
        SDL_FillRect(Surface, &BackgroundRect, 
            SDL_MapRGB(
                Surface->format,
                BackgroundColor.r,
                BackgroundColor.g,
                BackgroundColor.b
            )
        );

        if (CellState == Apple) {
            Assets.Apple.Render(Surface, &BackgroundRect);
        } else if (CellState == Snake) {
            SDL_FillRect(Surface, &BackgroundRect,
            SDL_MapRGB(
                Surface->format,
                Config::SNAKE_COLOR.r,
                Config::SNAKE_COLOR.g,
                Config::SNAKE_COLOR.b
            ));
        };
    }

    bool PlaceApple() {
        if (CellState != Empty) return false;

        CellState = Apple;
        return true;
    }

private:
    void Initialize() {
        CellState = Empty;
        SnakeDuration = 0;
        int MiddleRow{ Config::GRID_ROWS / 2 };

        if (Row == MiddleRow && Col == 2) {
            CellState = Snake;
            SnakeDuration = 1;
        } else if (Row == MiddleRow && Col == 3) {
            CellState = Snake;
            SnakeDuration = 2;
        } else if (Row == MiddleRow && Col == 11) {
            CellState = Apple;
        }
    }
    
    void Advance(SDL_UserEvent& E) {
        SnakeData* Data{ static_cast<SnakeData*>(E.data1) };

        bool isThisCell{
            Data->HeadRow == Row &&
            Data->HeadCol == Col
        };

        if (isThisCell) {
            if (CellState == Snake) {
                SDL_Event Event{ UserEvents::GAME_LOST };
                SDL_PushEvent(&Event);
                return;
            }
            if (CellState == Apple) {
                SDL_Event Event{ UserEvents::APPLE_EATEN };
                SDL_PushEvent(&Event);
            }
            CellState = Snake;
            SnakeDuration = Data->Length;
        } else if (CellState == Snake) {
            --SnakeDuration;
            if (SnakeDuration == 0) {
                CellState = Empty;
            }
        }
    }

    int Row;
    int Col;
    int SnakeDuration{ 0 };
    Assets& Assets;
    CellState CellState;
    SDL_Rect BackgroundRect{
        Col * Config::CELL_SIZE + Config::PADDING,
        Row * Config::CELL_SIZE + Config::PADDING,
        Config::CELL_SIZE,
        Config::CELL_SIZE
    };
    SDL_Color BackgroundColor{ 
        (Row + Col) % 2 == 0 
        ? Config::CELL_COLOR_A 
        : Config::CELL_COLOR_B 
    }; 
};