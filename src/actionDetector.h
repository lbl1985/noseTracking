#pragma once

#include <ntk/utils/opencv_utils.h>
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

	void set_coolDownThreshold(double a);
	double view_coolDownThreshold();
	void set_coolDownConNum(int a);
	int view_coolDownConNum();

	actionDetector(void);
	~actionDetector(void);
private:
	// Movement less than the coolDownThreshold to be one cooldown point
	double coolDownThreshold;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	int coolDownConNum;

};
