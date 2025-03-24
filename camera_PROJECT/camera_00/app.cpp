#include "app.h"
#include <stdio.h>
#include "LineTracer.h"
#include <opencv2/opencv.hpp>

/* センサーポートの定義 */
static const pbio_port_id_t
  color_sensor_port    = PBIO_PORT_ID_C,
  left_motor_port      = PBIO_PORT_ID_E,
  right_motor_port     = PBIO_PORT_ID_B;

void camera()
{
	printf("start!!\n");
	cv::VideoCapture cap(0); // カメラデバイスを開く
    if (!cap.isOpened()) {
        printf("カメラが開けません\n");
        return;
    }

    cv::Mat frame;
    
    do {
		printf("フレームが空です\n");
		cap >> frame; // フレームをキャプチャ
	} while (frame.empty());

    cv::imwrite("captured_image.jpg", frame); // 画像を保存
    printf("画像を保存しました: captured_image.jpg\n");
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  /* LineTracerに構成を渡す */
  //LineTracer_Configure(left_motor_port,right_motor_port,color_sensor_port);
  printf("Start Line Trace!!\n");
  camera();
    
  /* ライントレースタスクの起動 */
  //sta_cyc(LINE_TRACER_TASK_CYC);

  /* タスク終了 */
  ext_tsk();
}
