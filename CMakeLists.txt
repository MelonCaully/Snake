cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Snake VERSION 1.0.0)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(Snake
  "main.cpp"
  "GameConfig.hpp"
  "Engine/Window.hpp"
  "Engine/Image.hpp"
  "Engine/Text.hpp"
  "Engine/Random.hpp"
  "GameUI.hpp"
  "Assets.hpp"
  "GameState.hpp"
  "Cell.hpp"
  "Grid.hpp"
  "SnakeData.hpp"
  "ScoreCounter.hpp"
  "RestartButton.hpp"
)

target_link_libraries(Snake PRIVATE
  SDL2::SDL2
  SDL2_image::SDL2_image
  SDL2_ttf::SDL2_ttf
)

# Copy Assets to output directory
add_custom_command(
  TARGET Snake POST_BUILD COMMAND
  ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_SOURCE_DIR}/Assets
      $<TARGET_FILE_DIR:Snake>/Assets
)