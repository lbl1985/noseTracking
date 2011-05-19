// Only for visualize and check purpose
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <conio.h>

// Main blob library include
#include "BlobResult.h"

using namespace cv;
using namespace std;

void visualizeBlobs(const char* fileName, const char* figName){
	IplImage* original = cvLoadImage(fileName, 0);
	IplImage* originalThr = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 1);
	IplImage* displayBiggestBlob = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 1);
	CBlobResult blobs;
	CBlob biggestBlob;
	//IplImage source = maskROIThr;	IplImage* pSource = &source;
	blobs =  CBlobResult( originalThr, NULL, 1 );;
	blobs.GetNthBlob(CBlobGetArea(), 0, biggestBlob);
	biggestBlob.FillBlob(displayBiggestBlob, CV_RGB(255, 0, 0));

	// Drawing the eclipse and Rect on the blob
	Mat mat(displayBiggestBlob);

	cv::RotatedRect blobEllipseContour;
	cv::Rect blobRectContour;
	//RotatedRect blobEllipseContour;
	blobEllipseContour = biggestBlob.GetEllipse();
	blobRectContour = biggestBlob.GetBoundingBox();
	//cv::ellipse(
	cv::ellipse(mat, blobEllipseContour, cv::Scalar(0,255, 0), 3, CV_AA);
	cv::rectangle(mat, blobRectContour, cv::Scalar(255, 0, 0), 3, CV_AA);
	//cv::ellipse(mat, blobEllipseContour);
	
	cv::imshow(figName, mat);
}