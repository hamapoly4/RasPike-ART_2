#include "app.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>

/* センサーポートの定義 */
static const pbio_port_id_t
  color_sensor_port    = PBIO_PORT_ID_C,
  left_motor_port      = PBIO_PORT_ID_E,
  right_motor_port     = PBIO_PORT_ID_B;

cv::VideoCapture cap;
cv::Mat frame;

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
    cap.open(0); // カメラデバイスを開く
    if (!cap.isOpened()) {
		printf("カメラが開けません\n");
		return nullptr;
	}

	while (1)
	{
		cap >> frame;
		if (frame.empty())
		{
			printf("don't get frame\n");
			return nullptr;
		}
			
		cv::imshow("frame", frame);
		cv::waitKey(30);
	}
	
	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	
	pthread_t camera;
    printf("Start!!\n");
    
    sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
    pthread_create(&camera, nullptr, cameraThread, nullptr);
    pthread_join(camera, nullptr);
  
    slp_tsk();  // メインタスクの就寝
  
    stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
  
    printf("Finish!!\n");
    cv::destroyWindow("frame");
    cap.release();

    ext_tsk();  // タスク終了
}

/* サブタスク(10ms周期で関数コールされる) */
void sub_task(intptr_t unused) {
  hub_button_t pressed;
  hub_button_is_pressed(&pressed);

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  printf("Morita Hikaru\n");

  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
      printf("heheh\n");
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

