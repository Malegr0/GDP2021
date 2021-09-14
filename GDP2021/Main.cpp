#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"

int WINAPI WinMain(
    HINSTANCE hInstance,        //handle to our application instance (referencing a resource, like a pointer but it isn't always)
    HINSTANCE hPrevInstance,    // deprecated
    PSTR szCmdLine,            // command line
    INT nCMDShow                // how to present the window
)
{
    INT error = 0;
    INT width = 1024;
    INT height = 768;
    BOOL isFullscreen = false;

    // 1. create a window
    Window wnd = { };
    error = wnd.init(hInstance, width, height, nCMDShow);
    if (error != 0) return error;
    CheckError(error);

    // 2. create Direct3D connection
    D3D d3d = {};
    error = d3d.init(wnd.getWindowHandle(), width, height, isFullscreen);
    CheckError(error);

    //run phase
    while (wnd.run())
    {
        d3d.beginScene(D3DCOLOR_XRGB(255, 0, 0));
        d3d.endScene();
        Sleep(10);
    }

    //tidy up
    wnd.deInit();

    return 0;
}