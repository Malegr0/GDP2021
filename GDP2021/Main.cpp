#include <Windows.h>
#include "Window.h"

int WINAPI WinMain(
    HINSTANCE hInstance,        //handle to our application instance (referencing a resource, like a pointer but it isn't always)
    HINSTANCE hPrevInstance,    // deprecated
    LPTSTR szCmdLine,            // caommand line
    INT nCMDShow                // how to present the window
)
{
    INT error = 0;
    INT width = 1024;
    INT height = 768;

    // 1. create a window
    Window wnd = { };
    error = wnd.init(hInstance, width, height, nCMDShow);

    //run phase
    wnd.run();

    //tidy up
    wnd.deInit();

    return 0;
}