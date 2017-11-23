///////////////////////////////////////////////////////////////////////////////
// Filename: FPSTracker.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FPSTracker.h"


FPSTracker::FPSTracker()
{
}


FPSTracker::FPSTracker(const FPSTracker& other)
{
}


FPSTracker::~FPSTracker()
{
}


void FPSTracker::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return;
}


void FPSTracker::Frame()
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTime = timeGetTime();
	}
}


int FPSTracker::GetFps()
{
	return m_fps;
}