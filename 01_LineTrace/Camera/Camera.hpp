#ifndef ___CAMERA_CLASS
#define ___CAMERA_CLASS

#include <opencv2/opencv.hpp>

class Camera {
public:
	Camera();
	~Camera();
	void captureVideo();
	void showVideo();

private:
	cv::VideoCapture cap;
	cv::Mat frame;
};

#endif // ___CAMERA_CLASS
