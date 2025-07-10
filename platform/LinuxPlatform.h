#ifndef LINUXPLATFORM_H
#define LINUXPLATFORM_H

#include <X11/Xlib.h>
#include "PlatformLayer.h"

class LinuxPlatformLayer : public PlatformLayer {
public:
    LinuxPlatformLayer();

    void createWindow(const char* title, int minWidth, int minHeight, int width, int height) override;
    std::vector<Event*>& handleInput() override;
    void render() override;
    void shutdown() override;
    void drawRectangle(int x, int y, int width, int height) override;

private:
    ~LinuxPlatformLayer() override;
    Display* display;
    Window window{};
public:
    LinuxPlatformLayer& operator=(const LinuxPlatformLayer&) = delete;
    LinuxPlatformLayer(const LinuxPlatformLayer&) = delete;
};

#endif // LINUXPLATFORM_H
