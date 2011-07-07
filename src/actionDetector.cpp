#include "actionDetector.h"


void actionDetector::coolDownDetect(std::list<Point> m_History)
{
	// coolDownDetect only operate when m_History.size() >= 15
	//if (m_History.size() < 15)
		//printf("coolDownDetect should not be operated when m_History.size() < 15);
}



actionDetector::actionDetector(void)
{
	// Movement less than the coolDownThreshold to be one cooldown point
	coolDownThreshold = 15;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	coolDownConNum = 10;
}

actionDetector::~actionDetector(void)
{
}
