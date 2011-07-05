#include <string>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include <ntk/camera/kinect_grabber.h>
#include <ntk/camera/nite_rgbd_grabber.h>
#include <ntk/camera/rgbd_processor.h>
#include <ntk/utils/opencv_utils.h>

#include <ntk/mesh/mesh_generator.h>
#include <ntk/mesh/surfels_rgbd_modeler.h>
#include <ntk/mesh/mesh_viewer.h>
#include "GuiController.h"
#include "ObjectDetector.h"

#include "BlobResult.h"
//#include "blobs.h"

#include <QApplication>
#include <QMetaType>

using namespace ntk;
using namespace cv;
using namespace std;

// Create memory for calculations
static CvMemStorage* storage = 0;

// Control QT and detection
bool QT = false;
bool Detection = true;
bool isTracking = false;
// Create a new Haar classifier
//static CvHaarClassifierCascade* cascade = 0;
//static CvHaarClassifierCascade* nestedCascade = 0;

// Create a string that contains the cascade name
string cascade_name = "haarcascade_frontalface_alt.xml";
string nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";

// Face Tracking Declearations
Mat image;
bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;

int vmin = 10, vmax = 256, smin = 92;

// Nose Tracking Declearations
Mat imageNose;
int trackObjectNose = 0;
Point originNose;
Rect selectionNose;
int vminNose = 10, vmaxNose = 256, sminNose = 92;
// Nose movement maximum distance.
double diffThreshold = 100;

// Function prototype for detecting and drawing an object from an image
vector<Rect> detectAndDraw( Mat& img,
						   CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
						   double scale);
// Function for visualize the depth images with facial detection region
void depthAndDraw(Mat& img, vector<Rect> faces);

// Nose Tracking region selection
Rect noseRegion(Rect TrackingRegion, ntk::RGBDImage* current_frame);
Point noseRegion(Rect TrackingRegion, ntk::RGBDImage* current_frame, bool isPoint);

// Nose Location History Function


// Force rect in image bound
Rect checkRect(Rect r, CvSize siz);

// Simple threshold Segmentation Function
void thresholdSegmentation(Rect r, ntk::RGBDImage* current_frame, Mat& dst);

// Calculate the mean
Point meanPoint(std::list<Point> history);

// Smooth the trajectory by Gaussian Smooth
std::list<Point> trajGaussianSmooth(std::list<Point> history, double sigma1);

int main(int argc, char** argv)
{
	// QT UI Varables
	QApplication::setGraphicsSystem("raster");
	QApplication app (argc, argv);
	
	// ---- Facial Detection Initialization ----
	CascadeClassifier cascade, nestedCascade;
	//cascade = (CvHaarClassifierCascade&)cvLoad(cascade_name, 0, 0, 0);
	//nestedCascade = (CvHaarClassifierCascade&)cvLoad(nestedCascadeName, 0, 0, 0);
	cascade.load(cascade_name);
	nestedCascade.load(nestedCascadeName);
	storage = cvCreateMemStorage(0);

	// ---- Face Tracking Declearations ----
	Rect trackWindow;
	RotatedRect trackBox;
	int hsize = 16;
	int faceDetectionCount = 0;
	float hranges[] = {0,180};
    const float* phranges = hranges;
	Mat hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;

	// ---- Nose Tracking Declearations ----
	Rect faceTrackWindow;
	Rect nose;
	Point nosePoint;
	bool isPoint = true;
	
	Rect trackWindowNose;
	RotatedRect trackBoxNose;
	int hsizeNose = 16;
	float hrangesNose[] = {0,180};
    const float* phrangesNose = hrangesNose;
	Mat hsvNose, hueNose, maskNose, histNose, histimgNose = Mat::zeros(200, 320, CV_8UC3), backprojNose;

	// ---- Cursory Tracking based on Nose Tracking Declearations ----
	std::list<Point> m_History;
	int m_nHistorySize = 20;	// Max Size of Point History
	Point goldPoint;			// gold base point of the nose
	double sigma1 = 0.2;
	// ---- Depth threshold segmentation	 Declearations ----		
	Mat odst; Mat& dst = odst;

	// ---- Images Saving Section ----
	string imgPath = "C:\CProjects\Kinect_OpenNI\RGBDemo-0.5.0-Source\RGBDemo-0.5.0-Source\mysuperdemo\imgPath";
	string filename;

	// OpenCV Save an Video
	CvVideoWriter *writer = 0;
	int isColor = 1;
	int fps = 30;
	int frameW = 640;
	int frameH = 480;
	writer = cvCreateVideoWriter("out.avi", CV_FOURCC('I', '4', '2', '0'), fps, cvSize(frameW, frameH), isColor);

	/*KinectGrabber grabber;*/
	ntk::NiteRGBDGrabber* k_grabber = new NiteRGBDGrabber();
	ntk::RGBDGrabber* grabber = 0;
	//k_grabber->setHighRgbResolution(true);
	k_grabber->initialize();	
	grabber = k_grabber;
	

	// Postprocess raw kinect data.
	// Tell the processor to transform raw depth into meters using baseline-offset technique.
	ntk::NiteProcessor processor;
	processor.setFilterFlag(RGBDProcessor::ComputeKinectDepthBaseline, true);
	

	// ---- MeshGenerator Functionality ----
	ntk::MeshGenerator* mesh_generator = 0;
	ntk::MeshViewer* mesh_view;
	ntk::RGBDCalibration* calib_data = 0;

	calib_data = new RGBDCalibration();
	calib_data = grabber->calibrationData();
	if (calib_data)
	{
		mesh_generator = new MeshGenerator();
		grabber->setCalibrationData(*calib_data);
	}	

	// m_processor for mesh_viewer
	ntk::NiteProcessor* m_processor = 0;
	m_processor = new ntk::NiteProcessor();
	
	
	GuiController gui_controller (*grabber, *m_processor);
	if(QT)
	{		
		grabber->addEventListener(&gui_controller);
	}


	if (mesh_generator)
	{
		mesh_generator->setUseColor(true);
		if(QT)
			gui_controller.setMeshGenerator(*mesh_generator);
	}

	// ---- OpenCV windows ----
	if(!QT)
	{
		namedWindow("color");
		namedWindow("depth");
		namedWindow("depth_as_color");
		namedWindow("result");
		namedWindow("ROI");
		namedWindow("depthDraw");
		namedWindow( "Histogram", 1 );
		namedWindow( "CamShift Demo", 1 );
		namedWindow("debug", 1);
		namedWindow("faceROI", 1);
		namedWindow("noseROI", 1);
		namedWindow("thresholdSeg", 1);
		//setMouseCallback( "CamShift Demo", onMouse, 0 );
		createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );
		createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );
		createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );
	}

	
	
	
	// Current image. An RGBDImage stores rgb and depth data.
	ntk::RGBDImage current_frame;
	ntk::RGBDImage last_frame;

	grabber->start();	

	if (QT)
		app.exec();

	while (true)
	{
		// ---- Images Grabber Section ----
		grabber->waitForNextFrame();
		grabber->copyImageTo(current_frame);
		processor.processImage(current_frame);	

		// Show the frames per second of the grabber
		int fps = grabber->frameRate();
		cv::putText(current_frame.rgbRef(),
			cv::format("%d fps", fps),
			Point(10,20), 0, 0.5, Scalar(255,0,0,255));

		// Display the color image	
		IplImage SaveImg = current_frame.rgb();
		IplImage* pSaveImg = &SaveImg;

		imshow("color", pSaveImg);
		bool iswrite;
		const int nchannel = 3;
		vector<Rect> faces;
		iswrite = cvSaveImage("test.jpeg", pSaveImg, &nchannel);		
		if(!iswrite) printf("Could not save\n");
		cvWriteFrame(writer, pSaveImg);
		
		// ---- Facial Detection Section ----
		if (Detection)
		{
			cv::Mat frame_copy = current_frame.rgb();
			cv::Mat& rframe_copy = frame_copy;
			faces = detectAndDraw(rframe_copy, cascade, nestedCascade, 1);			
		}


		// Show the depth image as normalized gray scale
		imshow_normalized("depth", current_frame.depth());

		// Compute color encoded depth.
		cv::Mat3b depth_as_color;
		compute_color_encoded_depth(current_frame.depth(), depth_as_color);
		imshow("depth_as_color", depth_as_color);

		if (Detection)
		{
			depthAndDraw(depth_as_color, faces);
		}

		// ---- Face Tracking Section ----
		// If face detected. No detection required any further.
		
		if (!faces.empty())	
		//if (false)	
		{
			if(faceDetectionCount < 3)
			{
				Detection = false;	isTracking = true;	faceDetectionCount++;
			}
			else
			{
				faceDetectionCount = 0;
				Detection = true;	isTracking = false;
			}
			// Face Tracking Starts here
			for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
			{
				selection.x = r->x;
				selection.y = r->y;
				selection.height = r->height;
				selection.width  = r->width;				
			}

			
			thresholdSegmentation(selection, &current_frame, dst);
			
		}

		if (isTracking)
		{
			image = current_frame.rgb();
			cv::Mat& rimage = image;
			cvtColor(rimage, hsv, CV_BGR2HSV);
			imshow("debug", image);

			if (trackObject)
			{
				int _vmin = vmin, _vmax = vmax;

				inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
					Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = {0, 0};
				hue.create(hsv.size(), hsv.depth());
				mixChannels(&hsv, 1, &hue, 1, ch, 1);

				imshow( "debug", image );

				if( trackObject < 0 )
				{
					Mat roi(hue, selection), maskroi(mask, selection);
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
					normalize(hist, hist, 0, 255, CV_MINMAX);

					trackWindow = selection;
					trackObject = 1;

					histimg = Scalar::all(0);
					int binW = histimg.cols / hsize;
					Mat buf(1, hsize, CV_8UC3);
					for( int i = 0; i < hsize; i++ )
						buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
					cvtColor(buf, buf, CV_HSV2BGR);

					for( int i = 0; i < hsize; i++ )
					{
						int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
						rectangle( histimg, Point(i*binW,histimg.rows),
							Point((i+1)*binW,histimg.rows - val),
							Scalar(buf.at<Vec3b>(i)), -1, 8 );
					}

					
				}

				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				backproj &= mask;
				RotatedRect trackBox = CamShift(backproj, trackWindow,
					TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));				
				
				faceTrackWindow = trackBox.boundingRect();
				faceTrackWindow = checkRect(faceTrackWindow, cvGetSize(pSaveImg));
				
				imshow( "debug", image );

				if( backprojMode )
					cvtColor( backproj, image, CV_GRAY2BGR );
				ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );

				imshow( "debug", image );
			}
			
			if( !trackObject && selection.width > 0 && selection.height > 0 )
			{
				Mat roi(image, selection);
				bitwise_not(roi, roi);
				trackObject = -1;
			}

			// Threshold Segmentation 
			if (faceTrackWindow.width >0 && faceTrackWindow.height >0)
				thresholdSegmentation(faceTrackWindow, &current_frame, dst);

			imshow( "CamShift Demo", image );
			imshow( "Histogram", histimg );
		}
		
		
		// ---- Nose Tracking ----
		if (!faces.empty() || (faceTrackWindow.width >0 && faceTrackWindow.height > 0))
		//if (false)
		{			
			if (!faces.empty())						
				for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
				{
					// Rect as output
					//selectionNose = noseRegion(*r, &current_frame);
					// Point as output
					nosePoint = noseRegion(*r, &current_frame, isPoint);
				}
			else			
				// Rect as output
				//selectionNose = noseRegion(faceTrackWindow, &current_frame);
				// Point as output
				nosePoint = noseRegion(faceTrackWindow, &current_frame, isPoint);
		}
		
		// Cursor Tracking Based on Nost Tracking
		// If the movement is too large, ignore the current point, set the location as the one before. (for now).
		// Later, we need to set the location by using Kalman Filter

		//NoseLocations(m_History, nosePoint);
		if (m_History.size() > 0 )
		{
			Point tempPoint;
			tempPoint.x = m_History.front().x;
			tempPoint.y = m_History.front().y;

			double diff, xdiff, ydiff;
			xdiff = tempPoint.x - nosePoint.x;
			ydiff = tempPoint.y - nosePoint.y;
			diff = sqrt(xdiff * xdiff + ydiff * ydiff);
			printf("diff is: %f \n", diff);
			if (diff > diffThreshold)
				// if the movement distance is larget than the threshold
				// use the location before.
				m_History.push_front(m_History.front());
			else
				// push 
				m_History.push_front(nosePoint);
		}
		else
			m_History.push_front(nosePoint);
		
		if (m_History.size() > m_nHistorySize)
			m_History.pop_back();

		m_History = trajGaussianSmooth(m_History, sigma1);

		//if (m_History.size() == 1)
		//	goldPoint = nosePoint;

		if (m_History.size() >= 2){
			// New Point
			Point newPoint;
			newPoint.x = m_History.front().x;
			newPoint.y = m_History.front().y;
			
			// Old Point
			Point oldPoint;
			oldPoint = meanPoint(m_History);
			//std::list<Point>::iterator iter = m_History.begin();
			//iter++;
			//oldPoint.x = iter->X;
			//oldPoint.y = iter->Y;
			//oldPoint.x = iter->x;
			//oldPoint.y = iter->y;
			
			//Screen Coordinates Transfer Factor
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			float scaleW = ((float)screenWidth)/640.0f;
			float scaleH = ((float)screenHeight)/480.0f;
			newPoint.x = (int)(newPoint.x * scaleW);
			newPoint.y = (int)(newPoint.y * scaleH);
			oldPoint.x = (int)(oldPoint.x * scaleW);
			oldPoint.y = (int)(oldPoint.y * scaleH);

			// Location Differences
			double ratio = 1;
			long xOffset = newPoint.x - oldPoint.x;
			long yOffset = newPoint.y - oldPoint.y;
			//xOffset = xOffset / ratio;
			//yOffset = yOffset / ratio;

			// Compute Location Movment
			POINT currentPoint;
			POINT resultPoint;
			::GetCursorPos(&currentPoint);
			resultPoint.x = currentPoint.x - xOffset * ratio;
			resultPoint.y = currentPoint.y - yOffset * ratio;

			// Check inbound
			if(resultPoint.x <= 0)
				resultPoint.x = 0;
			if(resultPoint.x >= screenWidth)
				resultPoint.x = screenWidth;
			if(resultPoint.y <= 0)
				resultPoint.y = 0;
			if(resultPoint.y >= screenHeight)
				resultPoint.y = screenHeight;
			
			SetCursorPos(resultPoint.x, resultPoint.y);
		}

		// ---- Nose CamShift Tracking Beginning Part ----
		// Backup Code is stored in file: Backup_Sections.txt
		// ------ Ending Part ----
		// Save current Frame into lastFrame;
		grabber->copyImageTo(last_frame);
		processor.processImage(last_frame);

		// Enable switching to InfraRead mode.
		unsigned char c = cv::waitKey(10) & 0xff;
		switch (c)
		{
		case 'q':		
			exit(0);
			break;
		case 'm':
			// Mesh Showing, not finish developing yet. Interface reserved
			mesh_generator->generate(last_frame);
			mesh_view->addMesh(mesh_generator->mesh(), Pose3D(), MeshViewer::FLAT);
			break;
		case 'd':
			// If Detection was false, turn it on, create windows.
			if (!Detection)
			{
				Detection = true;
				namedWindow("result");
				namedWindow("ROI");
				namedWindow("depthDraw");
			}
		default:
			;
		}
		
		// ---- Post Processing Section ----
		if (!Detection)
		{
			//destroyWindow("result");
			//destroyWindow("ROI");
			//destroyWindow("depthDraw");
		}
	}

	delete mesh_generator;
	cvReleaseVideoWriter(&writer);
	return 0;
}

vector<Rect> detectAndDraw( Mat& img,
						   CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
						   double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces;
	const static Scalar colors[] =  { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255)} ;
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

	cvtColor( img, gray, CV_BGR2GRAY );
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
	equalizeHist( smallImg, smallImg );

	t = (double)cvGetTickCount();
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );
	t = (double)cvGetTickCount() - t;
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		Mat smallImgROI;
		// Region of Interest with Color
		Mat smallImgROIColor;
		// Without the Circle
		smallImgROIColor = img(*r);
		cv::imshow("ROI", smallImgROIColor);

		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, color, 3, 8, 0 );
		if( nestedCascade.empty() )
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, color, 3, 8, 0 );
		}

	}  
	cv::imshow( "result", img );   	
	return(faces);
}

void depthAndDraw(Mat& img, std::vector<Rect> faces)
{
	int i = 0;
	double scale = 1;
	const static Scalar colors[] =  { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255)} ;
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		//Mat smallImgROI;
		//// Region of Interest with Color
		//Mat smallImgROIColor;
		//// Without the Circle
		//smallImgROIColor = img(*r);
		//cv::imshow("ROI", smallImgROIColor);

		//vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, color, 3, 8, 0 );

		cv::imshow("depthDraw", img);
	}  
}

Rect noseRegion(Rect r, ntk::RGBDImage* current_frame)
{
	cv::Mat Depth_normal = current_frame->depth();
	
	Point minLoc, maxLoc;
	double minVal, maxVal, ratio = 5;
	Rect nose;
	IplImage noseROI = current_frame->rgb();
	Mat noseRoiRgb = current_frame->rgb();
	Mat faceROI;
	Mat nonZeroMask;
	
	selection.x = r.x;
	selection.y = r.y;
	selection.height = r.height;
	selection.width  = r.width;

	Rect& rSelection = selection;
	faceROI = Depth_normal(rSelection);
	noseRoiRgb = noseRoiRgb(rSelection);
	cv::Mat3b depth_as_color_face;
	compute_color_encoded_depth(faceROI, depth_as_color_face);

	inRange(faceROI, Scalar(0.001, 0.001, 0.001, 0.001), Scalar(255, 255, 255, 255), nonZeroMask);

	minMaxLoc(faceROI, &minVal, &maxVal, &minLoc, &maxLoc, nonZeroMask);

	cv::putText(noseRoiRgb,
		cv::format("nose"),
		minLoc, 0, 0.5, Scalar(255,0,0,255));
	imshow("faceROI", noseRoiRgb);

	// For debugging
	/*nose.width = r->width / ratio;
	nose.height = r->height / ratio;
	nose.x = minLoc.x - nose.width / 2;
	nose.y = minLoc.y - nose.height / 2;

	noseRoiRgb = noseRoiRgb(nose);
	imshow("noseROI", noseRoiRgb);*/

	// Project index back into original whole image coordinate system.
	nose.width = r.width / ratio;
	nose.height = r.height / ratio;
	nose.x = minLoc.x + r.x - 1 - nose.width / 2;
	nose.y = minLoc.y + r.y - 1 - nose.width / 2;

	//smallImgROIColor = img(*r);				
	/*noseROI = current_frame->rgb();
	cvSetImageROI(&noseROI, nose);
	imshow("noseROI", &noseROI);*/
	return(nose);
}

Point noseRegion(Rect r, ntk::RGBDImage* current_frame, bool isPoint)
{
	cv::Mat Depth_normal = current_frame->depth();
	
	Point minLoc, maxLoc;
	double minVal, maxVal, ratio = 5;
	Rect nose;
	IplImage noseROI = current_frame->rgb();
	Mat noseRoiRgb = current_frame->rgb();
	Mat faceROI;
	Mat nonZeroMask;
	
	selection.x = r.x;
	selection.y = r.y;
	selection.height = r.height;
	selection.width  = r.width;

	Rect& rSelection = selection;
	faceROI = Depth_normal(rSelection);
	noseRoiRgb = noseRoiRgb(rSelection);
	cv::Mat3b depth_as_color_face;
	compute_color_encoded_depth(faceROI, depth_as_color_face);

	inRange(faceROI, Scalar(0.001, 0.001, 0.001, 0.001), Scalar(255, 255, 255, 255), nonZeroMask);

	minMaxLoc(faceROI, &minVal, &maxVal, &minLoc, &maxLoc, nonZeroMask);

	cv::putText(noseRoiRgb,
		cv::format("nose"),
		minLoc, 0, 0.5, Scalar(255,0,0,255));
	imshow("faceROI", noseRoiRgb);

	// For debugging
	/*nose.width = r->width / ratio;
	nose.height = r->height / ratio;
	nose.x = minLoc.x - nose.width / 2;
	nose.y = minLoc.y - nose.height / 2;

	noseRoiRgb = noseRoiRgb(nose);
	imshow("noseROI", noseRoiRgb);*/

	// Project index back into original whole image coordinate system.
	nose.width = r.width / ratio;
	nose.height = r.height / ratio;
	nose.x = minLoc.x + r.x - 1 - nose.width / 2;
	nose.y = minLoc.y + r.y - 1 - nose.width / 2;

	//smallImgROIColor = img(*r);				
	/*noseROI = current_frame->rgb();
	cvSetImageROI(&noseROI, nose);
	imshow("noseROI", &noseROI);*/
	return(minLoc);
}

Rect checkRect(Rect r, CvSize siz){
	if (r.x + r.width >= siz.width)
		r.width = r.width - (r.x + r.width - siz.width);
	if (r.y + r.height >= siz.height)
		r.height = r.height - (r.y + r.height - siz.height);
	return (r);
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
	inRange(depthROI, Scalar::all(0.001), mFace, maskROI);
	mFace = cv::mean(rDepthROI, rMaskROI);
	


	
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

Point meanPoint(std::list<Point> history){
	Point acc;
	acc.x = 0; acc.y = 0;
	for (std::list<Point>::iterator iter = history.begin(); iter != history.end(); ++iter){
		acc.x = iter->x +acc.x;
		acc.y = iter->y + acc.y;
	}

	acc.x = acc.x / history.size();
	acc.y = acc.y / history.size();
	return acc;
}		
std::list<Point> trajGaussianSmooth(std::list<Point> history, double sigma1){
	CvMat* X = cvCreateMat(history.size(), 1, CV_32FC1);
	CvMat* Y = cvCreateMat(history.size(), 1, CV_32FC1);
	CvMat* smoothX = cvCreateMat(history.size(), 1, CV_32FC1);;
	CvMat* smoothY = cvCreateMat(history.size(), 1, CV_32FC1);;
	int count = 0;
	Point buff;
	std::list<Point> smoothHistory;
	
	if (history.size() <= 5)
		return history;
	else{
		for(std::list<Point>::iterator iter = history.begin(); iter != history.end(); ++iter, ++count){
			cvSetReal1D(X, count, iter->x);
			cvSetReal1D(Y, count, iter->y);
		}

		cvSmooth(X, smoothX, CV_GAUSSIAN, 3, 0, sigma1);
		cvSmooth(Y, smoothY, CV_GAUSSIAN, 3, 0, sigma1);
		
		for (--count; count >= 0; --count){
			Point temp(count, 0);
			buff.x = cvGetReal1D(smoothX, count);
			buff.y = cvGetReal1D(smoothY, count);
			smoothHistory.push_front(buff);
		}
		return smoothHistory;
	}
}


	