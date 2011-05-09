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
// Create a new Haar classifier
//static CvHaarClassifierCascade* cascade = 0;
//static CvHaarClassifierCascade* nestedCascade = 0;

// Create a string that contains the cascade name
string cascade_name = "haarcascade_frontalface_alt.xml";
string nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";

// Function prototype for detecting and drawing an object from an image
vector<Rect> detectAndDraw( Mat& img,
						   CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
						   double scale);
// Function for visualize the depth images with facial detection region
void depthAndDraw(Mat& img, vector<Rect> faces);


int main(int argc, char** argv)
{
	QApplication::setGraphicsSystem("raster");
	QApplication app (argc, argv);

	CascadeClassifier cascade, nestedCascade;

	string imgPath = "C:\CProjects\Kinect_OpenNI\RGBDemo-0.5.0-Source\RGBDemo-0.5.0-Source\mysuperdemo\imgPath";
	string filename;

	/*KinectGrabber grabber;*/
	ntk::NiteRGBDGrabber* k_grabber = new NiteRGBDGrabber();
	ntk::RGBDGrabber* grabber = 0;
	//k_grabber->setHighRgbResolution(true);
	k_grabber->initialize();	

	// OpenCV Save an Video
	CvVideoWriter *writer = 0;
	int isColor = 1;
	int fps = 30;
	int frameW = 640;
	int frameH = 480;
	writer = cvCreateVideoWriter("out.avi", CV_FOURCC('I', '4', '2', '0'), fps, cvSize(frameW, frameH), isColor);

	// Postprocess raw kinect data.
	// Tell the processor to transform raw depth into meters using baseline-offset technique.

	grabber = k_grabber;

	// MeshGenerator Functionality Added
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




	ntk::NiteProcessor processor;
	processor.setFilterFlag(RGBDProcessor::ComputeKinectDepthBaseline, true);

	// m_processor for mesh_viewer
	ntk::NiteProcessor* m_processor = 0;
	m_processor = new ntk::NiteProcessor();




	// OpenCV windows.
	if(!QT)
	{
		namedWindow("color");
		namedWindow("depth");
		namedWindow("depth_as_color");
		namedWindow("result");
		namedWindow("ROI");
		namedWindow("depthDraw");
	}

	// Current image. An RGBDImage stores rgb and depth data.
	ntk::RGBDImage current_frame;
	ntk::RGBDImage last_frame;
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

	grabber->start();

	//cascade = (CvHaarClassifierCascade&)cvLoad(cascade_name, 0, 0, 0);
	//nestedCascade = (CvHaarClassifierCascade&)cvLoad(nestedCascadeName, 0, 0, 0);
	cascade.load(cascade_name);
	nestedCascade.load(nestedCascadeName);
	storage = cvCreateMemStorage(0);

	if (QT)
		app.exec();

	while (true)
	{
	
		grabber->waitForNextFrame();
		grabber->copyImageTo(current_frame);
		processor.processImage(current_frame);	

		// Show the frames per second of the grabber
		//int fps = grabber.frameRate();
		int fps = grabber->frameRate();
		cv::putText(current_frame.rgbRef(),
			cv::format("%d fps", fps),
			Point(10,20), 0, 0.5, Scalar(255,0,0,255));

		// Display the color image	
		//imshow("color", current_frame.rgb());

		IplImage SaveImg = current_frame.rgb();
		IplImage* pSaveImg = &SaveImg;

		imshow("color", pSaveImg);
		bool iswrite;
		const int nchannel = 3;
		vector<Rect> faces;
		iswrite = cvSaveImage("test.jpeg", pSaveImg, &nchannel);		
		if(!iswrite) printf("Could not save\n");
		cvWriteFrame(writer, pSaveImg);

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
			Detection = false;



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

		if (!Detection)
		{
			destroyWindow("result");
			destroyWindow("ROI");
			destroyWindow("depthDraw");
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