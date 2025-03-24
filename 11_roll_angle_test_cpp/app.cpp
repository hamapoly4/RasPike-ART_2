#include "app.h"
#include <stdio.h>
#include "IMU.hpp"
#include "RollAngle.hpp"

static IMU Imu;
static RollAngle rollAngle;

void write_file(uint16_t cnt_1s, float ang_v[3])
{
	FILE* fp;
	fp = fopen("angle_data_02.csv", "a");
	if (fp == NULL)
	{
		printf("fp is NULL!!\n");
		return;
	}
	else
	{
		fprintf(fp, "%d,%f,%f,%f\n", cnt_1s, ang_v[0], ang_v[1], ang_v[2]);
		fclose(fp);
	}
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
  // ここからプログラムを書く
  sta_cyc(SUB_TASK_CYC); // ジャイロセンサ監視開始
  
  slp_tsk();

  stp_cyc(SUB_TASK_CYC); // ジャイロセンサ監視終了

  ext_tsk();  // タスク終了
}

/* サブタスク(2ms周期で関数コールされる) */
void sub_task(intptr_t unused) {
  hub_button_t pressed;
  int angle;
  float ang_raw[3];	// IMU角加速度 格納用配列
  static uint16_t cnt_1ms = 0;
  static uint16_t cnt_1s = 0;

  hub_button_is_pressed(&pressed);
  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  cnt_1ms += 2;
	  Imu.getAngularVelocity(ang_raw);
	  angle = rollAngle.getRollAngle(ang_raw[0], 2);
	  
	  if (cnt_1ms == 1000)
	  {
		  cnt_1s++;
		  //write_file(cnt_1s, ang_v);
		  printf("%2d, X:%d\n", cnt_1s, angle); // 角度情報を文字列に
		  cnt_1ms = 0;
	  }
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }
}

