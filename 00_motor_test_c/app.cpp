#include "app.h"
#include <stdio.h>

/* センサーポートの定義 */
static const pbio_port_id_t
  left_motor_port      = PBIO_PORT_ID_E,
  right_motor_port     = PBIO_PORT_ID_B;
  
static pup_motor_t* left_motor;
static pup_motor_t* right_motor;
  
void motor_config(pbio_port_id_t l_port, pbio_port_id_t r_port)
{
	
	left_motor = pup_motor_get_device(l_port);
	right_motor = pup_motor_get_device(r_port);
	
	pup_motor_setup(left_motor, PUP_DIRECTION_COUNTERCLOCKWISE, true);
	pup_motor_setup(right_motor, PUP_DIRECTION_CLOCKWISE, true);
	
	pup_motor_reset_count(left_motor);
	pup_motor_reset_count(right_motor);
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  motor_config(left_motor_port,right_motor_port);
  printf("Start Line Trace!!\n");
    
  /* ライントレースタスクの起動 */
  sta_cyc(TRACER_TASK_CYC);
  
  slp_tsk();
  
  stp_cyc(TRACER_TASK_CYC);
  
  printf("finish!!\n");

  /* タスク終了 */
  ext_tsk();
}

void tracer_task(intptr_t unused) {
  hub_button_t pressed;
  hub_button_is_pressed(&pressed);

  if (pressed != HUB_BUTTON_CENTER)
  {
	  pup_motor_set_power(left_motor, 30);
	  pup_motor_set_power(right_motor, 30);
	  printf("left_count  : %d\n"  , pup_motor_get_count(left_motor));
	  printf("right_count : %d\n\n", pup_motor_get_count(right_motor));
  }
  else
  {
	  pup_motor_stop(left_motor);
	  pup_motor_stop(right_motor);
	  printf("motor stop!!\n");
	  wup_tsk(MAIN_TASK);
  }

  /* タスク終了 */
  ext_tsk();
}

