#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Utils.h"
#include "Camera.h"
#include <random>
#include "Time.h"
#include "Material.h"
#include "Light.h"

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
    CheckError(error);

    // 2. create Direct3D connection
    D3D d3d = {};
    error = d3d.init(wnd.getWindowHandle(), width, height, isFullscreen);
    CheckError(error);

    //d3d.getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); // solid, wireframe, point
    //d3d.getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //d3d.getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
    //d3d.getDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

    // 3. create Mesh
    Mesh mesh = {};
    error = mesh.init(d3d.getDevice());
    CheckError(error);

    // 4. create camera
    Camera camera = {};
    error = camera.init(width, height);
    CheckError(error);

    // 5. create time
    Time time = {};
    error = time.init();
    CheckError(error);

    // 6. create material
    Material material = {};
    error = material.init(d3d.getDevice(), TEXT("wall.jpg"));
    CheckError(error);

    //// 7. create light
    //Light light = {};
    //D3DLIGHT9 lightData = {};
    //lightData.Type = D3DLIGHT_DIRECTIONAL;
    //lightData.Direction = { -1.0f, -1.0, 1.0f };
    //lightData.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
    //lightData.Diffuse = { 0.6f, 0.6f, 0.6f, 1.0f };
    //lightData.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
    //error = light.init(lightData);
    //CheckError(error);

    //run phase
    while (wnd.run())
    {
        // update objects
        time.update();
        camera.update(time.getDeltaTime());
        mesh.update(time.getDeltaTime());

        // draw objects
        // random colors
        //static std::default_random_engine e;
        //static std::uniform_int_distribution<int> d(0, 255);
        //d3d.beginScene(D3DCOLOR_XRGB(d(e), d(e), d(e)));

        d3d.beginScene(0.0f, 0.0f, 0.0f);

        material.render(d3d.getDeviceContext(), mesh.getWorldMatrix(), camera.getViewMatrix(), camera.getProjectionMatrix());
        //light.render(d3d.getDevice());
        mesh.render(d3d.getDeviceContext());

        d3d.endScene();
    }

    //tidy up
    //light.deInit();
    material.deInit();
    time.deInit();
    camera.deInit();
    mesh.deInit();
    d3d.deInit();
    wnd.deInit();

    return 0;
}