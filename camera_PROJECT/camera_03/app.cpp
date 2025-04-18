#include "app.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::VideoCapture cap(0);
cv::Mat frame;

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

    printf("Start!!\n");
    
    sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
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
	  cap >> frame;
	  if (frame.empty())
	  {
	   	  printf("don't get frame\n");
	  }
	  
	  cv::imshow("frame", frame);
	  cv::waitKey(1);

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

