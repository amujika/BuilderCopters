#include <iostream>
#include <opencv.hpp>
#include "Localization/camera.h"

using namespace std;

vector<Camera> web_cams;


int main(int argc, char* argv[])  {

	//This is needed so OpenCV windows can be closed
	cv::startWindowThread();

	cout << "Enter the webcam ports you want to use (-1 when you are done):" << endl;

	while(true) {
		Camera temporal_camera;
		int camera_port;
		cin >> camera_port;
		if (camera_port == -1) {
			if (web_cams.empty())
				cout << "No cameras where selected, please select at least one." << endl;
			else
				break;
		} else if (camera_port == -2) { // @@TODO. Remove when I can use webcams
			temporal_camera = Camera();
			if (!temporal_camera.isVideoOpened()) {
				cout << "Couldn't open a camera in port " << camera_port << endl;
				continue;
			}
			temporal_camera.calibrateColorFilters();
		} else {
			temporal_camera = Camera("Camera in port " + camera_port, camera_port);
			if (!temporal_camera.isVideoOpened()) {
				cout << "Couldn't open a camera in port " << camera_port << endl;
				continue;
			}
			temporal_camera.calibrateColorFilters();
		}
	}

	return 0;
}
