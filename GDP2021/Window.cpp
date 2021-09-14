#include "Window.h"

INT Window::init(HINSTANCE hInstance, INT width, INT height, INT nCMDShow)
{
    // 1. describe the windwo class
    WNDCLASS wc = {};
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 255));

    // 2. register window class

    // 3. calculate window size (optional)

    // 4. create window instance

    // 5. show window


    return 0;
}

bool Window::run()
{
    return false;
}

void Window::deInit()
{
}