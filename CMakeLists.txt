cmake_minimum_required(VERSION 3.31)
project(GameEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameEngine main.cpp
        game/Event.h
        game/Game.cpp
        game/Game.h
        windows/window.cpp
)

if(WIN32)
    target_link_libraries(GameEngine PRIVATE user32 gdi32)
elseif(UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(GameEngine PRIVATE X11)
endif()