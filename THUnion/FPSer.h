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
	void Wait(); //FPS‚Ì’²®
	const int setfps = 60; //FPS‚ÌÅ‘å’l
	const int checknum = 60; //FPSŒvZ‚Ì¸“x
};

