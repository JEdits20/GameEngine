#include "LinuxPlatform.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <thread>

LinuxPlatformLayer::LinuxPlatformLayer() {
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
}

LinuxPlatformLayer::~LinuxPlatformLayer(){
    LinuxPlatformLayer::shutdown();
}


void LinuxPlatformLayer::createWindow(const char* title, int minWidth, int minHeight, int width, int height) {
    if (!display) {
        std::cerr << "Unable to open X display" << std::endl;
        return;
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XStoreName(display, window, title);
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);
    XMapWindow(display, window);
    isRunning = true;

    std::thread inputThread([this]() {
        while (isRunning) {
            XEvent event;
            XNextEvent(display, &event);
            if (event.type == Expose) {
            } else if (event.type == KeyPress) {
                events.push_back(std::make_unique<KeyPressEvent>(event.xkey.keycode));
            } else if (event.type == ButtonPress) {
                events.push_back(std::make_unique<MouseClickEvent>(event.xbutton.x, event.xbutton.y));
            } else if (event.type == ClientMessage) {
                events.push_back(std::make_unique<QuitEvent>());
            }
        }
    });
}

std::vector<std::unique_ptr<Event>>& LinuxPlatformLayer::handleInput() {
    return events;
}

void LinuxPlatformLayer::render() {
    //TODO
}

void LinuxPlatformLayer::shutdown() {
    isRunning = false;
    if (inputThread.joinable()) inputThread.join();
    if (display) {
        XDestroyWindow(display, window);
        XCloseDisplay(display);
    }
}

void LinuxPlatformLayer::drawRectangle(int x, int y, int width, int height) {
    GC gc = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    XFillRectangle(display, window, gc, x, y, width, height);
    XFreeGC(display, gc);
}
