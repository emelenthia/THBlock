#pragma once
class FPSer
{
public:
	FPSer();
	~FPSer();
	int time_a = 0;
	int time_b = 0;
	void CountFPS();
	int count = 0;
	double FPS = 0;
	void Wait(); //FPS�̒���
	const int setfps = 60; //FPS�̍ő�l
	const int checknum = 60; //FPS�v�Z�̐��x
};

