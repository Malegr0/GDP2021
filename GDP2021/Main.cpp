#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Utils.h"
#include "Camera.h"
#include <random>

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

    d3d.getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); // solid, wireframe, point
    d3d.getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    d3d.getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

    // 3. create Mesh
    Mesh mesh = {};
    error = mesh.init(d3d.getDevice());
    CheckError(error);

    // 4. create camera
    Camera camera = {};
    error = camera.init(width, height);
    CheckError(error);

    //run phase
    while (wnd.run())
    {
        // update objects
        mesh.update(0.0f);


        // draw objects
        // random colors
        //static std::default_random_engine e;
        //static std::uniform_int_distribution<int> d(0, 255);
        //d3d.beginScene(D3DCOLOR_XRGB(d(e), d(e), d(e)));

        d3d.beginScene(D3DCOLOR_XRGB(0, 0, 0));

        camera.render(d3d.getDevice());
        mesh.render(d3d.getDevice());

        d3d.endScene();
        //Sleep(50);
    }

    //tidy up
    mesh.deInit();
    d3d.deInit();
    wnd.deInit();

    return 0;
}