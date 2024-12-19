#include "app.h"
#include <stdio.h>

/* ここに静的インスタンスを生成する */
static pup_device_t* ultrasonicsensor;

void ultrasonicsensor_config()
{
	ultrasonicsensor = pup_ultrasonic_sensor_get_device(PBIO_PORT_ID_F);
}


/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  printf("Start!!\n");
  ultrasonicsensor_config();
    
  sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
  slp_tsk();  // メインタスクの就寝
  
  stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
  
  printf("Finish!!\n");

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
	  printf("distance : %d\n", pup_ultrasonic_sensor_distance(ultrasonicsensor));
	  if (pup_ultrasonic_sensor_presence(ultrasonicsensor))
	  {
		  printf("ultrasonic sige!!\n");
	  }
	  printf("\n");
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  printf("-------------------------");
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

