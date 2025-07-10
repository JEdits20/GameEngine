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

#include <X11/Xlib.h>
int main() {
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 400, 300, 1,
                                        BlackPixel(display, screen), WhitePixel(display, screen));

    XStoreName(display, window, "Event Handling Example");
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);
    XMapWindow(display, window);

    std::vector<Event*> events;

    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
        } else if (event.type == KeyPress) {
            events.push_back(new KeyPressEvent(event.xkey.keycode));
        } else if (event.type == ButtonPress) {
            events.push_back(new MouseClickEvent(event.xbutton.x, event.xbutton.y));
        } else if (event.type == ClientMessage) {
            events.push_back(new QuitEvent());
            break;
        }

        for (const auto& e : events) {
            Game::getInstance().handleEvent(*e);
            delete e;
        }
        events.clear();
    }

    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
#endif