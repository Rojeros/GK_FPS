#pragma once
#include <iostream>
#include <ctime>
#include <deque>
#include <string>


class FpsTimer
{
private:
	std::deque<float> *lastFrameTimes;
	time_t lastFrame, tempTime;
	std::string fpsString;
	int averageOfFrames;
	int framesToUpdate;
	float averageFps;
public:
	FpsTimer(int averageOfFrames);
	void timeFrame();
	std::string getFps();
};
