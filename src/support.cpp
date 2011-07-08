#include "support.h"

double pointDistance(Point tempPoint, Point nosePoint)
{
	double diff, xdiff, ydiff;
	xdiff = tempPoint.x - nosePoint.x;
	ydiff = tempPoint.y - nosePoint.y;
	diff = sqrt(xdiff * xdiff + ydiff * ydiff);	
	//printf("diff is: %f \n", diff);
	return (diff);
}

Point assignPoint(list<Point>::iterator iter)
{
	Point target;
	target.x = iter->x;
	target.y = iter->y;
	return(target);
}