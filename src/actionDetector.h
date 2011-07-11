#pragma once

#include <ntk/utils/opencv_utils.h>
// For abs function
#include <cmath>
#include "support.h"

using namespace cv;

class actionDetector
{
public:
	// Comparing between the current and before Point
	void coolDownDetect(std::list<Point>);
	Point coolDownDetect(std::list<Point>, bool isPoint);
	// Comparing between the current and the initPoint.
	void coolDownDetect(std::list<Point>, Point initPoint);

	double swipeDetect();

	void setCoolDownThreshold(double a);
	double getCoolDownThreshold();
	void setCoolDownConNum(int a);
	int getCoolDownConNum();
	void setHeadOrientation(float sourceHeadOrientation);
	float getHeadOrientation();

	actionDetector(void);
	~actionDetector(void);
private:
	// Movement less than the coolDownThreshold to be one cooldown point
	double coolDownThreshold;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	int coolDownConNum;
	// Head Orientation from thresholdSegmentation
	float headOrientation;

};
