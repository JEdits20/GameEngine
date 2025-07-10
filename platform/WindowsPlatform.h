#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include "PlatformLayer.h"
#include <windows.h>
#include <vector>

class WindowsPlatformLayer : public PlatformLayer {
public:
    WindowsPlatformLayer();
    ~WindowsPlatformLayer();

    void CreateWindow(const char* title, int minWidth, int minHeight, int width, int height) override;
    std::vector<Event*>& HandleInput() override;
    void Render() override;
    void Shutdown() override;
    void DrawRectangle(int x, int y, int width, int height) override;

private:
    HWND hwnd;
    HDC hdc;
    bool isRunning;
};

#endif //WINDOWSPLATFORM_H
