cmake_minimum_required(VERSION 3.27)
project(Ludo_Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ludo_Game main.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        Game.h
        Board.cpp
        Board.h
        Computer.cpp
        Computer.h)
