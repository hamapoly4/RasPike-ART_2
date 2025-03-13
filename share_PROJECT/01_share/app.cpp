
#include "app.h"
#include "Motor.hpp"
#include "ColorSensor.hpp"
#include "Camera.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static ColorSensor colorSensor(PBIO_PORT_ID_C);

size_t data_size = 4 * sizeof(int);  // int型4つ分
void* ptr;

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

	// 共有メモリを開く
    int fd = shm_open("yuta", O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        ext_tsk();
    }

    // 共有メモリのマッピング
    ptr = mmap(0, data_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        ext_tsk();
    }

	sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
	slp_tsk();  // メインタスクの就寝
  
	stp_cyc(SUB_TASK_CYC);  // サブタスクの停止

    printf("finish\n");
    
    // 後処理
    munmap(ptr, data_size);
    close(fd);

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
	  
	  // データの読み取り
	  int* data = static_cast<int*>(ptr);
	  for (size_t i = 0; i < 4; ++i) {
		  printf("Data[%d] : %d\n", i, data[i]);
	  }
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

