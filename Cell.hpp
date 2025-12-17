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
        } else if (E.type == GAME_LOST) {
            SnakeColor = Config::SNAKE_LOST_COLOR;
        } else if (E.type == GAME_WON) {
            SnakeColor = Config::SNAKE_VICTORY_COLOR;
        } else if (E.type == RESTART_GAME) {
            Initialize();
        }
    }
    void Tick(Uint32 DeltaTime) {
        if (CellState == Snake && FillPercent < 1) {
            GrowHead(DeltaTime);
        } else if (CellState != Snake && FillPercent > 0) {
            ShrinkTail(DeltaTime);
        }
    }

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
        } else if (FillPercent > 0) {
            SDL_FillRect(Surface, &SnakeRect,
            SDL_MapRGB(
                Surface->format,
                SnakeColor.r,
                SnakeColor.g,
                SnakeColor.b
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
        SnakeColor = Config::SNAKE_COLOR;
        SnakeDuration = 0;
        SnakeRect = BackgroundRect;
        FillPercent = 0.0;
        FillDirection = Right;
        int MiddleRow{ Config::GRID_ROWS / 2 };

        if (Row == MiddleRow && Col == 2) {
            CellState = Snake;
            SnakeDuration = 1;
            FillPercent = 1.0;
        } else if (Row == MiddleRow && Col == 3) {
            CellState = Snake;
            SnakeDuration = 2;
            FillPercent = 1.0;
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
            FillDirection = Data->Direction;
            FillPercent = 0;
        } else if (CellState == Snake) {
            if (SnakeDuration == Data->Length) {
                FillDirection = Data->Direction;
            }
            SnakeDuration--;
            if (SnakeDuration <= 0) {
                CellState = Empty;
            }
        }
    }

    void GrowHead(float DeltaTime) {
        using namespace Config;
        FillPercent += DeltaTime / ADVANCE_INTERVAL;
        if (FillPercent > 1) { FillPercent = 1; }

        SnakeRect = BackgroundRect;
        if (FillDirection == Right) {
            SnakeRect.w = CELL_SIZE * FillPercent;
        } else if (FillDirection == Down) {
            SnakeRect.h = CELL_SIZE * FillPercent;
        } else if (FillDirection == Left) {
            SnakeRect.x = BackgroundRect.x + CELL_SIZE * (1 - FillPercent);
        } else if (FillDirection == Up) {
            SnakeRect.y = BackgroundRect.y + CELL_SIZE * (1 - FillPercent);
        }
    }

    void ShrinkTail(float DeltaTime) {
        using namespace Config;
        FillPercent -= DeltaTime / ADVANCE_INTERVAL;
        if (FillPercent < 0) FillPercent = 0;

        if (FillDirection == Right) {
            SnakeRect.x = BackgroundRect.x + CELL_SIZE * (1 - FillPercent);
        } else if (FillDirection == Left) {
            SnakeRect.w = CELL_SIZE * FillPercent;
        } else if (FillDirection == Up) {
            SnakeRect.h = CELL_SIZE * FillPercent;
        } else if (FillDirection == Down) {
            SnakeRect.y = BackgroundRect.y + CELL_SIZE * (1 - FillPercent);
        }
    }

    int Row;
    int Col;
    int SnakeDuration{ 0 };
    float FillPercent{ 0 };
    MovementDirection FillDirection{ Right };
    SDL_Color SnakeColor{ Config::SNAKE_COLOR };
    Assets& Assets;
    CellState CellState;
    SDL_Rect BackgroundRect{
        Col * Config::CELL_SIZE + Config::PADDING,
        Row * Config::CELL_SIZE + Config::PADDING,
        Config::CELL_SIZE,
        Config::CELL_SIZE
    };
    SDL_Rect SnakeRect{

    };
    SDL_Color BackgroundColor{ 
        (Row + Col) % 2 == 0 
        ? Config::CELL_COLOR_A 
        : Config::CELL_COLOR_B 
    }; 
};