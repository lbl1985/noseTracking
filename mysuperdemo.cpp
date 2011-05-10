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
int vmin = 10, vmax = 256, smin = 30;


// Function prototype for detecting and drawing an object from an image
vector<Rect> detectAndDraw( Mat& img,
						   CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
						   double scale);
// Function for visualize the depth images with facial detection region
void depthAndDraw(Mat& img, vector<Rect> faces);


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
	float hranges[] = {0,180};
    const float* phranges = hranges;
	
	Mat hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;

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
		{
			Detection = false;
			isTracking = true;

			// Face Tracking Starts here
			for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
			{
				selection.x = r->x;
				selection.y = r->y;
				selection.height = r->height;
				selection.width  = r->width;

				
			}
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
				//trackWindow = trackBox.boundingRect();

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

			imshow( "CamShift Demo", image );
			imshow( "Histogram", histimg );
		}
		




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