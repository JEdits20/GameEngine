#ifndef LINUXPLATFORM_H
#define LINUXPLATFORM_H

#include "PlatformLayer.h"
#include <X11/Xlib.h>

class LinuxPlatformLayer : public PlatformLayer {
public:
    static LinuxPlatformLayer& getInstance() {
        static LinuxPlatformLayer instance;
        return instance;
    }
    LinuxPlatformLayer();
    ~LinuxPlatformLayer() override;
    void createWindow(const char* title, int minWidth, int minHeight, int width, int height) override;
    std::vector<Event*> handleInput() override;
    void render() override;
    void shutdown() override;
    void drawRectangle(int x, int y, int width, int height) override;

private:
    Display* display;
    Window window{};
public:
    LinuxPlatformLayer& operator=(const LinuxPlatformLayer&) = delete;
    LinuxPlatformLayer(const LinuxPlatformLayer&) = delete;
};

#endif // LINUXPLATFORM_H
