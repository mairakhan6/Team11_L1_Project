@echo off
cls

:: Update these paths to match your SFML and MinGW installation
set SFML_PATH=D:\HOORAIN\uni\3rd semester\C++\project\SFML-2.5.0
set MINGW_PATH=C:\mingw_dev_lib\mingw\mingw64\bin

:: Compile files individually in the correct order
%MINGW_PATH%\g++ -c src/square.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/pieces.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/piece.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/pawn.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/rook.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/knight.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/bishop.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/queen.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/king.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/timer.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/player.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/inputBox.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/dropdown.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/boardTheme.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/gameOverScreen.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/board.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/game.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/settings.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/welcome.cpp -I"%SFML_PATH%\include"
%MINGW_PATH%\g++ -c src/main.cpp -I"%SFML_PATH%\include"

:: Link all object files
%MINGW_PATH%\g++ *.o -o output.exe -L"%SFML_PATH%\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

:: Clean up object files
del *.o
