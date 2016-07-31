#pragma once
class Stage;
#include"Block.h"
#include<string>
#include"Message.h"
#include"Ball.h"
#include"GameMain.h"
#include "SceneBase.h"
#include"Key_Input.h"

using namespace std;

class Stage :
	public SceneBase
{
public:


	static Stage* instance;
	//// �B��̃A�N�Z�X�o�H
	static Stage* GetInstance()
	{
		if (instance == NULL)instance = new Stage();
		return instance;
	}

	int m_block_num = 0; //�u���b�N�̌�
	Block** m_blocks;
	const int m_posx = 10, m_posy = 10;
	const int m_sizex = 360, m_sizey = 420;
	string* m_bgm_fileName;
	int m_sound_bgm;
	int m_sound_ball_block_nonbreak;
	int m_sound_ball_block_break;
	int img;
	int m_bg_stage;
	int m_bg_around;// = Image.FromFile("./pic/BG00a0_80.jpg");
	bool m_clearflag;
	GameMain* m_gamemain;

	void Draw();
	void DrawHSN();
	void DrawBG(); //����͔w�i�ł�


	void SetInfo(); //���̏�����

	Message::MESSAGE Reaction(); //�v�Z�Ƃ������Ƃ�����������֐�

	void PlayBgm();

	//Ball��Stage����GameMain�������Ă�ق������R�ȋC���������ǁABlock��Bar�Ɣ��肷�邩�瓯���̂������Ă������݌v�I�ɂ͎��R���������c
	GameMain::direction HitCheck(); //�{�[���ƐڐG���Ă���u���b�N�����邩�ǂ������肷��

	void HitCheckBomb(); //��̂Ƌ��ʂ��Ă邩�牽�Ƃ����������{���Ǘ���GameMain�N���X�����c

	bool HitCheckPointToBlock(int posx, int posy, Block* block);

	bool HitCheckBlockToBomb(Block* block); //�{���N���X��������ق����悳�C�c?

	GameMain::direction HitCheckBarToBall();


	Message::MESSAGE HitCheckWall(); //�{�[�����ǂƐڂ��ĂȂ����ǂ���
private:

	Stage();
	~Stage();
	Stage(const Stage& rhs);
	Stage& operator=(const Stage& rhs);
	Ball* m_ball;
	Bar* m_bar; //Bar��Ball��Stage�������ĂĂ����ŕ`�悷�邱�ƂɕύX
	Key_Input* m_key;
	bool m_first_flag;
	void DrawInfo();
	int m_sound_bomb;
	int m_sound_gameover;
	int m_sound_clear;
	void Reset(); //���̃N���A
	void ReadFile(); //�t�@�C������ݒ�Ƃ���ǂݍ���
};

