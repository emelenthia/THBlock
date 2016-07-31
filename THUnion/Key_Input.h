#pragma once
//#include"Options.h"

class Key_Input //キーボードからの入力を受け取るクラス
{
public:
	static Key_Input* instance;
	//// 唯一のアクセス経路
	static Key_Input* GetInstance()
	{
		if (instance == nullptr)instance = new Key_Input();
		return instance;
	}


	int GetKeyTime(int key) { return buff_time[key]; } //keyはDXライブラリのに準ずる
	bool GetKeyOn(int key) { return (bool)buff[key]; } //keyはDXライブラリのに準ずる
	int i;
	void KeyUpdate();
	int talkingflag; //話し中フラグ
	int JoyPadInput;
	int AnalogInputx;
	int AnalogInputy;
	//Options* options;
	//D_XINPUT_STATE xboxInput;

private:
	char buff[256]; //GetHitKeyStateAll()の引数がchar*なので
	int buff_time[256]; //それぞれのキーの押し下時間
	Key_Input();
	~Key_Input();
	Key_Input(const Key_Input& rhs);
	Key_Input& operator=(const Key_Input& rhs);
};

