#include "app.h"
#include "Motor.hpp"
#include "ColorSensor.hpp"
#include "Camera.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static ColorSensor colorSensor(PBIO_PORT_ID_C);

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
    
    while(true) {
		camera.captureVideo();
		camera.showVideo();
		usleep(30 * 1000);
		printf("camera finish\n");
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
	const int8_t target = 35;
	int8_t brightness;
	int8_t diff;
	int8_t old_diff = 0;
	int8_t p_value = 0;
	int8_t d_value = 0;
	int8_t turn;
	
	while (true)
	{
		brightness = colorSensor.getBrightness();
		diff = target - brightness;
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
