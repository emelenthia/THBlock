#include "Key_Input.h"
#include<DxLib.h>

Key_Input* Key_Input::instance;

Key_Input::Key_Input()
{
	//options = Options::GetInstance();
	instance = nullptr;
}


Key_Input::~Key_Input()
{
}


void Key_Input::KeyUpdate()
{
	GetHitKeyStateAll(buff);

	//�p�b�h���͂��L�[���͂ɕϊ�����
	if (GetJoypadNum())
	{
		if (1) //Xbox�R���g���[���[�łȂ�
		{
			JoyPadInput = GetJoypadInputState(DX_INPUT_PAD1);
			GetJoypadAnalogInput(&AnalogInputx, &AnalogInputy, DX_INPUT_PAD1);
			if ((JoyPadInput&PAD_INPUT_UP) || AnalogInputy > 100)
			{
				buff[KEY_INPUT_UP] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_RIGHT) || AnalogInputx < -100)
			{
				buff[KEY_INPUT_RIGHT] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_DOWN) || AnalogInputy < -100)
			{
				buff[KEY_INPUT_DOWN] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_LEFT) || AnalogInputx > 100)
			{
				buff[KEY_INPUT_LEFT] = 1;
			}
			if (JoyPadInput&PAD_INPUT_3)
			{
				buff[KEY_INPUT_Z] = 1;
			}
			if (JoyPadInput&PAD_INPUT_1)
			{
				buff[KEY_INPUT_X] = 1;
			}
			if (JoyPadInput&PAD_INPUT_5)
			{
				buff[KEY_INPUT_A] = 1;
			}
			if (JoyPadInput&PAD_INPUT_6)
			{
				buff[KEY_INPUT_D] = 1;
			}

		}
		else
		{
			//GetJoypadXInputState();
		}
	}
	i = 0;

	/*
	//�g���ĂȂ��L�[�̏���
	if (options->keyconfingflag) //�L�[�R���t�B�O���ł͂Ȃ��BTODO:�G���[���Ƃ����悤
	{
	}
	else
	{
		while (i < 256)
		{
			if (buff[i])
			{
				for (int n = 0; n < options->key_max; n++)
				{
					if (i == options->key_deside[n])
					{
						break;
					}
					if (n == options->key_max - 1)
					{
						buff[i] = 0;
					}
				}
			}
			i++;
		}

		i = 0;
		
		//�L�[�R���t�B�O�ɂ��L�[�̕ϊ�
		if (buff[options->key_deside[0]]) //���L�[
		{
			buff[options->key_deside[0]] = 0;
			buff[KEY_INPUT_UP] = 1;
		}
		else if (buff[options->key_deside[1]]) //���L�[
		{
			buff[options->key_deside[1]] = 0;
			buff[KEY_INPUT_RIGHT] = 1;
		}
		else if (buff[options->key_deside[2]]) //���L�[
		{
			buff[options->key_deside[2]] = 0;
			buff[KEY_INPUT_DOWN] = 1;
		}
		else if (buff[options->key_deside[3]]) //���L�[
		{
			buff[options->key_deside[3]] = 0;
			buff[KEY_INPUT_LEFT] = 1;
		}
		else if (buff[options->key_deside[4]]) //A�L�[
		{
			buff[options->key_deside[4]] = 0;
			buff[KEY_INPUT_A] = 1;
		}
		else if (buff[options->key_deside[5]]) //D�L�[
		{
			buff[options->key_deside[5]] = 0;
			buff[KEY_INPUT_D] = 1;
		}
		else if (buff[options->key_deside[6]]) //Z�L�[
		{
			buff[options->key_deside[6]] = 0;
			buff[KEY_INPUT_Z] = 1;
		}
		else if (buff[options->key_deside[7]]) //X�L�[
		{
			buff[options->key_deside[7]] = 0;
			buff[KEY_INPUT_X] = 1;
		}
	}*/


	while (i < 256) //���������Ԃ𒲂ׂ�
	{
		if (buff[i])
		{
			buff_time[i]++;
		}
		else
		{
			buff_time[i] = 0;
		}
		i++;

	}


	/*if (Flags::talkflag) //��b���͌���L�[�̂�
	{
		if (buff[KEY_INPUT_Z])
		{
			talkingflag++;
		}
		for (int i = 0; i < 256; i++)
		{
			buff[i] = 0;
		}
		if (talkingflag)
		{
			buff[KEY_INPUT_Z] = 1;
			talkingflag = 0;
		}
	}*/
}