#pragma once
#include"DxLib.h"
#include"Message.h"

class GameMain //�Q�[���}�X�^�[�݂����Ȃ��̂ŁA�F��ȏ����Ǘ�����
{
public :
	static GameMain* instance;
	//// �B��̃A�N�Z�X�o�H
	static GameMain* GetInstance()
	{
		if (instance == NULL)instance = new GameMain();
		return instance;
	}

	enum DIFFCULT { DIF_EASY = 1, 
		DIF_NORMAL, 
		DIF_HARD, 
		DIF_LUNATIC, 
		DIF_EXTRA };

	
	void SetDiff(DIFFCULT diff) { m_difficulty = diff; }
	DIFFCULT GetDiff() { return m_difficulty; }
	enum STATE
	{
		STATE_TITLE = 1,
		STATE_START = 10, //�{�[�����o�[�ɂ������Ă�����
		STATE_PLAY = 11, //�{�[���������Ă�����
		STATE_FALL = 12, //�{�[�������������
		STATE_BOMB = 13, //�{���������Ă����ԁB���̏�Ԃ͕K��STATE.PLAY�Əd�Ȃ�
		STATE_GAMEOVER = 20,
		STATE_STAGECLEAR = 21, //�X�e�[�W�N���A�[��ԁB���̂܂�
		STATE_GAMECLEAR = 22, //�Q�[���N���A��ԁB�X�e�[�W�N���A�Ƃ͕�
		STATE_RANKING = 23 //�����L���O�\�����
	};
	STATE GetState() { return m_state; }
	void SetState(STATE state); //����ŊO����state��M��c����܂�悭��������������
	int GetGameTime() { return m_time; } //m_gametime�Ɣ��ɂ킩��ɂ����Ȃ��Ă��܂����cGetStateTime()�ɂ��悤�������悤
	enum direction { DIRECT_NONE = 0, DIRECT_BUTTOM = 1, 
		DIRECT_RIGHT, DIRECT_TOP, DIRECT_LEFT };
	void Reaction(Message::MESSAGE mes); //state�̍X�V�Ƃ����s��
	int m_players; //�c��c�@
	const int MAX_PLAYER = 2; //�v���C���[�̏����c�@�B0�ɂȂ��Ă��Q�[���I�[�o�[����Ȃ����Ƃɗ���
	int m_bombs; //�c��{��
	const int MAX_BOMB = 3; //�v���C���[�̏����c�@
	int m_stage_number; //���݂̖ʐ�
	int m_gametime;
	
private:
	DIFFCULT m_difficulty;
	// ������R�s�[���֎~����
	GameMain();
	GameMain(const GameMain& rhs);
	GameMain& operator=(const GameMain& rhs);
	~GameMain() {}
	STATE m_state; //���݂̏�ԁBs_state����m_state��
	int m_time; //����s_time

	/*
	PictureBox m_pictureBox; //���g��`�悷�邽�߂̗̈�
	Stage m_stage;
	Bar m_bar;
	Ball m_ball;
	Font m_font;
	Font m_font_go;
	Title m_title;
	Key_Manage m_key;
	Text_Input m_textinput; //���O���͗p�̃_�C�A���O
	int m_fps;
	int m_oldtime;
	int m_draw_fps;
	int m_gametime; //�X�R�A�I�ȃ^�C���B�����قǗǂ�
	public static String s_name; //�ʃ_�C�A���O����̃f�[�^�̎󂯓n�������񂽂�
	struct RANKING //����A����std::Pair�Ƃ����̂�����炵����?
	{
		public int score;
		public String name;
	}
	const int RANKING_MAX = 10; //10�ʂ܂ŕ\�����悤
	RANKING[] m_ranking = new RANKING[RANKING_MAX];
	int m_ranknum;
	Image m_bg_rank;
	Image m_bg_play;
	bool m_title_z_flag; //��Փx�I�����炢���Ȃ�n�܂�Ȃ��悤�ɁBfalse�Ȃ痣����Ă���B�����Ɨǂ��Ȃ�񂩂Ȃ�
	*/

};