#pragma once
#include <Windows.h>
#include <chrono>

using namespace std;

#define TIMEPOINT chrono::high_resolution_clock::time_point
typedef chrono::high_resolution_clock::time_point time_point;

class Time
{
public:
	INT init();
	void update();
	void deInit();

	FLOAT getDeltaTime() { return _deltaTime; }

private:
	time_point _lastTimestamp = {}; // timestamp of the last frame
	FLOAT _deltaTime = 0.0f;		// time between two frames
	FLOAT _totalTime = 0.0f;		// total time since application startup
	INT _fpsCount = 0;				// frames since last update
	FLOAT _fpsTime = 0.0f;			// time since last frame update
};
