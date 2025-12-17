# Snake (Clone)
This project is an Snake clone created using the SDL2 lirary\
with C++. A custom engine that supports:
- Image Objects
- Rendom Num Gen
- Text Objects
- Window Objects
![](Assets/demo.gif)

## Features
- Win, Loss and Pause states
- Restart Button
- Grid and Cell Objects for Level Layout
- Score Counter
- Smooth Snake Animation

### Needs added
- Settings menu
- Input Queue for Keyboard
- Add const for const-correctness
- Add static and inline where needed
- Overall Refactor

## How to Play
If you want to take a gander at the game and mess around with the\
files you can clone the repository and run build_run.bat in the root\
of the project. This will compile the game into an executable in the\
'Debug' folder inside 'build' where you can then run it. Most settings\
for the game will be in GameConfig.hpp if you want to modify to your liking.

You will have to have the SDL2 package integrated into the project. I used\
vcpkg to manage my packages/libraries, you can use a differant method you will\
have to modify the CMakeLists.txt file to understand where your SDL2 libraries are.