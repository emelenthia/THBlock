#include "FPSer.h"
#include<DxLib.h>
#include"Flag.h"

FPSer::FPSer()
{
}


FPSer::~FPSer()
{
}


void FPSer::CountFPS()
{
	Wait();

	if (!count)
	{
		time_a = GetNowCount();
	}
	if (count == checknum - 1)
	{
		time_b = GetNowCount();
		FPS = 1000 / (((time_b - time_a) ? (time_b > time_a ? time_b - time_a : time_b + (INT_MAX - time_a)) : checknum) / (double)checknum);
		count = 0;
	}
	else
	{
		count++;
	}
	DrawFormatString(560, 0, Flag::color.white, "fps:%.2f", FPS);
}


void FPSer::Wait()
{
	int tookTime = GetNowCount() - time_a;	//������������
	int waitTime = count * 1000 / setfps - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}