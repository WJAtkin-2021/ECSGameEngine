#include <Windows.h>
#include "Time.h"

Time* Time::m_instance = nullptr;

Time::Time()
{
	// Init the variables in this class
	m_secondsPerCount = 0.0;
	m_deltaTime = -1.0;
	m_prevTime = 0;
	m_instance = this;

	// Query the frequency of the performance counter
	__int64 countsPerSec;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

Time::~Time() { }

void Time::Start()
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	// Previous time is not valid so reset this
	m_prevTime = startTime;
}

void Time::TickFrameTime()
{
	// Get the time this frame
	__int64 currTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

	// Calculate the delta time
	m_deltaTime = (currTime - m_prevTime) * m_secondsPerCount;

	// Prep for the next delta time calculation
	m_prevTime = currTime;

	// Force a non negative on the delta time calculation, if the CPU
	// goes into sleep mode or if we get our thread moved to another physical
	// core m_DeltaTime could be negative
	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}