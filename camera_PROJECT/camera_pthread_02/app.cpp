#include "app.h"
#include "Motor.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

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

    cv::VideoCapture cap(0); // カメラデバイスを開く
    if (!cap.isOpened()) {
        printf("カメラが開けません\n");
        return nullptr;
    }

    cv::Mat frame;
    
    while(true) {
		cap >> frame;
		if (frame.empty())
		{
			printf("don't get frame\n");
			return nullptr;
		}
		
		cv::imshow("frame", frame);
		cv::waitKey(30);
		printf("camera finish\n");
	}

	cv::destroyWindow("frame");
	cap.release();
	
	return nullptr;
}

void* robotThread(void* arg)
{
	disable_interrupt(NULL);
	
	while (true) {
		LeftMotor.setPower(40);
		RightMotor.setPower(40);
		
		usleep(10 * 1000);
		printf("robot finish\n");
	}

	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	pthread_t camera;
	pthread_t robot;
	
    pthread_create(&camera, nullptr, cameraThread, nullptr);
    pthread_create(&robot, nullptr, robotThread, nullptr);

    pthread_join(camera, nullptr);
    pthread_join(robot, nullptr);

    printf("finish\n");

    /* タスク終了 */
    ext_tsk();
}
