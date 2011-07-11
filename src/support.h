#include <ntk/utils/opencv_utils.h>
#include <ntk/camera/nite_rgbd_grabber.h>

#include "BlobResult.h"

using namespace cv;
using namespace ntk;

double pointDistance(Point a, Point b);
Point assignPoint(list<Point>::iterator iter);
// Face depth threshold Segmentation Function
float thresholdSegmentation(Rect r, ntk::RGBDImage* current_frame, Mat& dst);