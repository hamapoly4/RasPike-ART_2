
#include <stdio.h>
#include "app.h"

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "enum_class.hpp"
#include "Robot.hpp"
#include "Route.hpp"
#include "Section.hpp"
#include "MainRun.hpp"
#include "AreaMove.hpp"
#include "Step.hpp"
#include "SubRun.hpp"
#include "RotateRun.hpp"
#include "StraightRun.hpp"
#include "Judge.hpp"
#include "RotateAngleJudge.hpp"
#include "RunDistJudge.hpp"
#include "InitMotor.hpp"
#include "Control.hpp"
#include "GyroPControl.hpp"
#include "EncoderPDControl.hpp"
#include "RotateAngleDetect.hpp"
#include "RotateAngleCorrect.hpp"
#include "RunDistDetect.hpp"
#include "SensorMonitor.hpp"
#include "EncoderMonitor.hpp"
#include "GyroSensorMonitor.hpp"
#include "Motor.hpp"
#include "GyroSensor.hpp"
#include "Button.hpp"

static const float TARGET[2] = { 85, 680 };

/* ここに静的インスタンスを生成する */
static Motor        gLeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor        gRightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static GyroSensor   gAngV;
static Button       gCenterButton;

/* 動的インスタンス確保のためのポインタを定義 */
debrisys::SensorMonitor*    gRollV      = nullptr;  // ロール角速度
debrisys::SensorMonitor*    gLeftCount  = nullptr;  // 左回転角
debrisys::SensorMonitor*    gRightCount = nullptr;  // 右回転角

debrisys::RotateAngleCorrect*   gAngCorr    = nullptr;  // 角度補正
debrisys::RotateAngleDetect*    gConAng     = nullptr;  // 制御用旋回角度
debrisys::RotateAngleDetect*    gJudgeAng   = nullptr;  // 判定用旋回角度
debrisys::RunDistDetect*        gRunDist    = nullptr;  // 走行距離

debrisys::Control* gGyroTurn        = nullptr;      // ジャイロ操作量
debrisys::Control* gEncoderTurn[2]  = {nullptr};    // エンコーダ操作量

debrisys::SubRun* gLeftRotate = nullptr;    // 左旋回走行
debrisys::SubRun* gFrontStra   = nullptr;   // 前進走行

debrisys::Judge* gLeftJudge = nullptr;  // 左旋回判定
debrisys::Judge* gFrontJudge = nullptr; // 前進距離判定

debrisys::InitMotor* gInit[2] = {nullptr};  // 初期化

debrisys::Step*     gStep[2]  = {nullptr};  // 手順
debrisys::MainRun*  gAreaMove = nullptr;    // R→Yエリア
debrisys::Section*  gSection  = nullptr;    // R→Yエリアへの移動区間
debrisys::Route*    gRoute    = nullptr;    // デブリリムーバル走行経路
debrisys::Robot*    gRobot    = nullptr;    // デブリリムーバル攻略号

/* 動的にインスタンスを確保 */
static void create_system()
{
    gRollV          = new debrisys::GyroSensorMonitor(gAngV);
    gLeftCount      = new debrisys::EncoderMonitor(gLeftMotor);
    gRightCount     = new debrisys::EncoderMonitor(gRightMotor);
    gAngCorr        = new debrisys::RotateAngleCorrect();
    gConAng         = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gJudgeAng       = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gRunDist        = new debrisys::RunDistDetect(gLeftCount, gRightCount);
    gGyroTurn       = new debrisys::GyroPControl(gConAng, TARGET[0]);
    gEncoderTurn[0] = new debrisys::EncoderPDControl(gLeftCount, gRightCount);
    gEncoderTurn[1] = new debrisys::EncoderPDControl(gLeftCount, gRightCount);
    gLeftRotate     = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn, gEncoderTurn[0], debrisys::ERotDire::LEFT);
    gFrontStra      = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[1], debrisys::EStraDire::FRONT);
    gLeftJudge      = new debrisys::RotateAngleJudge(gJudgeAng, TARGET[0]);
    gFrontJudge     = new debrisys::RunDistJudge(gRunDist, TARGET[1]);
    gInit[0]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gInit[1]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gStep[0]        = new debrisys::Step(gLeftRotate, gLeftJudge, gInit[0]);
    gStep[1]        = new debrisys::Step(gFrontStra, gFrontJudge, gInit[1]);
    gAreaMove       = new debrisys::AreaMove(gStep[0], gStep[1]);
    gSection        = new debrisys::Section(gAreaMove);
    gRoute          = new debrisys::Route(gSection);
    gRobot          = new debrisys::Robot(gStep[0], gRollV, gLeftCount, gRightCount);
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
    delete gRunDist; 
    delete gGyroTurn; 
    delete gEncoderTurn[0]; 
    delete gEncoderTurn[1]; 
    delete gLeftRotate; 
    delete gFrontStra; 
    delete gLeftJudge; 
    delete gFrontJudge; 
    delete gInit[0]; 
    delete gInit[1]; 
    delete gStep[0];
    delete gStep[1];
    delete gAreaMove; 
    delete gSection; 
    delete gRoute;
    delete gRobot;

    gRollV          = nullptr;
    gLeftCount      = nullptr;
    gRightCount     = nullptr;
    gAngCorr        = nullptr;
    gConAng         = nullptr;
    gJudgeAng       = nullptr;
    gRunDist        = nullptr;
    gGyroTurn       = nullptr;
    gEncoderTurn[0] = nullptr;
    gEncoderTurn[1] = nullptr;
    gLeftRotate     = nullptr;
    gFrontStra      = nullptr;
    gLeftJudge      = nullptr;
    gFrontJudge     = nullptr;
    gInit[0]        = nullptr;
    gInit[1]        = nullptr;
    gStep[0]        = nullptr;
    gStep[1]        = nullptr;
    gAreaMove       = nullptr;
    gSection        = nullptr;
    gRoute          = nullptr;
    gRobot          = nullptr;
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
    }
    else
    {
        gRobot->conquer();
    }

    ext_tsk();  // タスク終了
}
