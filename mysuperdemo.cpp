#include <ntk/camera/kinect_grabber.h>
#include <ntk/camera/nite_rgbd_grabber.h>
#include <ntk/camera/rgbd_processor.h>
#include <ntk/utils/opencv_utils.h>

#include <ntk/mesh/mesh_generator.h>
#include <ntk/mesh/surfels_rgbd_modeler.h>

using namespace ntk;
using namespace cv;


int main()
{
	/*KinectGrabber grabber;*/
	ntk::NiteRGBDGrabber* k_grabber = new NiteRGBDGrabber();
	//k_grabber->setHighRgbResolution(true);
	k_grabber->initialize();	

	// Postprocess raw kinect data.
	// Tell the processor to transform raw depth into meters using baseline-offset technique.

	ntk::RGBDGrabber* grabber = 0;
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

	if (mesh_generator)
	{
		mesh_generator->setUseColor(true);
		// Doesn't have gui controller here
	}
	

	ntk::NiteProcessor processor;
	processor.setFilterFlag(RGBDProcessor::ComputeKinectDepthBaseline, true);
	//processor = new ntk::NiteProcessor;


	// OpenCV windows.
	namedWindow("color");
	namedWindow("depth");
	namedWindow("depth_as_color");
	namedWindow("mesh");

	// Current image. An RGBDImage stores rgb and depth data.
	ntk::RGBDImage current_frame;

	/*GuiController gui_controller (*grabber, *processor);
	grabber->addEventListener(&gui_controller);*/
	grabber->start();


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
		imshow("color", current_frame.rgb());

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
