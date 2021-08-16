cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMKAE_CXX_STANDARD_REQUIRED True)

project(sudoku-solver VERSION 1.0)

set(src
  src/main.cpp
  src/solver.cpp
  )

add_executable(sudoku-solver ${src})
target_include_directories(sudoku-solver PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/include
  )
