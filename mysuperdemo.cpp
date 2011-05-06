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
#include "GuiController.h"
#include "ObjectDetector.h"

#include <QApplication>
#include <QMetaType>

using namespace ntk;
using namespace cv;
using namespace std;

// Create memory for calculations
static CvMemStorage* storage = 0;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

// Create a string that contains the cascade name
const char* cascade_name = "haarcascade_frontalface_alt.xml";

// Function prototype for detecting and drawing an object from an image
void detect_and_draw(IplImage* image);


int main(int argc, char** argv)
{
	QApplication::setGraphicsSystem("raster");
	QApplication app (argc, argv);

	string imgPath = "C:\CProjects\Kinect_OpenNI\RGBDemo-0.5.0-Source\RGBDemo-0.5.0-Source\mysuperdemo\imgPath";
	string filename;
	
	/*KinectGrabber grabber;*/
	ntk::NiteRGBDGrabber* k_grabber = new NiteRGBDGrabber();
	ntk::RGBDGrabber* grabber = 0;
	//k_grabber->setHighRgbResolution(true);
	k_grabber->initialize();	

	// Postprocess raw kinect data.
	// Tell the processor to transform raw depth into meters using baseline-offset technique.
	
	grabber = k_grabber;

	// MeshGenerator Functionality Added
	ntk::MeshGenerator* mesh_generator = 0;
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
	namedWindow("color");
	namedWindow("depth");
	namedWindow("depth_as_color");
	namedWindow("result");

	// Current image. An RGBDImage stores rgb and depth data.
	ntk::RGBDImage current_frame;
	//GuiController gui_controller (*grabber, *m_processor);
	//grabber->addEventListener(&gui_controller);


	if (mesh_generator)
	{
		mesh_generator->setUseColor(true);
		//gui_controller.setMeshGenerator(*mesh_generator);
	}

	grabber->start();
	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
	storage = cvCreateMemStorage(0);
	while (true)
	{


		/*grabber.waitForNextFrame();
		grabber.copyImageTo(current_frame);
		processor.processImage(current_frame);*/

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
		iswrite = cvSaveImage("test.jpeg", pSaveImg, &nchannel);		
		if(!iswrite)
			printf("Could not save\n");
		IplImage* frame_copy = pSaveImg;
		detect_and_draw(frame_copy);

		// Show the depth image as normalized gray scale
		imshow_normalized("depth", current_frame.depth());

		// Compute color encoded depth.
		cv::Mat3b depth_as_color;
		compute_color_encoded_depth(current_frame.depth(), depth_as_color);
		imshow("depth_as_color", depth_as_color);
		
		// Enable switching to InfraRead mode.
		unsigned char c = cv::waitKey(10) & 0xff;
		if (c == 'q')
			exit(0);
	}

	delete mesh_generator;
	return 0;
}

void detect_and_draw( IplImage* img )
{
    int scale = 1;

    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
    }

    // Show the image in the window named "result"
    cvShowImage( "result", img );

    // Release the temp image created.
    cvReleaseImage( &temp );
}