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
}

void Camera::calibrateColorFilters() {
	Mat color_frame, HSV_frame, threshold_frame;
	string window_name = "calibrate camera: " + this->name_;

	namedWindow(window_name);

	//Trackbars for the user to calibrate the threshold
	createTrackbar("LowH", window_name, &LowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", window_name, &HighH, 179);
	createTrackbar("LowS", window_name, &LowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", window_name, &HighS, 255);
	createTrackbar("LowV", window_name, &LowV, 255); //Value (0 - 255)
	createTrackbar("HighV", window_name, &HighV, 255);

	while ((char)waitKey(15) != 'x') {
		// @@TODO. This loops video files, when using webcams replace with (video_input_ >> frame;)
		if (!video_input_.read(color_frame)) {
			video_input_.set(CV_CAP_PROP_POS_FRAMES, 0);
			continue;
		}
		cvtColor(color_frame, HSV_frame, CV_RGB2HSV);
		inRange(HSV_frame, Scalar(100, 100, 100), Scalar(120, 120, 120), threshold_frame);

		imshow(window_name, threshold_frame);
	}
	destroyWindow(window_name);
}

bool Camera::isVideoOpened() {
	return video_input_.isOpened();
}

string Camera::name() {
	return name_;
}
