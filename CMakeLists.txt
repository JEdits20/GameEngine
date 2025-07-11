cmake_minimum_required(VERSION 3.31)
project(GameEngine)

set(CMAKE_CXX_STANDARD 23)

set(COMMON_SOURCES
        main.cpp
        game/Game.cpp
        game/Game.h
        game/Event.h
        platform/PlatformLayer.h
        platform/SPSCQueue.h
)

if(WIN32)
    set(PLATFORM_SOURCES
            platform/WindowsPlatform.cpp
            platform/WindowsPlatform.h
    )
elseif(UNIX)
    set(PLATFORM_SOURCES
            platform/LinuxPlatform.cpp
            platform/LinuxPlatform.h
    )
endif()

add_executable(GameEngine
        ${COMMON_SOURCES}
        ${PLATFORM_SOURCES}
)

if(WIN32)
    target_link_libraries(GameEngine PRIVATE user32 gdi32)
elseif(UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(GameEngine PRIVATE X11)
endif()
