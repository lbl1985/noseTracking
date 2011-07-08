#include "actionDetector.h"

void actionDetector::set_coolDownThreshold(double a)
{
	coolDownThreshold = a;
}
double actionDetector::view_coolDownThreshold()
{
	return (coolDownThreshold);
}

void actionDetector::set_coolDownConNum(int a)
{
	coolDownConNum = a;
}
int actionDetector::view_coolDownConNum()
{
	return(coolDownConNum);
}

void actionDetector::coolDownDetect(std::list<Point> m_History)
{
	// coolDownDetect only operate when m_History.size() >= 15
	//if (m_History.size() < 15)
		//printf("coolDownDetect should not be operated when m_History.size() < 15);
	int m_HistorySize = m_History.size();
	std::list<bool> isMove;
	std::list<bool>::iterator iter_isMove = isMove.begin();
	for (std::list<Point>::iterator iter_m_History = m_History.begin(); iter_m_History != m_History.end(); iter_m_History++)
	{
	}

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
