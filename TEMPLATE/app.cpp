#include "app.h"
#include <stdio.h>
#include "Motor.hpp"

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  printf("Start!!\n");
    
  /* ライントレースタスクの起動 */
  sta_cyc(TRACER_TASK_CYC);
  
  slp_tsk();
  
  stp_cyc(TRACER_TASK_CYC);
  
  printf("Finish!!\n");

  /* タスク終了 */
  ext_tsk();
}

void tracer_task(intptr_t unused) {
  hub_button_t pressed;
  hub_button_is_pressed(&pressed);

  if (pressed != HUB_BUTTON_CENTER)
  {
	  LeftMotor.setPower(60);
	  RightMotor.setPower(60);
	  printf("left count  : %d\n"  , LeftMotor.getCount());
	  printf("right count : %d\n\n", RightMotor.getCount());
  }
  else
  {
	  LeftMotor.stop();
	  RightMotor.stop();
	  printf("motor stop!!\n");
	  wup_tsk(MAIN_TASK);
  }

  /* タスク終了 */
  ext_tsk();
}

