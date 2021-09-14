#pragma once
#include <Windows.h>

class Window
{
public:
    INT init(HINSTANCE hInstance, INT width, INT height, INT nCMDShow);
    bool run();
    void deInit();

    HWND getWindowHandle() { return _hWnd; }

private:
    HWND _hWnd = nullptr;    // handle to window instance
};