#include "app.h"
#include <stdio.h>

static pup_device_t* colorsensor;

void color_config()
{
	colorsensor = pup_color_sensor_get_device(PBIO_PORT_ID_C);
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  printf("Start!!\n");
  
  color_config();
    
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
  
  pup_color_rgb_t rgb;
  pup_color_hsv_t hsv;

  /* ハブの中央ボタンが押されてない */
  if (pressed != HUB_BUTTON_CENTER)
  {
	  /* ここに処理を書く */
	  printf("Brightness : %d\n", pup_color_sensor_reflection(colorsensor));
	  rgb = pup_color_sensor_rgb(colorsensor);
	  hsv = pup_color_sensor_hsv(colorsensor, true);
	  printf("red : %d\n", rgb.r);
	  printf("gre : %d\n", rgb.g);
	  printf("blu : %d\n", rgb.b);
	  printf("hue : %d\n", hsv.h);
	  printf("sat : %d\n", hsv.s);
	  printf("val : %d\n", hsv.v);
	  printf("\n");
  }
  /* ハブの中央ボタンが押されている */
  else
  {
	  /* ここに処理を書く */
	  printf("------------------\n\n");
	  wup_tsk(MAIN_TASK);   // メインタスクの起床
  }

  ext_tsk();  // タスク終了
}

