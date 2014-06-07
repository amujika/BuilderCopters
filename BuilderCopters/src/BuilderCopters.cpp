#include "opencv.hpp"

int main(int argc, char* argv[])  {

	IplImage* img = cvCreateImage( cvSize( 640, 480 ), IPL_DEPTH_8U, 3 );

	cvCircle( img, cvPoint( 320, 240 ), 100, cvScalar( 255, 0, 0 ), 5 );

	cvNamedWindow( "OpenCV Window", CV_WINDOW_NORMAL );
	cvShowImage( "OpenCV Window", img );

	cvWaitKey(0);

	cvDestroyWindow( "OpenCV Window" );
	cvReleaseImage( &img );

	return 0;
}
