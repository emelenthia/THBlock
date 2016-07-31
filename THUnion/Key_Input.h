#pragma once
//#include"Options.h"

class Key_Input //�L�[�{�[�h����̓��͂��󂯎��N���X
{
public:
	static Key_Input* instance;
	//// �B��̃A�N�Z�X�o�H
	static Key_Input* GetInstance()
	{
		if (instance == nullptr)instance = new Key_Input();
		return instance;
	}


	int GetKeyTime(int key) { return buff_time[key]; } //key��DX���C�u�����̂ɏ�����
	bool GetKeyOn(int key) { return (bool)buff[key]; } //key��DX���C�u�����̂ɏ�����
	int i;
	void KeyUpdate();
	int talkingflag; //�b�����t���O
	int JoyPadInput;
	int AnalogInputx;
	int AnalogInputy;
	//Options* options;
	//D_XINPUT_STATE xboxInput;

private:
	char buff[256]; //GetHitKeyStateAll()�̈�����char*�Ȃ̂�
	int buff_time[256]; //���ꂼ��̃L�[�̉���������
	Key_Input();
	~Key_Input();
	Key_Input(const Key_Input& rhs);
	Key_Input& operator=(const Key_Input& rhs);
};

