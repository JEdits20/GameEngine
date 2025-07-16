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
        ui/Drawable.cpp
        ui/Drawable.h
        ui/clickable/Clickable.cpp
        ui/clickable/Clickable.h
        ui/nonInteractive/Menu.cpp
        ui/nonInteractive/Menu.h
        ui/clickable/clickables/Button.cpp
        ui/clickable/clickables/Button.h
        ui/clickable/clickables/Slider.cpp
        ui/clickable/clickables/Slider.h
        ui/text/TextBox.cpp
        ui/text/TextBox.h
        ui/basics/RoundRect.cpp
        ui/basics/RoundRect.h
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
