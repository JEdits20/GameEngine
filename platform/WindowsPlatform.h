#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include "PlatformLayer.h"
#include <windows.h>
#include <vector>

class WindowsPlatformLayer : public PlatformLayer {
public:
    static WindowsPlatformLayer& getInstance() {
        static WindowsPlatformLayer instance;
        return instance;
    }
    WindowsPlatformLayer& operator=(const WindowsPlatformLayer&) = delete;
    WindowsPlatformLayer(const WindowsPlatformLayer&) = delete;

    WindowsPlatformLayer();
    ~WindowsPlatformLayer();

    void createWindow(const char* title, int minWidth, int minHeight, int width, int height) override;
    std::vector<std::unique_ptr<Event>>& handleInput() override;
    void pushEvent(const std::unique_ptr<Event> &event);
    void render() override;
    void shutdown() override;
    void drawRectangle(int x, int y, int width, int height) override;

private:
    HWND hwnd;
    HDC hdc;
};

#endif //WINDOWSPLATFORM_H
