#include "app.h"
#include "Motor.hpp"
#include "ColorSensor.hpp"
#include "Camera.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include <iostream> // 入出力を行うための標準ライブラリ
#include <vector> // std::vectorを使用するためのヘッダー
#include <algorithm> // std::max_elementを使用するためのヘッダー

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static ColorSensor colorSensor(PBIO_PORT_ID_C);

int offset_x = 0;

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
    cv::Mat frame, gray, binary;
    
    while(true) {
		camera.captureVideo();
		camera.showVideo();
		camera.getVideo(frame);
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::threshold(gray, binary, 50, 255, cv::THRESH_BINARY);
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(binary, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
		if (!contours.empty()) {
			// 最大の輪郭を選択
			auto max_contour = *std::max_element(contours.begin(), contours.end(), [](const auto &a, const auto &b) {
				return cv::contourArea(a) < cv::contourArea(b);
			});
			// 重心を求める
			cv::Moments m = cv::moments(max_contour);
			cv::Point line_center(m.m10/m.m00, m.m01/m.m00);
			// ここで制御アルゴリズムを実装
			int image_center_x = frame.cols / 2;
			int image_center_y = frame.rows / 2;
			cv::Point image_center(image_center_x, image_center_y);

			offset_x = line_center.x - image_center.x;
			printf("offset_x : %d\n", offset_x);
		}

		cv::imshow("gray", gray);
		cv::waitKey(1);
		cv::imshow("binary", binary);
		cv::waitKey(1);
		usleep(30 * 1000);
	}
	
	return nullptr;
}

void* linetrace(void* arg)
{
	disable_interrupt(NULL);
	hub_button_t pressed;
	const int8_t PWM = 40;
	const float KP = 0.7;
	const float KD = 1.5;
	const int8_t target = 0;
	int8_t diff;
	int8_t old_diff = 0;
	int8_t p_value = 0;
	int8_t d_value = 0;
	int8_t turn;
	
	while (true)
	{
		diff = target - offset_x;
		p_value = (diff) * KP;
		d_value = (diff - old_diff) * KD;
		old_diff = diff;
		turn = p_value + d_value;
		
		LeftMotor.setPower(PWM + turn);
		RightMotor.setPower(PWM - turn);
		
		hub_button_is_pressed(&pressed);
		if (pressed == HUB_BUTTON_CENTER)
		{
			LeftMotor.stop();
			RightMotor.stop();
			break;
		}

		usleep(10 * 1000);
	}

	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	pthread_t camera;
	pthread_t trace;

	pthread_create(&camera, nullptr, cameraThread, nullptr);
    pthread_create(&trace, nullptr, linetrace, nullptr);
    pthread_join(camera, nullptr);
    pthread_join(trace, nullptr);

    printf("finish\n");

    /* タスク終了 */
    ext_tsk();
}
