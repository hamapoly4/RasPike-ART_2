#include <stdio.h>
#include "app.h"
#include <iostream>
#include "Motor.hpp"

#define MAX 10000

static Motor LeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor RightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

void read_data(unsigned int* data)
{
	FILE* fp;
	
	fp = fopen("/home/user/camera/color_data.txt", "r");
	if (fp == NULL)
	{
		printf("No such a file\n");
		return;
	}
	else
	{
		fscanf(fp, "%d", data);
		printf("(read_data)data : %d", *data);
		fclose(fp);
	}
}

void main_task(intptr_t unused) {

    /* 周期ハンドラ開始 */
    sta_cyc(SUB_TASK_CYC);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(SUB_TASK_CYC);

    ext_tsk();  /* タスクの終了 */
}

void sub_task(intptr_t unused)
{
	static bool flag = true;
	unsigned int data = 0;
	hub_button_t pressed;
	
	if (flag)
	{
		flag = false;
		
		system("cd /home/user/camera && ./capture");
		printf("already captured!!\n");
		system("cd /home/user/camera && ./hsv_detect");
		
		read_data(&data);
		printf("(main)data : \n", data);
	}

	hub_button_is_pressed(&pressed);
	if (pressed == HUB_BUTTON_CENTER)
	{
		wup_tsk(MAIN_TASK);
	}
	else
	{
		if (data >= MAX)
		{
			printf("max!!\n");
			LeftMotor.setPower(40);
			RightMotor.setPower(40);
		}
	}
}
