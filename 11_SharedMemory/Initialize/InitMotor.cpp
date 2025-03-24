#include "InitMotor.hpp"
#include <stdio.h>

using namespace debrisys;   // 名前空間debrisys

/* 静的データメンバの初期化 */
float	InitMotor::sampl[SAMP_MAX] = { 0 };
float	InitMotor::sampr[SAMP_MAX] = { 0 };
uint8_t	InitMotor::idx = 0;

/* 初期化する */
void InitMotor::init()
{
    switch (mState)
    {
        case EState::MOTOR_STOP :
            stopMotor();
            break;
        case EState::ENCODER_RESET :
            resetEncoder();
            break;
        default:
            break;
    }
}

/* モータを停止する */
void InitMotor::stopMotor()
{
	uint8_t cnt = 0;
	uint8_t i;

    if (mStopFlag)  // モータ停止フラグが立っているか判定
    {
        mStopFlag = false;  // モータ停止フラグを降ろす
        mLeftMotor.stop();  // 左モータを停止
        mRightMotor.stop(); // 右モータを停止
        return;
    }

	sampl[idx] = mLeftCount->readData();
	sampr[idx] = mRightCount->readData();
	printf("%d, leftcount  : %f\n", idx, sampl[idx]);
	printf("    rightcount : %f\n", idx, sampr[idx]);
	idx++;
	if (idx >= SAMP_MAX)
	{
		idx = 0;
	}
	
	for (i = 0; i < (SAMP_MAX - 1); i++)
	{
		if (sampl[i] == sampl[i + 1])
		{
			cnt++;
		}
		
		if (sampr[i] == sampr[i + 1])
		{
			cnt++;
		}
	}
	
	if (cnt >= (SAMP_MAX * 2 - 2))
	{
		switchState(EState::ENCODER_RESET);
		printf("エンコーダリセット状態に遷移\n");
	}
}

/* エンコーダをリセットする */
void InitMotor::resetEncoder()
{
    float leftcount;
    float rightcount;

    if (mResetFlag) // エンコーダリセットフラグが立っているか判定
    {
        mResetFlag = false;     // エンコーダリセットフラグを降ろす
        sampDataReset();        // サンプリングデータをリセット
        mLeftCount->init();     // 左回転角をリセット
        mRightCount->init();    // 右回転角をリセット
        return;
    }

    leftcount  = mLeftCount->readData();    // 左回転角読み取り
    rightcount = mRightCount->readData();   // 右回転角読み取り
    printf("leftcount  : %f\n", leftcount);
    printf("rightcount : %f\n", rightcount);
    if (leftcount == 0 && rightcount == 0)  // 左右回転角がリセットできたか判定
    {
        switchState(EState::FIN);   // 終了状態に遷移
        printf("初期化終了状態に遷移\n");
    }
}

/* サンプリングデータをリセットする */
void InitMotor::sampDataReset()
{
	uint8_t i;
	for (i = 0; i < SAMP_MAX; i++)
	{
		sampl[i] = 0;
		sampr[i] = 0;
	}
	idx = 0;
}

/* 状態を切り替える */
void InitMotor::switchState(EState state)
{
    mState = state;
}

