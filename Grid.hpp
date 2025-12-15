#pragma once
#include <vector>

#include "Cell.hpp"
#include "GameConfig.hpp"
#include "Engine/Random.hpp"

class Grid {
public:
    Grid(Assets& Assets) {
        using namespace Config;
        Cells.reserve(GRID_ROWS * GRID_COLUMNS);
        for (int R{ 0 }; R < GRID_ROWS; ++R) {
            for (int C{ 0 }; C < GRID_COLUMNS; ++C) {
                Cells.emplace_back(R, C, Assets);
            }
        }
    }

    void HandleEvent(SDL_Event& E) {
        for (auto& Cell : Cells) {
            Cell.HandleEvent(E);
        }
        if (E.type == UserEvents::APPLE_EATEN) {
            PlaceRandomApple();
        }
    }

    void Tick(Uint32 DeltaTime) {
        for (auto& Cell : Cells) {
            Cell.Tick(DeltaTime);
        }
    }

    void Render(SDL_Surface* Surface) {
        for (auto& Cell : Cells) {
            Cell.Render(Surface);
        }
    }
private:
    std::vector<Cell> Cells;

    void PlaceRandomApple() {
        while(true) {
            int RandomIndex { Random::Int(0, Cells.size() - 1) };
            if (Cells[RandomIndex].PlaceApple()) {
                break;
            }
        }
    }
};