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
		//喰らいボム的な設定でバーを動かすことに成功。以前はボム中にバーを動かして、ボールと当たった時にどうすれば良いか悩んでた
		KeyCheck(stage_posx, stage_sizex);
	}
	break;
	}
}


void Bar::KeyCheck(int stage_posx,int stage_sizex) //キーが押されている場合の処理
{
	if (m_key->GetKeyOn(KEY_INPUT_RIGHT))
	{
		m_posx += m_speedx;
		if (m_posx + m_sizex > stage_posx + stage_sizex) //ステージからはみ出ないように
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