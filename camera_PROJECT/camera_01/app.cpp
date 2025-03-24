#include "app.h"
#include <stdio.h>

/* ここに使用するクラスのヘッダファイルをインクルード */
#include <opencv2/opencv.hpp>


/* ここに静的インスタンスを生成する */
cv::VideoCapture cap;
cv::Mat frame;

bool camera_config()
{
    cap.open(0);
	if (!cap.isOpened()) {
        printf("カメラが開けません\n");
        return false;
    }
    else {
		printf("カメラが開ita\n");
		return true;
	}
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  printf("Start!!\n");
  
  if (camera_config()) {
	  sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
	  
	  slp_tsk();  // メインタスクの就寝
	  
	  stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
  }
  
  printf("Finish!!\n");

  ext_tsk();  // タスク終了
}

/* サブタスク(70ms周期で関数コールされる) */
void sub_task(intptr_t unused) {
  hub_button_t pressed;
  hub_button_is_pressed(&pressed);

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  cap >> frame; // フレームをキャプチャ

	  if (frame.empty()) {
		  printf("フレームが空です\n");
	  }
	  else {
		  cv::imshow("カメラ画像", frame);
	  }
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  cv::destroyWindow("カメラ画像"); //ウィンドウを閉じる
      cap.release();
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

