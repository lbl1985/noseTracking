#include "actionDetector.h"
#include <numeric>

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
	// coolDownDetect only operate when m_History.size() >= coolDownConNum + 1 (need coolDownConNum distance less than the coolDownThreshold
	//if (m_History.size() < coolDownConNum + 1)
	//	printf("coolDownDetect should not be operated when m_History.size() < 15);
	int m_HistorySize = m_History.size();
	std::list<int> isMove;
	std::list<int>::iterator iter_isMove = isMove.begin();
	Point current, before;
	double distance;
	// count to control how many consecutive points we really need
	int count = 0;
	// isCoolDown Default is false.
	bool isCoolDown = false;
	std::list<Point>::iterator iter_before;
	for (std::list<Point>::iterator iter_m_History = m_History.begin(); count < coolDownConNum; iter_m_History++)
	{
		iter_before = iter_m_History;	iter_before++;
		current = assignPoint(iter_m_History);
		before  = assignPoint(iter_before);
		distance = pointDistance(current, before);
		if (distance < coolDownThreshold)
			isMove.push_front(1);
		else
			isMove.push_front(0);
		count++;
	}
	int sumList = std::accumulate(isMove.begin(), isMove.end(), 0);
	if (sumList == coolDownConNum){	
		isCoolDown = true;
		printf("Cool Down Detected");}
}



void coolDownDetect(std::list<Point>, Point initPoint)
{
	// coolDownDetect only operate when m_History.size() >= coolDownConNum + 1 (need coolDownConNum distance less than the coolDownThreshold
	//if (m_History.size() < coolDownConNum + 1)
	//	printf("coolDownDetect should not be operated when m_History.size() < 15);
	int m_HistorySize = m_History.size();
	std::list<int> isMove;
	std::list<int>::iterator iter_isMove = isMove.begin();
	Point current, before;
	double distance;
	// count to control how many consecutive points we really need
	int count = 0;
	// isCoolDown Default is false.
	bool isCoolDown = false;
	
	for (std::list<Point>::iterator iter_m_History = m_History.begin(); count < coolDownConNum; iter_m_History++)
	{		
		current = assignPoint(iter_m_History);		
		distance = pointDistance(current, initPoint);
		if (distance < coolDownThreshold)
			isMove.push_front(1);
		else
			isMove.push_front(0);
		count++;
	}
	int sumList = std::accumulate(isMove.begin(), isMove.end(), 0);
	if (sumList == coolDownConNum){	
		isCoolDown = true;
		printf("Cool Down Detected");}

}
actionDetector::actionDetector(void)
{
	// Movement less than the coolDownThreshold to be one cooldown point
	coolDownThreshold = 3;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	coolDownConNum = 15;
}

actionDetector::~actionDetector(void)
{
}
