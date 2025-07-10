#ifdef _WIN32
#include <windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static std::vector<Event*> events;

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
        Game::getInstance().handleEvent(*e);
        delete event;
    }

    return 0;
}
#endif