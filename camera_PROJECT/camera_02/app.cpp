#include "app.h"
#include <stdio.h>
#include "LineTracer.h"
#include <opencv2/opencv.hpp>

/* センサーポートの定義 */
static const pbio_port_id_t
  color_sensor_port    = PBIO_PORT_ID_C,
  left_motor_port      = PBIO_PORT_ID_E,
  right_motor_port     = PBIO_PORT_ID_B;

void camera() {
    printf("start!!\n");
    cv::VideoCapture cap(0); // カメラデバイスを開く
    if (!cap.isOpened()) {
        printf("カメラが開けません\n");
        return;
    }

    //cv::namedWindow("カメラ画像", cv::WINDOW_AUTOSIZE);  // ウィンドウを事前に作成

    cv::Mat frame;
    while(1) {
        printf("while start\n");
        cap >> frame;

        try {
            if (frame.empty()) {
                printf("フレームが空です\n");
                frame.setTo(cv::Scalar(0, 0, 0)); // フレームをクリア
                continue;
            } else {
                cv::Mat display_frame = frame.clone();  // フレームをコピー
                printf("フレームのサイズ: %d x %d\n", display_frame.cols, display_frame.rows);
                printf("フレームのタイプ: %d\n", display_frame.type());
                cv::imshow("カメラ画像", display_frame);
                cv::waitKey(1); // ウィンドウの更新を行う
            }
        } catch (const cv::Exception& e) {
            printf("エラー: %s\n", e.what());
        }

        // ESCキーが押されたらループを終了
        if (cv::waitKey(1) == 27) {
            cv::destroyWindow("カメラ画像");
            cap.release();
            break;
        }
    }
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    printf("Start Line Trace!!\n");
    camera();

    /* ライントレースタスクの起動 */
    //sta_cyc(LINE_TRACER_TASK_CYC);

    /* タスク終了 */
    ext_tsk();
}
