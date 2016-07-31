#pragma once
class Ball;
#include"Bar.h"
#include"GameMain.h"
#include"Message.h"
#include"Stage.h"

class Ball //�ʂ̃N���X
{
public:
	int m_color; //colors.purple_low��
	int m_pos_x = 99, m_pos_y = 400; //���S�̓_
	int m_r; //�~�̔��a
	const int m_default_speed_x = 2; //�{�[���̑����̐�Βl�I��
	const int m_default_speed_y = 3; //1:3���Y��ȋC������c���ǁA���ˈʒu�Ƃ��l����2�Ɂc
	int m_speed_x = 0, m_speed_y = 0;
	int m_sound_bar;
	int m_sound_wall;
	int m_sound_fall;
	GameMain* m_gamemain;


	void Draw();

	Message::MESSAGE Reaction(Bar* bar, Stage* stage); //�ʒu�̈ړ��Ƃ�������֐�

	int GetSize_r() { return m_r; }

	void Refrection(GameMain::direction number);

	void RefrectionBar(GameMain::direction number, Bar* bar); //�_�Ɠ��������ꍇ�̔��ˏ����B������posx�͍���̍��W

	GameMain::direction HitCheckSquare(int posx, int posy, int sizex, int sizey); //�^����ꂽ�l�p�`�ƃ{�[�����ڐG���Ă��邩�ǂ����𒲂ׂ�BBar��Block�̓����蔻������ʉ����邽�߂ɂ����ɏ����B

	Ball();
	~Ball() {}

private:
	bool HitCheckPointinSquare(int ball_posx, int ball_posy, int posx, int posy, int sizex, int sizey);

};
