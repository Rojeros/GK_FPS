#pragma once
#include <iostream>
#include <ctime>
#include <deque>
#include <string>


/// <summary>	The FPS timer. </summary>
class FpsTimer
{
private:
	/// <summary>	List of times of the last frames. </summary>
	std::deque<float> *lastFrameTimes;

	/// <summary>	Gets the temporary time. </summary>
	///
	/// <value>	The temporary time. </value>

	time_t lastFrame, tempTime;
	/// <summary>	The FPS string. </summary>
	std::string fpsString;
	/// <summary>	The average of frames. </summary>
	int averageOfFrames;
	/// <summary>	The frames to update. </summary>
	int framesToUpdate;
	/// <summary>	The average FPS. </summary>
	float averageFps;
public:

	/// <summary>	Constructor. </summary>
	///
	/// <param name="averageOfFrames">	The average of frames. </param>

	FpsTimer(int averageOfFrames);
	/// <summary>	Time frame. </summary>
	void timeFrame();

	/// <summary>	Gets the FPS. </summary>
	///
	/// <returns>	The FPS. </returns>

	std::string getFps();
};
