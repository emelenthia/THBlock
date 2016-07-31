#include "Bar.h"
#include"Flag.h"
#include"DxLib.h"

Bar::Bar()
{
	m_posx = 200;
	m_posy = 380;
	m_gamemain = GameMain::GetInstance();
	m_key = Key_Input::GetInstance();
}


Bar::~Bar()
{
}


void Bar::Draw()
{
	DrawBox(m_posx, m_posy, m_posx + m_sizex, m_posy + m_sizey, Flag::color.purple, TRUE);
}


void Bar::Reaction(int stage_posx, int stage_sizex)
{
	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		KeyCheck(stage_posx, stage_sizex);
	}
	break;
	case GameMain::STATE_PLAY:
	{
		KeyCheck(stage_posx, stage_sizex);
	}
	break;
	case GameMain::STATE_BOMB:
	{
		//��炢�{���I�Ȑݒ�Ńo�[�𓮂������Ƃɐ����B�ȑO�̓{�����Ƀo�[�𓮂����āA�{�[���Ɠ����������ɂǂ�����Ηǂ����Y��ł�
		KeyCheck(stage_posx, stage_sizex);
	}
	break;
	}
}


void Bar::KeyCheck(int stage_posx,int stage_sizex) //�L�[��������Ă���ꍇ�̏���
{
	if (m_key->GetKeyOn(KEY_INPUT_RIGHT))
	{
		m_posx += m_speedx;
		if (m_posx + m_sizex > stage_posx + stage_sizex) //�X�e�[�W����͂ݏo�Ȃ��悤��
		{
			m_posx = stage_posx + stage_sizex - m_sizex;
		}
	}
	if (m_key->GetKeyOn(KEY_INPUT_LEFT))
	{
		m_posx -= m_speedx;
		if (m_posx < stage_posx)
		{
			m_posx = stage_posx;
		}
	}
}