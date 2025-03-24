#include "app.h"
#include <stdio.h>

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "Motor.hpp"
#include "IMU.hpp"
#include "RollAngle.hpp"

/* ここに静的インスタンスを生成する */
static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static IMU Imu;
static RollAngle rollAngle;

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
  float ang_raw[3];	// IMU角加速度 格納用配列
  int angle;
  int16_t leftcnt;
  int16_t rightcnt;
  int diff;
  static int old_diff;
  const float pgain = 1.5;
  const float dgain = 1.5;
  int pvalue;
  int dvalue;
  int turn;
  hub_button_is_pressed(&pressed);

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  Imu.getAngularVelocity(ang_raw);
	  angle = rollAngle.getRollAngle(ang_raw[0], 10);
	  leftcnt = LeftMotor.getCount();
	  rightcnt = RightMotor.getCount();
	  if (angle <= -90)
	  {
		  printf("angle : %d\n", angle);
		  printf("leftcnt  : %d\n", leftcnt);
		  printf("rightcnt : %d\n", rightcnt);
		  LeftMotor.stop();
		  RightMotor.stop();
		  wup_tsk(MAIN_TASK);   // メインタスクの起床
	  }
	  else
	  {
		  diff = leftcnt + rightcnt;
		  pvalue = static_cast<int>(diff * pgain);
		  dvalue = (old_diff - diff) * dgain;
		  old_diff = diff;
		  turn = pvalue + dvalue;
		  LeftMotor.setPower(45 - turn);
		  RightMotor.setPower(-(45 + turn));
	  }
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  LeftMotor.stop();
	  RightMotor.stop();
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

