#pragma once

class Time
{
public:

	Time();
	~Time();

	static float DeltaTime() { return static_cast<float>(m_instance->m_deltaTime); }

	void Start();
	void TickFrameTime();

private:

	static Time* m_instance;

	// Number of counts the performance timer makes a second
	double m_secondsPerCount;

	// Frame delta
	double m_deltaTime;
	__int64 m_prevTime;
};