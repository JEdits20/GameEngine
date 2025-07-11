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

LinuxPlatformLayer::~LinuxPlatformLayer() {
    if (inputThread.joinable() && std::this_thread::get_id() != inputThread.get_id()) {
        inputThread.join();
    }
    LinuxPlatformLayer::shutdown();
}


void LinuxPlatformLayer::createWindow(const char* title, int minWidth, int minHeight, int width, int height) {
    if (!display) {
        std::cerr << "Unable to open X display" << std::endl;
        return;
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    if (!window) {
        std::cerr << "Unable to create X Window" << std::endl;
        return;
    }
    XStoreName(display, window, title);
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);
    XMapWindow(display, window);
    isRunning.store(true);
    inputThread = std::thread([this]() {
        try {
            while (isRunning) {
                XEvent event;
                try {
                    if (XPending(display) > 0) XNextEvent(display, &event);
                } catch (...) {
                    std::cerr << "X11 threw an error. Possibly invalid or closed display.\n";
                    break;
                }
                if (event.type == Expose) {
                } else if (event.type == KeyPress) {
                    eventQueue.push(std::make_unique<KeyPressEvent>(event.xkey.keycode));
                } else if (event.type == ButtonPress) {
                    eventQueue.push(std::make_unique<MouseClickEvent>(event.xbutton.x, event.xbutton.y));
                } else if (event.type == ClientMessage) {
                    eventQueue.push(std::make_unique<QuitEvent>());
                }
            }
        } catch (const std::exception &e) {
            std::cerr << "Input thread exception: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Input thread unknown exception" << std::endl;
        }
    });
}

std::unique_ptr<Event> LinuxPlatformLayer::handleInput() {
    return eventQueue.pop();
}

void LinuxPlatformLayer::render() {
    //TODO
}

void LinuxPlatformLayer::shutdown() {
    if (!isRunning.exchange(false)) return;
    if (inputThread.joinable() && std::this_thread::get_id() != inputThread.get_id()) {
        inputThread.join();
    }
    if (display) {
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        display = nullptr;
    }
}

void LinuxPlatformLayer::drawRectangle(int x, int y, int width, int height) {
    GC gc = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    XFillRectangle(display, window, gc, x, y, width, height);
    XFreeGC(display, gc);
}
