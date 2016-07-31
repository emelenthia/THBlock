#pragma once
#include"SceneBase.h"
#include"Common_TH.h"
#include"GameMain.h"
#include"Message.h"
#include"Key_Input.h"

class Title :
	public SceneBase
{

public:
	Title();
	~Title();
	void Draw();
	Message::MESSAGE Reaction();
	void PlayBgm();
	int m_font_title;
	int m_font_select;
	int m_font_context;
	int m_bg_title;
	int m_bg_diff;
	int m_sound_bgm;


	enum TITLE_STATE { TSTATE_TITLE = 1, TSTATE_DIFFICUT, TSTATE_BOMB };
	TITLE_STATE m_state;
	int m_time; //キーを連続で処理されないように
	enum CHOOSE_TITLE { 
		CT_GAME_START = 0,
		CT_EXTRA_START, 
		CT_RANKING, 
		CT_EXIT }; //EXIT=TITLE_MAX-1

private:
	int m_title_pic;
	int m_choose; //現在選んでいる内容
	int m_choose_diff;
	const int m_menu_x = 440; //メニュー一覧の左上の支点x
	const int m_menu_y = 320; //メニュー一覧の左上の支点y

	Key_Input* m_key;
	GameMain* m_gamemain;
};