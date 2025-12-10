#pragma once 
#define CHECK_ERRORS

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

namespace Config {
    // Game settings
    inline const std::string GAME_NAME{ "Snake" };
    inline constexpr int WINDOW_HEIGHT{ 400 };
    inline constexpr int WINDOW_WIDTH{ 800 };

    // Colors
    inline constexpr SDL_Color BACKGROUND_COLOR{ 85, 138, 52, 255 };
    inline constexpr SDL_Color FONT_COLOR{ 255, 255, 255, 255 };

    // Asset Paths
    inline const std::string APPLE_IMAGE{ "Assets/apple.png" };
    inline const std::string FONT{ "Assets/Rubik-SemimBold.ttf" };
}

inline void CheckSDLError(const std::string& Msg) {
#ifdef CHECK_ERRORS
    const char* error = SDL_GetError();
    if (*error != '\0') {
        std::cerr << Msg << " Error: " << error << '\n';
        SDL_ClearError();
    }
#endif
}