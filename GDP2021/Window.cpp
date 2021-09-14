#include "Window.h"

LRESULT CALLBACK WndProc(
    HWND hWnd,  // handle to window isntance this message is sent to
    UINT msg,   // message number
    WPARAM wParam,  // important message property (main message property)(e.g. which key got pressed)
    LPARAM lParam   // additional message properties (e.g. which key got pressed -> repeat count, value...)
)
{
    switch (msg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);    //everytime there happens something (moving the mouse, window...
    }
    return 0;
}

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
    wc.lpfnWndProc = WndProc;   //long pointer function
                                // pointer to communication function (short Window Procedure)

    // 2. register window class
    if (!RegisterClass(&wc)) return 10;

    // 3. calculate window size (optional)


    // 4. create window instance
    _hWnd = CreateWindow(
        wc.lpszClassName,   // window class name a window should be created from
        wc.lpszClassName,   // window title
        WS_OVERLAPPEDWINDOW,    // window visual style
        100, 100,   // window position (left-top corner)
        width, height,  // window size
        nullptr,    // handle to parent window
        nullptr,    // handle to menu object
        hInstance,
        nullptr     // optional parameters
    );

    if (!_hWnd) return 15;

    // 5. show window
    ShowWindow(_hWnd, nCMDShow);    // put window to front
    SetFocus(_hWnd);    // set keyboard focus to window

    return 0;
}

bool Window::run()
{
    static MSG msg = {};
    if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE)) // PeekMessage takes last message of the message queue // take next message from message queue and remove
    {
        TranslateMessage(&msg); // translating keyboard information into a virtual keyboard table
        DispatchMessage(&msg);  // send message to window procedure
    }
    return msg.message != WM_QUIT;
}

void Window::deInit()
{
}