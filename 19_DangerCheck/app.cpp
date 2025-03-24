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
#define H_MAX 179
#define H_MIN 140
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

void* cameraThread(void* arg) {

	disable_interrupt(NULL);

    Camera camera;
    hub_button_t pressed;
    Mat frame;
    Mat roiFrame;
    Mat rgb_image;
    Mat hsv_image;
    Mat mask_image;
    Scalar lowerRed(H_MIN, S_MIN, V_MIN);
    Scalar upperRed(H_MAX, S_MAX, V_MAX);
    Rect roi(200, 60, 200, 210);
    unsigned int blue_data = 0;
    bool flag = true;
    
    while(true) {
		hub_button_is_pressed(&pressed);
		if (pressed != HUB_BUTTON_LEFT) {
			camera.captureVideo();
			camera.showVideo();
			camera.getVideo(frame);
			roiFrame = frame(roi);
			imshow("roiFrame", roiFrame);
			waitKey(1);

			cvtColor(roiFrame, hsv_image, COLOR_BGR2HSV);
		
			// inRangeを用いてフィルタリング
			inRange(hsv_image, lowerRed, upperRed, mask_image);
			imshow("mask", mask_image);
			waitKey(1);
			
			blue_data = countNonZero(mask_image);
			
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
