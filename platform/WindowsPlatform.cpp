#include "WindowsPlatform.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include "../ui/clickable/clickables/Button.h"

class Drawable;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    auto& platform = WindowsPlatformLayer::getInstance();
    switch (uMsg) {
        case WM_DESTROY:
            platform.pushEvent(std::make_unique<QuitEvent>());
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            platform.pushEvent(std::make_unique<KeyPressEvent>(static_cast<int>(wParam)));
            return 0;
        case WM_LBUTTONDOWN:
            platform.pushEvent(std::make_unique<MouseClickEvent>(LOWORD(lParam), HIWORD(lParam)));
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

WindowsPlatformLayer::WindowsPlatformLayer()
    : hwnd(nullptr), hdc(nullptr) {}

WindowsPlatformLayer::~WindowsPlatformLayer() {
    shutdown();
}

void WindowsPlatformLayer::pushEvent(std::unique_ptr<Event> event) {
    eventQueue.push(std::move(event));
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

std::unique_ptr<Event> WindowsPlatformLayer::handleInput() {
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            eventQueue.push(std::make_unique<QuitEvent>());
            isRunning = false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        return eventQueue.pop();
    }
    return nullptr;
}

void WindowsPlatformLayer::render() {
    std::vector<Drawable> values = { new Button()};
    for (Drawable drawable : values) {
        drawable->draw(*this);
    }
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
