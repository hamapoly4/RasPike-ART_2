/*---------------------------------------------------
 * 
 * 			Cyclic_Handler and Thread
 * 
 *---------------------------------------------------*/

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
    hub_button_t pressed;
    
    while(true) {
		hub_button_is_pressed(&pressed);
		if (pressed != HUB_BUTTON_LEFT) {
			camera.captureVideo();
			camera.showVideo();
			usleep(30 * 1000);
		} else {
			break;
		}
	}
	
	return nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
	pthread_t camera;

	while (true) {
		sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
		slp_tsk();  // メインタスクの就寝
  
		stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
		printf("sub_task stop\n");
		pthread_create(&camera, nullptr, cameraThread, nullptr);
		pthread_join(camera, nullptr);
	}

    printf("finish\n");

    /* タスク終了 */
    ext_tsk();
}

/* サブタスク(10ms周期で関数コールされる) */
void sub_task(intptr_t unused) {
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
  
  hub_button_is_pressed(&pressed);

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  brightness = colorSensor.getBrightness();
	  diff = target - brightness;
	  p_value = (diff) * KP;
	  d_value = (diff - old_diff) * KD;
	  old_diff = diff;
	  turn = p_value + d_value;
		
	  LeftMotor.setPower(PWM + turn);
	  RightMotor.setPower(PWM - turn);
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  printf("center button pressed\n");
	  LeftMotor.stop();
	  RightMotor.stop();
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

