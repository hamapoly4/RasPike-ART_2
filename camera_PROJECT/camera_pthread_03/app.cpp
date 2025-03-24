#include "app.h"
#include "Motor.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

cv::VideoCapture cap(0); // カメラデバイスを開く
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

void* cameraThread(void* arg)
{
    disable_interrupt(NULL);
    printf("10ms スレッドが実行されています\n");
    
    cap >> frame;	
	if (frame.empty())
	{
		printf("don't get frame\n");
		return nullptr;
	}
	
	cv::imshow("frame", frame);
	cv::waitKey(1);

    return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
  printf("Start!!\n");
    
  sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
  slp_tsk();  // メインタスクの就寝
  
  stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
  
  printf("Finish!!\n");
}

/* サブタスク(10ms周期で関数コールされる) */
void sub_task(intptr_t unused) {
  pthread_t camera;
  hub_button_t pressed;
  hub_button_is_pressed(&pressed);

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  pthread_create(&camera, nullptr, cameraThread, nullptr);
	  pthread_join(camera, nullptr);
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */

	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

