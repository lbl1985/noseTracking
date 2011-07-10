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
void thresholdSegmentation(Rect r, ntk::RGBDImage* current_frame, Mat& dst){
	Mat depth = current_frame->depth();
	Rect& rr = r;
	Mat depthROI = depth(rr), maskROI;
	Mat& rDepthROI = depthROI, &rMaskROI = maskROI;
	double var = 0.3;

	// maskROI for nonZero values in the Face Region
	inRange(depthROI, Scalar::all(0.001), Scalar::all(255), maskROI);
	// Mean depth of Face Region
	Scalar mFace = cv::mean(rDepthROI, rMaskROI);
	//mFace[0]  = mFace[0] - mFace[0] * var;
	inRange(depthROI, Scalar::all(0.001), mFace, maskROI);
	mFace = cv::mean(rDepthROI, rMaskROI);
	//inRange(depthROI, Scalar::all(0.001), mFace, maskROI);
	//mFace = cv::mean(rDepthROI, rMaskROI);
	


	
	// Mask for nearer than the mean of face.
	inRange(depth, Scalar::all(0.001), mFace, dst);
	Mat rgbImage = current_frame->rgb();
	Mat outFrame = cvCreateMat(rgbImage.rows, rgbImage.cols, CV_32FC3);
	rgbImage.copyTo(outFrame, dst);
	Mat outFrameROI;
	outFrameROI = outFrame(rr);
	//cvCopy(&rgbImage, &outFrame, &dst);
	//rgbImageROI = rgbImageROI(rr);
	
	imshow("ROI", outFrameROI);
	//imshow("thresholdSeg", dst);

	// For debug of cvblobslib
	// Display the color image	

	imshow("faceRIO", maskROI);
	bool iswrite;
	const int nchannel = 1;
	vector<Rect> faces;
	iswrite = imwrite("faceROI.png", maskROI);
	//iswrite = cvSaveImage("faceROI.jpeg", pOutFrame, &nchannel);

	// ---- blob segmentation on maskROI by using cvblobslib ----
	// ---		Third Trial	---
	//visualizeBlobs("faceROI.png", "faceRIO");




	// ---		First Trial Not Successful		---
	//Mat maskROIThr=cvCreateMat(maskROI.rows, maskROI.cols, CV_8UC1);	
	//maskROIThr = maskROI;
	//IplImage imgMaskROIThr = maskROIThr;
	//IplImage* pImgMaskROIThr = &imgMaskROIThr;
	//cvThreshold(pImgMaskROIThr, pImgMaskROIThr, 0.1, 255, CV_THRESH_BINARY_INV);

	// ---		Second Trial	---
	IplImage* original = cvLoadImage("faceROI.png", 0);
	IplImage* originalThr = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 1);
	IplImage* displayBiggestBlob = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 3);
	CBlobResult blobs;
	CBlob biggestBlob;
	//IplImage source = maskROIThr;	IplImage* pSource = &source;
	//blobs = CBlobResult(
	cvThreshold(original, originalThr, 0.1, 255, CV_THRESH_BINARY_INV);
	blobs =  CBlobResult( originalThr, NULL, 255);
	printf("%d blobs \n", blobs.GetNumBlobs());
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
	
	cv::imshow("faceRIO", mat);

	

}

