#include "Window.h"

INT Window::init(HINSTANCE hInstance, INT width, INT height, INT nCMDShow)
{
    // 1. describe the windwo class
    WNDCLASS wc = {};
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 255));  //handle to brush (background color)
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    // handle to cursor icon
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);  // handle to application icon
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // if window is changed horizontal or vertical then we force a redraw of the whole project, (pipe is a bit-or-gate)
                                                    // not visual style, but how windows is using this window or simple window instance properties
    wc.lpszClassName = TEXT("Direct3D 9");

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