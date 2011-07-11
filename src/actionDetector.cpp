#include "actionDetector.h"
#include <numeric>

void actionDetector::setCoolDownThreshold(double sourceCoolDownThreshold){
	this->coolDownThreshold = sourceCoolDownThreshold;}

double actionDetector::getCoolDownThreshold(){
	return (this->coolDownThreshold);}

void actionDetector::setCoolDownConNum(int sourceCoolDownConNum){
	this->coolDownConNum = sourceCoolDownConNum;}

int actionDetector::getCoolDownConNum(){
	return(this->coolDownConNum);}

void actionDetector::setHeadOrientation(float sourceHeadOrientation){
	this->headOrientation = sourceHeadOrientation;	}

float actionDetector::getHeadOrientation(){
	return(this->headOrientation);}

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



void actionDetector::coolDownDetect(std::list<Point> m_History, Point initPoint)
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

double actionDetector::swipeDetect(){
	double headSwipeFlag;
	if (abs(headOrientation) > 15){
		if (headOrientation > 0)
			headSwipeFlag = 1;
		else
			headSwipeFlag = -1;
	}
	else
		headSwipeFlag = 0;
	return (headSwipeFlag);
}

actionDetector::actionDetector(void)
{
	// Movement less than the coolDownThreshold to be one cooldown point
	coolDownThreshold = 15;
	// How many Consecutive Frames moving less than threshold to decide as cooldown
	coolDownConNum = 10;

	headOrientation = 0;
}

actionDetector::~actionDetector(void)
{
}
