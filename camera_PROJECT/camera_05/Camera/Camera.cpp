#include "Camera.hpp"
#include <stdio.h>

using namespace cv;

Camera::Camera()
{
	cap.open(0);
	if (!cap.isOpened())
	{
		printf("カメラが開けません\n");
	}
}

Camera::~Camera()
{
	destroyAllWindows();
    cap.release();
}

void Camera::captureVideo()
{
	cap >> frame;
	if (frame.empty())
	{
		printf("フレームが空です\n");
		return;
	}
	
	imshow("frame", frame);
	waitKey(1);
}
