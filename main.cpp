#include <iostream>
#include <vector>
#include "game/Event.h"
#include "game/Game.h"

#ifdef _WIN32
#include <windows.h>
static std::vector<Event*> events;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            events.push_back(new QuitEvent());
            return 0;
        case WM_KEYDOWN:
            events.push_back(new KeyPressEvent(static_cast<int>(wParam)));
            return 0;
        case WM_LBUTTONDOWN:
            events.push_back(new MouseClickEvent(LOWORD(lParam), HIWORD(lParam)));
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Event Handling Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    for (const auto& event : events) {
        Game::getInstance().handleEvent(*event);
        delete event;
    }

    return 0;
}

#else

#include <thread>
#include <bits/chrono.h>
#include <X11/Xlib.h>

#include "platform/LinuxPlatform.h"


int main() {
    const int targetFPS = 60; // Target frames per second
    const int frameDuration = 1000 / targetFPS; // Duration of each frame in milliseconds

    LinuxPlatformLayer::getInstance().createWindow("test", 100, 100, 400, 400);
    LinuxPlatformLayer::getInstance().drawRectangle(50, 50, 150, 150);

    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Handle input events
        for (Event* event : LinuxPlatformLayer::getInstance().handleInput()) {
            Game::getInstance().handleEvent(*event);
            delete event;
        }

        // Calculate the time taken for the frame
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> frameTime = frameEnd - frameStart;

        // Calculate how long to sleep to maintain the target FPS
        int sleepTime = frameDuration - static_cast<int>(frameTime.count());
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
    return 0;
}
#endif