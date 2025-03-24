#include "app.h"
#include <stdio.h>
#include "LineTracer.h"
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>

/* センサーポートの定義 */
static const pbio_port_id_t
  color_sensor_port    = PBIO_PORT_ID_C,
  left_motor_port      = PBIO_PORT_ID_E,
  right_motor_port     = PBIO_PORT_ID_B;

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
    
    for (int i = 0; i < 100; i++) {
		cap >> frame;
		if (frame.empty())
		{
			printf("don't get frame\n");
			return nullptr;
		}
		
		cv::imshow("frame", frame);
		cv::waitKey(30);
	}

	cv::destroyWindow("frame");
	cap.release();
	
	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	pthread_t camera;
	
    pthread_create(&camera, nullptr, cameraThread, nullptr);
    pthread_join(camera, nullptr);
    printf("finish\n");

    /* ライントレースタスクの起動 */
    //sta_cyc(LINE_TRACER_TASK_CYC);

    /* タスク終了 */
    ext_tsk();
}
