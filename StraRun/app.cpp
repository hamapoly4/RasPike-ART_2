
#include "app.h"
#include <stdio.h>
#include <cstdint>

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "enum_class.hpp"
#include "Robot.hpp"
#include "Step.hpp"
#include "Run.hpp"
#include "RotateRun.hpp"
#include "StraightRun.hpp"
#include "Judge.hpp"
#include "RotateAngleJudge.hpp"
#include "RunDistJudge.hpp"
#include "InitMotor.hpp"
#include "Control.hpp"
#include "RotatePControl.hpp"
#include "StraPDControl.hpp"
#include "RotateAngleDetect.hpp"
#include "RotateAngleCorrect.hpp"
#include "RunDistDetect.hpp"
#include "SensorMonitor.hpp"
#include "EncoderMonitor.hpp"
#include "GyroSensorMonitor.hpp"
#include "Motor.hpp"
#include "GyroSensor.hpp"
#include "Button.hpp"

static const float TARGET = 90;

/* ここに静的インスタンスを生成する */
static Motor        gLeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor        gRightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static GyroSensor   gAngV;
static Button       gCenterButton;

/* 動的インスタンス確保のためのポインタを定義 */
debrisys::SensorMonitor*    gRollV      = nullptr;
debrisys::SensorMonitor*    gLeftCount  = nullptr;
debrisys::SensorMonitor*    gRightCount = nullptr;

debrisys::Control*  gTurn = nullptr;

debrisys::RunDistDetect* gRunDist = nullptr;

debrisys::Run* gFrontStra = nullptr;

debrisys::Judge* gFrontJudge = nullptr;

debrisys::InitMotor* gInit = nullptr;

debrisys::Step* gStep = nullptr;

debrisys::Robot* gRobot = nullptr;

/* 動的にインスタンスを確保 */
static void create_system()
{
    gRollV      = new debrisys::GyroSensorMonitor(gAngV);
    gLeftCount  = new debrisys::EncoderMonitor(gLeftMotor);
    gRightCount = new debrisys::EncoderMonitor(gRightMotor);
    gTurn       = new debrisys::StraPDControl(gLeftCount, gRightCount);
    gRunDist    = new debrisys::RunDistDetect(gLeftCount, gRightCount);
    gFrontStra  = new debrisys::StraightRun(gLeftMotor, gRightMotor, gTurn, debrisys::EStraDire::FRONT);
    gFrontJudge = new debrisys::RunDistJudge(gRunDist, TARGET);
    gInit       = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gStep       = new debrisys::Step(gFrontStra, gFrontJudge, gInit);
    gRobot      = new debrisys::Robot(gStep, gRollV, gLeftCount, gRightCount);
}

/* 動的インスタンスを解放 */
static void destroy_system()
{
    delete gRollV;
    delete gLeftCount;
    delete gRightCount;
    delete gTurn;
    delete gRunDist;
    delete gFrontStra;
    delete gFrontJudge;
    delete gInit;
    delete gStep;
    delete gRobot;

    gRollV      = nullptr;
    gLeftCount  = nullptr;
    gRightCount = nullptr;
    gTurn       = nullptr;
    gRunDist    = nullptr;
    gFrontStra  = nullptr;
    gFrontJudge = nullptr;
    gInit       = nullptr;
    gStep       = nullptr;
    gRobot      = nullptr;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused)
{
    create_system();

    sta_cyc(SUB_TASK_CYC);  // サブタスクの起動
  
    slp_tsk();  // メインタスクの就寝
  
    stp_cyc(SUB_TASK_CYC);  // サブタスクの停止
  
    destroy_system();

	printf("------------攻略終了------------\n");

    ext_tsk();  // タスク終了
}

/* サブタスク(10ms周期で関数コールされる) */
void sub_task(intptr_t unused)
{
    if (gCenterButton.isCenterPressed())
    {
        wup_tsk(MAIN_TASK);
        gLeftMotor.stop();
        gRightMotor.stop();
    }
    else
    {
        gRobot->conquer();
    }

    ext_tsk();  // タスク終了
}
