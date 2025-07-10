#include <vector>
#include "game/Event.h"
#include <thread>
#include <chrono>

#include "game/Game.h"
#ifdef _WIN32
#include "platform/WindowsPlatform.h"
#include <windows.h>
#else
#include "platform/LinuxPlatform.h"
#endif

int main() {
    constexpr int targetFPS = 60;
    constexpr int frameDuration = 1000 / targetFPS;
    #ifdef _WIN32
    PlatformLayer* platformLayer = &WindowsPlatformLayer::getInstance();
    #else
    PlatformLayer* platformLayer = &LinuxPlatformLayer::getInstance();
    #endif
    platformLayer->createWindow("test", 100, 100, 400, 400);
    platformLayer->drawRectangle(50, 50, 150, 150);

    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        for (Event* event : platformLayer->handleInput()) {
            Game::getInstance().handleEvent(*event);
            delete event;
        }
        auto frameEnd = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> frameTime = frameEnd - frameStart;
        int sleepTime = frameDuration - static_cast<int>(frameTime.count());
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
    return 0;
}