# cmake_minimum_required(VERSION <specify CMake version here>)
project(First_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(First_Project main.cpp Player.cpp Player.h Die.cpp Die.h Yahtzee.cpp Yahtzee.h ScoreSheet.cpp ScoreSheet.h)