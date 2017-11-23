#pragma once

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class FPSTracker
{
public:
	FPSTracker();
	FPSTracker(const FPSTracker&);
	~FPSTracker();

	void Initialize();
	void Frame();
	int GetFps();

private:
	int m_fps, m_count;
	unsigned long m_startTime;
};
