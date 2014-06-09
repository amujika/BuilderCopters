#ifndef CAMERA_H_
#define CAMERA_H_

#include <opencv.hpp>

class Camera {
public:
	Camera();
	Camera(std::string name, int port);
	void calibrateColorFilters();
	bool isVideoOpened();
	std::string name();

private:
	cv::VideoCapture video_input_;
	std::string name_;
	//Limits in HSV image
	int LowH;
	int HighH;
	int LowS;
	int HighS;
	int LowV;
	int HighV;
};



#endif /* CAMERA_H_ */
