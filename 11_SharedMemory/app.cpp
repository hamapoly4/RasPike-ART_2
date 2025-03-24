
#include <stdio.h>
#include <cstdint>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "app.h"

/* ここに使用するクラスのヘッダファイルをインクルード */
#include "enum_class.hpp"
#include "Robot.hpp"
#include "Route.hpp"
#include "Section.hpp"
#include "MainRun.hpp"
#include "AreaMove.hpp"
#include "DebriRemove.hpp"
#include "Circle.hpp"
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

size_t data_size = sizeof(uint32_t);
void* ptr;

static const float TARGET_ANGL[] = { 0, 42, 130, };
static const float TARGET_DIST[] = { 680, 250, };

/* ここに静的インスタンスを生成する */
static Motor        gLeftMotor(PBIO_PORT_ID_E, PUP_DIRECTION_COUNTERCLOCKWISE); // 左モータ
static Motor        gRightMotor(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);       // 右モータ
static GyroSensor   gAngV;          // ジャイロセンサ
static Button       gCenterButton;  // 中央ボタン

/* 動的インスタンス確保のためのポインタを定義 */
debrisys::SensorMonitor*    gRollV      = nullptr;  // ロール角速度
debrisys::SensorMonitor*    gLeftCount  = nullptr;  // 左回転角
debrisys::SensorMonitor*    gRightCount = nullptr;  // 右回転角

debrisys::RotateAngleCorrect*   gAngCorr    = nullptr;      // 角度補正
debrisys::RotateAngleDetect*    gConAng[9]  = {nullptr};    // 制御用旋回角度
debrisys::RotateAngleDetect*    gJudgeAng[9]= {nullptr};    // 判定用旋回角度
debrisys::RunDistDetect*        gRunDist    = nullptr;      // 走行距離

debrisys::Control* gGyroTurn[9]      = {nullptr};   // ジャイロ操作量
debrisys::Control* gEncoderTurn[18]  = {nullptr};   // エンコーダ操作量

debrisys::SubRun* gLeftRotate[5]  = {nullptr};  // 左旋回走行
debrisys::SubRun* gRightRotate[4] = {nullptr};  // 右旋回走行
debrisys::SubRun* gFrontStra[5]   = {nullptr};  // 前進走行
debrisys::SubRun* gBackStra[4]    = {nullptr};  // 後退走行

debrisys::Judge* gRotateJudge[9] = {nullptr};   // 旋回判定
debrisys::Judge* gDistJudge[9] = {nullptr};     // 走行距離判定

debrisys::InitMotor* gInit[18] = {nullptr};     // 初期化

debrisys::Step* gAreaStep = nullptr;    // エリア移動走行に関する手順(2つ)
debrisys::Step* gCir1Step = nullptr;    // サークル1走行に関する手順(4つ)
debrisys::Step* gCir2Step = nullptr;    // サークル2走行に関する手順(4つ)
debrisys::Step* gCir3Step = nullptr;    // サークル3走行に関する手順(4つ)
debrisys::Step* gCir4Step = nullptr;    // サークル4走行に関する手順(4つ)

debrisys::Circle*   gCircle     = nullptr;      // サークル1~4
debrisys::MainRun*  gBtoA       = nullptr;      // BエリアからRエリア
debrisys::MainRun*  gAarea      = nullptr;      // Rエリア内のデブリボトル除去走行
debrisys::Section*  gSection    = nullptr;      // 2区間
debrisys::Route*    gRoute      = nullptr;      // デブリリムーバル走行経路
debrisys::Robot*    gRobot      = nullptr;      // デブリリムーバル攻略号

/* 動的にインスタンスを確保 */
static void create_system()
{
    uint8_t i;

    gRollV      = new debrisys::GyroSensorMonitor(gAngV);
    gLeftCount  = new debrisys::EncoderMonitor(gLeftMotor);
    gRightCount = new debrisys::EncoderMonitor(gRightMotor);

    gAngCorr = new debrisys::RotateAngleCorrect();
    for (i = 0; i < 9; i++)
    {
        gConAng[i]  = new debrisys::RotateAngleDetect(gRollV, gAngCorr);
        gJudgeAng[i]= new debrisys::RotateAngleDetect(gRollV, gAngCorr);
    }
    gRunDist = new debrisys::RunDistDetect(gLeftCount, gRightCount);

    gGyroTurn[0]    = new debrisys::GyroPControl(gConAng[0], TARGET_ANGL[0]);   // LEFT
    gGyroTurn[1]    = new debrisys::GyroPControl(gConAng[1], TARGET_ANGL[1]);   // LEFT
    gGyroTurn[2]    = new debrisys::GyroPControl(gConAng[2], TARGET_ANGL[1]);
    gGyroTurn[3]    = new debrisys::GyroPControl(gConAng[3], TARGET_ANGL[2]);   // LEFT
    gGyroTurn[4]    = new debrisys::GyroPControl(gConAng[4], TARGET_ANGL[2]);
    gGyroTurn[5]    = new debrisys::GyroPControl(gConAng[5], TARGET_ANGL[1]);
    gGyroTurn[6]    = new debrisys::GyroPControl(gConAng[6], TARGET_ANGL[1]);   // LEFT
    gGyroTurn[7]    = new debrisys::GyroPControl(gConAng[7], TARGET_ANGL[2]);
    gGyroTurn[8]    = new debrisys::GyroPControl(gConAng[8], TARGET_ANGL[2]);   // LEFT
    for (i = 0; i < 9; i++)
    {
        gEncoderTurn[i] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::ROTATE);
    }
    for (i = 9; i < 18; i++)
    {
        gEncoderTurn[i] = new debrisys::EncoderPDControl(gLeftCount, gRightCount, debrisys::EncoderPDControl::ERun::STRAIGHT);
    }

    /* 左旋回 */
    gLeftRotate[0]  = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[0], gEncoderTurn[0], debrisys::ERotDire::LEFT);
    gLeftRotate[1]  = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[1], gEncoderTurn[1], debrisys::ERotDire::LEFT);
    gLeftRotate[2]  = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[3], gEncoderTurn[2], debrisys::ERotDire::LEFT);
    gLeftRotate[3]  = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[6], gEncoderTurn[3], debrisys::ERotDire::LEFT);
    gLeftRotate[4]  = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[8], gEncoderTurn[4], debrisys::ERotDire::LEFT);

    /* 右旋回 */
    gRightRotate[0] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[2], gEncoderTurn[5], debrisys::ERotDire::RIGHT);
    gRightRotate[1] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[4], gEncoderTurn[6], debrisys::ERotDire::RIGHT);
    gRightRotate[2] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[5], gEncoderTurn[7], debrisys::ERotDire::RIGHT);
    gRightRotate[3] = new debrisys::RotateRun(gLeftMotor, gRightMotor, gGyroTurn[7], gEncoderTurn[8], debrisys::ERotDire::RIGHT);

    /* 前進 */
    gFrontStra[0]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[9], debrisys::EStraDire::FRONT);
    gFrontStra[1]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[10], debrisys::EStraDire::FRONT);
    gFrontStra[2]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[11], debrisys::EStraDire::FRONT);
    gFrontStra[3]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[12], debrisys::EStraDire::FRONT);
    gFrontStra[4]   = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[13], debrisys::EStraDire::FRONT);

    /* 後退 */
    gBackStra[0]    = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[14], debrisys::EStraDire::BEHIND);
    gBackStra[1]    = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[15], debrisys::EStraDire::BEHIND);
    gBackStra[2]    = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[16], debrisys::EStraDire::BEHIND);
    gBackStra[3]    = new debrisys::StraightRun(gLeftMotor, gRightMotor, gEncoderTurn[17], debrisys::EStraDire::BEHIND);

    /* 旋回角度判定 */
    gRotateJudge[0] = new debrisys::RotateAngleJudge(gJudgeAng[0], TARGET_ANGL[0]);
    gRotateJudge[1] = new debrisys::RotateAngleJudge(gJudgeAng[1], TARGET_ANGL[1]);
    gRotateJudge[2] = new debrisys::RotateAngleJudge(gJudgeAng[2], TARGET_ANGL[1]);
    gRotateJudge[3] = new debrisys::RotateAngleJudge(gJudgeAng[3], TARGET_ANGL[2]);
    gRotateJudge[4] = new debrisys::RotateAngleJudge(gJudgeAng[4], TARGET_ANGL[2]);
    gRotateJudge[5] = new debrisys::RotateAngleJudge(gJudgeAng[5], TARGET_ANGL[1]);
    gRotateJudge[6] = new debrisys::RotateAngleJudge(gJudgeAng[6], TARGET_ANGL[1]);
    gRotateJudge[7] = new debrisys::RotateAngleJudge(gJudgeAng[7], TARGET_ANGL[2]);
    gRotateJudge[8] = new debrisys::RotateAngleJudge(gJudgeAng[8], TARGET_ANGL[2]);

    /* 走行距離判定 */
    gDistJudge[0] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[0]);
    gDistJudge[1] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[2] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[3] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[4] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[5] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[6] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[7] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);
    gDistJudge[8] = new debrisys::RunDistJudge(gRunDist, TARGET_DIST[1]);

    for (i = 0; i < 18; i++)
    {
        gInit[i] = new debrisys::InitMotor(gLeftCount, gRightCount, gLeftMotor, gRightMotor);
    }

    gAreaStep = new debrisys::Step[2] {
        debrisys::Step(gLeftRotate[0], gRotateJudge[0], gInit[0]),  // 手順1
        debrisys::Step(gFrontStra[0], gDistJudge[0], gInit[1])      // 手順2
    };
    gCir1Step = new debrisys::Step[4] {
        debrisys::Step(gLeftRotate[1], gRotateJudge[1], gInit[2]),    // 手順1
        debrisys::Step(gFrontStra[1], gDistJudge[1], gInit[3]),       // 手順2
        debrisys::Step(gBackStra[0], gDistJudge[2], gInit[4]),        // 手順3
        debrisys::Step(gRightRotate[0], gRotateJudge[2], gInit[5])    // 手順4
    };
    gCir2Step = new debrisys::Step[4] {
        debrisys::Step(gLeftRotate[2], gRotateJudge[3], gInit[6]),    // 手順1
        debrisys::Step(gFrontStra[2], gDistJudge[3], gInit[7]),       // 手順2
        debrisys::Step(gBackStra[1], gDistJudge[4], gInit[8]),        // 手順3
        debrisys::Step(gRightRotate[1], gRotateJudge[4], gInit[9])    // 手順4
    };
    gCir3Step = new debrisys::Step[4] {
        debrisys::Step(gRightRotate[2], gRotateJudge[5], gInit[10]),  // 手順1
        debrisys::Step(gFrontStra[3], gDistJudge[5], gInit[11]),      // 手順2
        debrisys::Step(gBackStra[2], gDistJudge[6], gInit[12]),       // 手順3
        debrisys::Step(gLeftRotate[3], gRotateJudge[6], gInit[13])    // 手順4
    };
    gCir4Step = new debrisys::Step[4] {
        debrisys::Step(gRightRotate[3], gRotateJudge[7], gInit[14]),  // 手順1
        debrisys::Step(gFrontStra[4], gDistJudge[7], gInit[15]),      // 手順2
        debrisys::Step(gBackStra[3], gDistJudge[8], gInit[16]),       // 手順3
        debrisys::Step(gLeftRotate[4], gRotateJudge[8], gInit[17])    // 手順4
    };

    gCircle = new debrisys::Circle[4] {
        debrisys::Circle(gCir1Step, true),
        debrisys::Circle(gCir2Step, true),
        debrisys::Circle(gCir3Step, false),
        debrisys::Circle(gCir4Step, false)
    };

    gBtoA   = new debrisys::AreaMove(gAreaStep);
    gAarea  = new debrisys::DebriRemove(gCircle);
    gSection= new debrisys::Section[2] {
        debrisys::Section(gBtoA),
        debrisys::Section(gAarea)
    };
    gRoute  = new debrisys::Route(gSection);
    gRobot  = new debrisys::Robot(gRoute, gRollV, gLeftCount, gRightCount);
}

/* 動的インスタンスを解放 */
static void destroy_system()
{
    uint8_t i;
    delete  gRobot;
    delete  gRoute;
    delete[] gSection;
    delete  gAarea;
    delete  gBtoA;
    delete[] gCircle;
    delete[] gCir4Step;
    delete[] gCir3Step;
    delete[] gCir2Step;
    delete[] gCir1Step;
    delete[] gAreaStep;
    for (i = 0; i < 18; i++)
    {
        delete gInit[i];
    }
    for (i = 0; i < 9; i++)
    {
        delete gRotateJudge[i];
        delete gDistJudge[i];
    }
    for (i = 0; i < 4; i++)
    {
        delete gBackStra[i];
    }
    for (i = 0; i < 5; i++)
    {
        delete gFrontStra[i];
    }
    for (i = 0; i < 4; i++)
    {
        delete gRightRotate[i];
    }
    for (i = 0; i < 5; i++)
    {
        delete gLeftRotate[i];
    }
    for (i = 0; i < 18; i++)
    {
        delete gEncoderTurn[i];
    }
    for (i = 0; i < 9; i++)
    {
        delete gGyroTurn[i];
    }
    delete  gRunDist;
    for (i = 0; i < 9; i++)
    {
        delete gConAng[i];
        delete gJudgeAng[i];
    }
    delete  gAngCorr;
    delete  gRightCount;
    delete  gLeftCount;
    delete  gRollV;
}

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused)
{
	// 共有メモリを開く
    int fd = shm_open("yuta", O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        ext_tsk();
    }

    // 共有メモリのマッピング
    ptr = mmap(0, data_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        ext_tsk();
    }
	
    create_system();    // システムを生成

    sta_cyc(SUB_TASK_CYC);  // サブタスクの起動

    slp_tsk();              // メインタスクの就寝
    
    stp_cyc(SUB_TASK_CYC);  // サブタスクの停止

    destroy_system();   // システムを破棄
    
    // 後処理
    munmap(ptr, data_size);
    close(fd);

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
		debrisys::Circle::setBluePixels(*static_cast<int*>(ptr));	// データの読み取り
        gRobot->conquer();
    }

    ext_tsk();  // タスク終了
}
