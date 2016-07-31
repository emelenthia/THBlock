#pragma once
#include<stdio.h>
#include"Key_Input.h"

class Options //�I�v�V�������ڂ̃N���X
{
public:
	static Options* instance;
	//// �B��̃A�N�Z�X�o�H
	static Options* GetInstance()
	{
		if (instance == NULL)instance = new Options();
		return instance;
	}

	int move_speed;
	int revolve_speed; //�Eor�������������̑���
	void Draw();
	int Reaction();
	bool optionflag; //�I�v�V������ʕ`��t���O
	int choosenow;
	int black;
	int white;
	int yellow;
	int blue;
	FILE *fp;
	char option_list[10][80];
	char option_explanation[10][120];
	int option_max;
	int bgm_bolume;
	int se_bolume;
	int battle_effect_flag;
	int keyconfigflag;
	int choosenow_keyconfig;
	int keyconfingflag;
	void DrawKey(int pos_x, int pos_y, int key); //�^����ꂽ�����ɑ΂���DX���C�u�����Ŋ��蓖�Ă�ꂽ�L�[�̖��O��`��
	unsigned char key_deside[15];
	unsigned char key_deside_temp[15];
	int pad_deside[15];
	int pad_deside_temp[15];
	FILE *key_name_fp;
	char key_name_list[10][15];
	int key_name_max;
	FILE *key_fp;
	int key_max;
	int GetKeyKwsk(); //�����ꂽ�L�[��1�����擾
	Key_Input* m_key;

private:

	// ������R�s�[���֎~����
	Options();
	Options(const Options& rhs);
	Options& operator=(const Options& rhs);
	~Options() {}

};

