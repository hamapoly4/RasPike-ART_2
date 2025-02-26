
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

static const float TARGET[4] = { 85, 85, 680, 680, };

/* ここに静的インスタンスを生成する */
static Motor        gLeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE);
static Motor        gRightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);
static GyroSensor   gAngV;
static Button       gCenterButton;

/* 動的インスタンス確保のためのポインタを定義 */
debrisys::SensorMonitor*    gRollV      = nullptr;  // ロール角速度
debrisys::SensorMonitor*    gLeftCount  = nullptr;  // 左回転角
debrisys::SensorMonitor*    gRightCount = nullptr;  // 右回転角

debrisys::RotateAngleCorrect*   gAngCorr    = nullptr;      // 角度補正
debrisys::RotateAngleDetect*    gConAng[2]  = {nullptr};    // 制御用旋回角度
debrisys::RotateAngleDetect*    gJudgeAng[2]= {nullptr};    // 判定用旋回角度
debrisys::RunDistDetect*        gRunDist    = nullptr;      // 走行距離

debrisys::Control* gGyroTurn[2]     = {nullptr};    // ジャイロ操作量
debrisys::Control* gEncoderTurn[4]  = {nullptr};    // エンコーダ操作量

debrisys::SubRun* gLeftRotate[2] = {nullptr};   // 左旋回走行
debrisys::SubRun* gFrontStra[2]   = {nullptr};  // 前進走行

debrisys::Judge* gRightJudge[2] = {nullptr};    // 右旋回判定
debrisys::Judge* gFrontJudge[2] = {nullptr};    // 前進距離判定

debrisys::InitMotor* gInit[4] = {nullptr};  // 初期化

debrisys::Step*     gStep[4]    = {nullptr};    // 手順
debrisys::MainRun*  gAreaMove[2]= {nullptr};    // 各エリア
debrisys::Section*  gSection    = nullptr;      // R→Yエリアへの移動区間
debrisys::Route*    gRoute      = nullptr;      // デブリリムーバル走行経路
debrisys::Robot*    gRobot      = nullptr;      // デブリリムーバル攻略号

/* 動的にインスタンスを確保 */
static void create_system()
{
    gRollV          = new debrisys::GyroSensorMonitor(gAngV);
    gLeftCount      = new debrisys::EncoderMonitor(gLeftMotor);
    gRightCount     = new debrisys::EncoderMonitor(gRightMotor);
    gAngCorr        = new debrisys::RotateAngleCorrect();
    gConAng[0]      = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gConAng[1]      = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gJudgeAng[0]    = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gJudgeAng[1]    = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    gRunDist        = new debrisys::RunDistDetect(gLeftCount, gRightCount);
    gGyroTurn[0]    = new debrisys::GyroPControl(gConAng[0], TARGET[0]);
    gGyroTurn[1]    = new debrisys::GyroPControl(gConAng[1], TARGET[1]);
    gEncoderTurn[0] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::ROTATE);
    gEncoderTurn[1] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::ROTATE);
    gEncoderTurn[2] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::STRAIGHT);
    gEncoderTurn[3] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::STRAIGHT);
    gLeftRotate[0] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[0], gEncoderTurn[0], debrisys::ERotDire::LEFT);
    gLeftRotate[1] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[1], gEncoderTurn[1], debrisys::ERotDire::LEFT);
    gFrontStra[0]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[2], debrisys::EStraDire::FRONT);
    gFrontStra[1]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[3], debrisys::EStraDire::FRONT);
    gRightJudge[0]  = new debrisys::RotateAngleJudge(gJudgeAng[0], TARGET[0]);
    gRightJudge[1]  = new debrisys::RotateAngleJudge(gJudgeAng[1], TARGET[1]);
    gFrontJudge[0]  = new debrisys::RunDistJudge(gRunDist, TARGET[2]);
    gFrontJudge[1]  = new debrisys::RunDistJudge(gRunDist, TARGET[3]);
    gInit[0]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gInit[1]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gInit[2]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gInit[3]        = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    gStep[0]        = new debrisys::Step(gLeftRotate[0], gRightJudge[0], gInit[0]);
    gStep[1]        = new debrisys::Step(gFrontStra[0], gFrontJudge[0], gInit[1]);
    gStep[2]        = new debrisys::Step(gLeftRotate[1], gRightJudge[1], gInit[2]);
    gStep[3]        = new debrisys::Step(gFrontStra[1], gFrontJudge[1], gInit[3]);
    gAreaMove[0]    = new debrisys::AreaMove(gStep[0], gStep[1]);
    gAreaMove[1]    = new debrisys::AreaMove(gStep[2], gStep[3]);
    gSection        = new debrisys::Section[2] { (gAreaMove[0]), (gAreaMove[1]), };
    gRoute          = new debrisys::Route(gSection);
    gRobot          = new debrisys::Robot(gRoute, gRollV, gLeftCount, gRightCount);
}

/* 動的インスタンスを解放 */
static void destroy_system()
{
    delete   gRollV; 
    delete   gLeftCount; 
    delete   gRightCount; 
    delete   gAngCorr; 
    delete   gConAng[0];
    delete   gConAng[1]; 
    delete   gJudgeAng[0]; 
    delete   gJudgeAng[1]; 
    delete   gRunDist; 
    delete   gGyroTurn[0]; 
    delete   gGyroTurn[1]; 
    delete   gEncoderTurn[0]; 
    delete   gEncoderTurn[1]; 
    delete   gEncoderTurn[2]; 
    delete   gEncoderTurn[3]; 
    delete   gLeftRotate[0]; 
    delete   gLeftRotate[1]; 
    delete   gFrontStra[0]; 
    delete   gFrontStra[1]; 
    delete   gRightJudge[0]; 
    delete   gRightJudge[1]; 
    delete   gFrontJudge[0]; 
    delete   gFrontJudge[1]; 
    delete   gInit[0]; 
    delete   gInit[1]; 
    delete   gInit[2]; 
    delete   gInit[3]; 
    delete   gStep[0]; 
    delete   gStep[1]; 
    delete   gStep[2]; 
    delete   gStep[3]; 
    delete   gAreaMove[0]; 
    delete   gAreaMove[1]; 
    delete[] gSection; 
    delete   gRoute; 
    delete   gRobot; 

    gRollV          = nullptr;
    gLeftCount      = nullptr;
    gRightCount     = nullptr;
    gAngCorr        = nullptr;
    gConAng[0]      = nullptr;
    gConAng[1]      = nullptr;
    gJudgeAng[0]    = nullptr;
    gJudgeAng[1]    = nullptr;
    gRunDist        = nullptr;
    gGyroTurn[0]    = nullptr;
    gGyroTurn[1]    = nullptr;
    gEncoderTurn[0] = nullptr;
    gEncoderTurn[1] = nullptr;
    gEncoderTurn[2] = nullptr;
    gEncoderTurn[3] = nullptr;
    gLeftRotate[0] = nullptr;
    gLeftRotate[1] = nullptr;
    gFrontStra[0]   = nullptr;
    gFrontStra[1]   = nullptr;
    gRightJudge[0]  = nullptr;
    gRightJudge[1]  = nullptr;
    gFrontJudge[0]  = nullptr;
    gFrontJudge[1]  = nullptr;
    gInit[0]        = nullptr;
    gInit[1]        = nullptr;
    gInit[2]        = nullptr;
    gInit[3]        = nullptr;
    gStep[0]        = nullptr;
    gStep[1]        = nullptr;
    gStep[2]        = nullptr;
    gStep[3]        = nullptr;
    gAreaMove[0]    = nullptr;
    gAreaMove[1]    = nullptr;
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
