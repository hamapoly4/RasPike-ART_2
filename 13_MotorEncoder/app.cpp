#include "app.h"
#include <stdio.h>
#include <cstdint>

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "Motor.hpp"
#include "Button.hpp"

/* ここに静的インスタンスを生成する */
static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

static Button button;

void write_file(int32_t l, int32_t r)
{
	FILE* fp;
	
	fp = fopen("encoder37.csv", "a");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fprintf(fp, "left, %d, right, %d\n", l, r);
		//fflush(fp); // バッファをフラッシュしてディスクに書き込む
		fclose(fp);
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
  int32_t l;
  int32_t r;
  static int cnt = 0;
  cnt++;

  if (cnt <= 300)
  {
	  /* ここに処理を書く */
	  LeftMotor.setPower(-37);
	  RightMotor.setPower(37);
	  l = LeftMotor.getCount();
	  r = RightMotor.getCount();
	  write_file(l, r);
  }
  else
  {
	  /* ここに処理を書く */
	  LeftMotor.stop();
	  RightMotor.stop();
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

