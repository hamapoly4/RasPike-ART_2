#include "app.h"
#include <stdio.h>

void imu_config()
{
	pbio_error_t err;
	err = hub_imu_init();
	
	if (err == PBIO_SUCCESS)
	{
		printf("complete init!!\n");
	}
	else if (err == PBIO_ERROR_FAILED)
	{
		printf("failed init!!\n");
	}
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  printf("Start!!\n");
    
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
  
  float accel[3];
  float angv[3];
  float temp;

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  hub_imu_get_acceleration(accel);
	  hub_imu_get_angular_velocity(angv);
	  temp = hub_imu_get_temperature();
	  printf("x     :%f\n", accel[0]);
	  printf("y     :%f\n", accel[1]);
	  printf("z     :%f\n", accel[2]);
	  printf("pitch :%f\n", angv[0]);
	  printf("roll  :%f\n", angv[1]);
	  printf("yaw   :%f\n", angv[2]);
	  printf("temp  :%f\n", temp);
	  printf("\n");
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */

	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

