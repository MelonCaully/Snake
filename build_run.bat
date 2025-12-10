@echo off
setlocal

rmdir /s /q build
mkdir build
cd build

cmake ..
msbuild Snake.sln

cd Debug
Snake.exe

endlocal