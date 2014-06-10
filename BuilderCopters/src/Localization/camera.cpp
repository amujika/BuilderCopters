#include <opencv.hpp>
#include "camera.h"

using namespace std;
using namespace cv;

Camera::Camera() {
	name_ = "testCamera";
	video_input_ = VideoCapture("TestFiles/Video/singleCameraTest_easy.mp4");
}

Camera::Camera(string name, int port) {
	name_ = name;
	video_input_ = VideoCapture(port);

	LowH = 0;
	HighH = 179;
	LowS = 0;
	HighS = 255;
	LowV = 0;
	HighV = 255;
}

void Camera::calibrateColorFilters() {
	Mat RGB_frame, HSV_frame, threshold_frame;
	string calibrate_window_name = "calibrate camera: " + name_;
	string original_window_name = "original image: " + name_;

	namedWindow(calibrate_window_name);
	namedWindow(original_window_name);

	//Trackbars for the user to calibrate the threshold
	createTrackbar("LowH", calibrate_window_name, &LowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", calibrate_window_name, &HighH, 179);
	createTrackbar("LowS", calibrate_window_name, &LowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", calibrate_window_name, &HighS, 255);
	createTrackbar("LowV", calibrate_window_name, &LowV, 255); //Value (0 - 255)
	createTrackbar("HighV", calibrate_window_name, &HighV, 255);

	while ((char)waitKey(15) != 'x') {
		// @@TODO. This loops video files, when using webcams replace with (video_input_ >> frame;)
		if (!video_input_.read(RGB_frame)) {
			video_input_.set(CV_CAP_PROP_POS_FRAMES, 0);
			continue;
		}

		cvtColor(RGB_frame, HSV_frame, CV_RGB2HSV);
		inRange(HSV_frame, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), threshold_frame);

		imshow(calibrate_window_name, threshold_frame);
		imshow(original_window_name, RGB_frame);
	}
	destroyWindow(calibrate_window_name);
	destroyWindow(original_window_name);
}

bool Camera::isVideoOpened() {
	return video_input_.isOpened();
}

string Camera::name() {
	return name_;
}
