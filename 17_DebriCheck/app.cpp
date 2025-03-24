#include "app.h"
#include "Motor.hpp"
#include "Camera.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

// 抽出する画像の輝度値の範囲を指定
#define H_MAX 105
#define H_MIN 95
#define S_MAX 255
#define S_MIN 50
#define V_MAX 255
#define V_MIN 50

using namespace cv;

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

static void disable_interrupt(sigset_t *old)
{
  sigset_t sigset;
  sigemptyset(&sigset);

  sigaddset(&sigset,SIGUSR2);
  sigaddset(&sigset,SIGALRM);
  sigaddset(&sigset,SIGPOLL);
  sigprocmask(SIG_BLOCK, &sigset, old);
  return;
}

void extract_area(Mat& square, const Mat& mask)
{
	square = Mat::zeros(mask.size(), mask.type());
	rectangle(square, Point(200, 50), Point(400, 230), Scalar(255, 255, 255), FILLED);
}

void* cameraThread(void* arg) {

	disable_interrupt(NULL);

    Camera camera;
    hub_button_t pressed;
    Mat frame;
    Mat hsv_image;
    Mat mask_image;
    Mat square;
    Mat result;
    Scalar s_min;
    Scalar s_max;
    unsigned int blue_data = 0;
    bool flag = true;
    
    while(true) {
		hub_button_is_pressed(&pressed);
		if (pressed != HUB_BUTTON_LEFT) {
			camera.captureVideo();
			camera.getVideo(frame);
			camera.showVideo();
			cvtColor(frame, hsv_image, COLOR_BGR2HSV, 3);
			imshow("HSV_image", hsv_image);
			waitKey(1);
			
			// inRangeを用いてフィルタリング
			s_min = Scalar(H_MIN, S_MIN, V_MIN);
			s_max = Scalar(H_MAX, S_MAX, V_MAX);
			inRange(hsv_image, s_min, s_max, mask_image);
			imshow("mask1", mask_image);
			waitKey(1);
			
			extract_area(square, mask_image);
			imshow("square", square);
			bitwise_and(mask_image, square, result);
			imshow("result", result);
			waitKey(1);
			
			blue_data = countNonZero(result);
			
			printf("blue_data : %d\n", blue_data);
			if (blue_data >= 10000)
			{
				printf("motor move\n");
				//LeftMotor.setPower(40);
				//RightMotor.setPower(40);
			}
			flag = true;
		} else {
			if (flag) {
				blue_data = 0;
				LeftMotor.stop();
				RightMotor.stop();
				flag = false;
			}
		}
		usleep(30 * 1000);
	}
	
	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	pthread_t camera;

	pthread_create(&camera, nullptr, cameraThread, nullptr);
	pthread_join(camera, nullptr);

    printf("finish\n");

    /* タスク終了 */
    ext_tsk();
}
