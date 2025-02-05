#include "GyroStopP.h"
#include <stdio.h>

float GyroStopP::pgain = 0.15;
int   GyroStopP::threathold = -350;

GyroStopP::GyroStopP()
{
    ;
}

int GyroStopP::getTurn(int ang)
{
	angle = ang;
    calcTurn();
    return turn;
}

void GyroStopP::calcTurn()
{
    calcP();
    turn = Pvalue;
    if (turn > 13.35)
    {
		turn = 13.35;
	}
}

void GyroStopP::calcP()
{
    diff = threathold - angle;
    if (threathold < 0)
    {
        diff = -diff;
    }

    Pvalue = diff * pgain;
}
