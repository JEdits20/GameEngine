#include "WindowsPlatform.h"
#include <iostream>

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    auto& platform = WindowsPlatformLayer::getInstance();
    switch (uMsg) {
        case WM_DESTROY:
            platform.pushEvent(new QuitEvent());
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            platform.pushEvent(new KeyPressEvent(static_cast<int>(wParam)));
            return 0;
        case WM_LBUTTONDOWN:
            platform.pushEvent(new MouseClickEvent(LOWORD(lParam), HIWORD(lParam)));
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

WindowsPlatformLayer::WindowsPlatformLayer()
    : hwnd(nullptr), hdc(nullptr) {}

WindowsPlatformLayer::~WindowsPlatformLayer() {
    shutdown();
}

void WindowsPlatformLayer::pushEvent(Event *event) {
    events.push_back(event);
}


void WindowsPlatformLayer::createWindow(const char* title, int minWidth, int minHeight, int width, int height) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "CustomWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, wc.hInstance, nullptr
    );

    if (!hwnd) {
        std::cerr << "Failed to create window" << std::endl;
        return;
    }

    ShowWindow(hwnd, SW_SHOW);
    hdc = GetDC(hwnd);

    isRunning = true;
}

std::vector<Event *> WindowsPlatformLayer::handleInput() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            events.push_back(new QuitEvent());
            isRunning = false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return events;
}

void WindowsPlatformLayer::render() {

}

void WindowsPlatformLayer::shutdown() {
    if (hdc && hwnd) {
        ReleaseDC(hwnd, hdc);
        DestroyWindow(hwnd);
        hwnd = nullptr;
        hdc = nullptr;
    }
}

void WindowsPlatformLayer::drawRectangle(int x, int y, int width, int height) {
    if (!hdc) return;
    RECT rect = { x, y, x + width, y + height };

    // Roten Brush erstellen
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}
