#include "Time.h"
#include <string>

INT Time::init()
{
    _lastTimestamp = chrono::high_resolution_clock::now();

    return 0;
}

void Time::update()
{
    time_point now = chrono::high_resolution_clock::now();
    chrono::duration<float> diff = now - _lastTimestamp;
    _deltaTime = diff.count();
    _totalTime += _deltaTime;
    _lastTimestamp = now;

    _fpsCount++;
    _fpsTime += _deltaTime;

#if _DEBUG
#if UNICODE
    wstring output = (TEXT("deltaTime: ") + to_wstring(_deltaTime) + TEXT(" s\n"));
#else // UNICODE
    string output = (TEXT("deltaTime: ") + to_string(_deltaTime) + TEXT(" s\n"));
#endif // UNICODE
    OutputDebugString(output.c_str());

    if (_fpsTime >= 1.0f)
    {
#if UNICODE
        output = (TEXT("fps: ") + to_wstring(_fpsCount) + TEXT("\n"));
#else // UNICODE
        output = (TEXT("fps: ") + to_string(_fpsCount) + TEXT("\n"));
#endif // UNICODE
        OutputDebugString(output.c_str());

        _fpsCount = 0;
        _fpsTime -= 1.0f;
    }
#endif // _DEBUG


}

void Time::deInit()
{
}
