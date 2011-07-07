#pragma once

#include <ntk/utils/opencv_utils.h>

using namespace cv;

class actionDetector
{
public:
	void coolDownDetect(std::list<Point>);
	Point coolDownDetect(std::list<Point>, bool isPoint);
	actionDetector(void);
	~actionDetector(void);
private:
	// Movement less than the coolDownThreshold to be one cooldown point
	double coolDownThreshold;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	int coolDownConNum;

};
