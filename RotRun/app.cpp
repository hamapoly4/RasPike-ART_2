
#include "app.h"
#include <stdio.h>

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "enum_class.hpp"
#include "Robot.hpp"
#include "Step.hpp"
#include "Run.hpp"
#include "RotateRun.hpp"
#include "Judge.hpp"
#include "RotateAngleJudge.hpp"
#include "InitMotor.hpp"
#include "Control.hpp"
#include "RotatePControl.hpp"
#include "RotateAngleDetect.hpp"
#include "RotateAngleCorrect.hpp"
#include "SensorMonitor.hpp"
#include "EncoderMonitor.hpp"
#include "GyroSensorMonitor.hpp"
#include "Motor.hpp"
#include "GyroSensor.hpp"
#include "Button.hpp"

static const TARGET = 90;

/* ここに静的インスタンスを生成する */
static Motor        gLeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor        gRightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static GyroSensor   gAngV();
static Button       gCenterButton();

/* 動的インスタンス確保のためのポインタを定義 */
debrisys::SensorMonitor*    gRollV      = nullptr;
debrisys::SensorMonitor*    gLeftCount  = nullptr;
debrisys::SensorMonitor*    gRightCount = nullptr;

debrisys::RotateAngleCorrect*   gAngCorr    = nullptr;
debrisys::RotateAngleDetect*    gConAng     = nullptr;
debrisys::RotateAngleDetect*    gJudgeAng   = nullptr;

debrisys::Control*  gTurn = nullptr;

debrisys::Run* gRightRotate = nullptr;

debrisys::Judge* gRightJudge = nullptr;

debrisys::InitMotor* gInit = nullptr;

debrisys::Step* gStep = nullptr;

debrisys::Robot* gRobot = nullptr;

/* 動的にインスタンスを確保 */
static void create_system()
{
    gRollV      = new GyroSensorMonitor(gAngV);
    gLeftCount  = new EncoderMonitor(gLeftMotor);
    gRightCount = new EncoderMonitor(gRightMotor);
    gAngCorr    = new RotateAngleCorrect();
    gConAng     = new RotateAngleDetect(gRollV, gAngCorr);
    gJudgeAng   = new RotateAngleDetect(gRollV, gAngCorr);
    gTurn       = new RotatePControl(gConAng, TARGET);
    gRightRotate= new RotateRun(gLeftMotor, gRightMotor, gTurn, ERotDire::RIGHT);
    gRightJudge = new RotateJudge(gJudgeAng, TARGET);
    gInit       = new InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gStep       = new Step(gRightRotate, gRightJudge, gInit);
    gRobot      = new Robot(gStep, gRollV, gLeftCount, gRightCount);
}

/* 動的インスタンスを解放 */
static void destroy_system()
{
    delete gRollV;
    delete gLeftCount;
    delete gRightCount;
    delete gAngCorr;
    delete gConAng;
    delete gJudgeAng;
    delete gTurn;
    delete gRightRotate;
    delete gRightJudge;
    delete gInit;
    delete gStep;
    delete gRobot;

    gRollV      = nullptr;
    gLeftCount  = nullptr;
    gRightCount = nullptr;
    gAngCorr    = nullptr;
    gConAng     = nullptr;
    gJudgeAng   = nullptr;
    gTurn       = nullptr;
    gRightRotate= nullptr;
    gRightJudge = nullptr;
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
