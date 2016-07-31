#include"Title.h"
#include"DxLib.h"
#include"Flag.h"


Title::Title()
{
	m_state = TSTATE_TITLE; //最初は必ずタイトル
	m_font_title = CreateFontToHandle("ＭＳ ゴシック", 48, -1, -1);
	m_font_select = CreateFontToHandle("ＭＳ ゴシック", 18, -1, -1);
	m_font_context = CreateFontToHandle("ＭＳ ゴシック", 24, -1, -1);
	m_choose = 0;
	m_choose_diff = GameMain::DIF_EASY;
	m_sound_bgm = LoadSoundMem("../data/sound/Same_Street.wav");
	m_bg_title = LoadGraph("../data/pic/BG00e_80.jpg");
	m_bg_diff = LoadGraph("../data/pic/BG00f_80.jpg");

	m_key = Key_Input::GetInstance();
	m_gamemain = GameMain::GetInstance();
}

void Title::Draw()
{
	switch (m_state)
	{
	case TSTATE_TITLE:
	{
		DrawGraph(0, 0, m_bg_title, FALSE);

		DrawStringToHandle(200, 100,"B-CRASH", Flag::color.aqua, m_font_title);
		DrawStringToHandle(400 - (m_choose == CT_GAME_START ? 20 : 0), 300, "GAME START", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose == CT_EXTRA_START ? 20 : 0), 325, "EXTRA START", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose == CT_RANKING ? 20 : 0), 350, "RANKING", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose == CT_EXIT ? 20 : 0), 375, "EXIT", Flag::color.black, m_font_select);
	}
	break;
	case TSTATE_DIFFICUT:
	{
		DrawGraph(0, 0, m_bg_diff, FALSE);

		DrawStringToHandle(100, 100, "難易度を選択して下さい", Flag::color.red, m_font_title);
		DrawStringToHandle(400 - (m_choose_diff == GameMain::DIF_EASY ? 20 : 0), 300, "EASY", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose_diff == GameMain::DIF_NORMAL ? 20 : 0), 325, "NORMAL", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose_diff == GameMain::DIF_HARD ? 20 : 0), 350, "HARD", Flag::color.black, m_font_select);
		DrawStringToHandle(400 - (m_choose_diff == GameMain::DIF_LUNATIC ? 20 : 0), 375, "LUNATIC", Flag::color.black, m_font_select);
	}
	break;
	case TSTATE_BOMB:
	{

	}
	break;
	}
}

Message::MESSAGE Title::Reaction()
{
	Message::MESSAGE ret = Message::MES_NONE;
	PlayBgm();
	switch (m_state)
	{
	case TSTATE_TITLE:
	{
		if (m_key->GetKeyOn(KEY_INPUT_Z))
		{
			switch (m_choose)
			{
			case CT_GAME_START:
			{
				m_state = TSTATE_DIFFICUT;
				m_time = 0;
			}
			break;
			case CT_EXTRA_START:
			{
				ret = Message::MES_GAME_START;
				m_gamemain->SetDiff(GameMain::DIF_EXTRA);
				StopSoundMem(m_sound_bgm);
			}
			break;
			/*case (int)CHOOSE_TITLE.PRACTICE_START:
			{
			//TODO:作らなきゃ！
			}
			break;*/
			case CT_RANKING:
			{
				ret = Message::MES_RANKING;
			}
			break;
			case CT_EXIT:
			{
				ret = Message::MES_END;
			}
			break;
			}

		}
		if (m_key->GetKeyTime(KEY_INPUT_UP) % 20 == 1) //TODO:この辺の数値はキチンと決める
		{
			m_choose = m_choose != 0 ? --m_choose : CT_EXIT;
		}

		if (m_key->GetKeyTime(KEY_INPUT_DOWN) % 20 == 1) //TODO:この辺の数値はキチンと決める
		{
			m_choose = m_choose != CT_EXIT ? ++m_choose : 0;
		}
	}
	break;
	case TSTATE_DIFFICUT:
	{
		m_time++;
		if (m_time > 15)
		{
			if (m_key->GetKeyOn(KEY_INPUT_Z))
			{
				ret = Message::MES_GAME_START;
				m_gamemain->SetDiff((GameMain::DIFFCULT)m_choose_diff);
				StopSoundMem(m_sound_bgm);
				m_state = TSTATE_TITLE;

			}
		}
		if (m_key->GetKeyOn(KEY_INPUT_X))
		{
			m_state = TSTATE_TITLE;
		}
		if (m_key->GetKeyTime(KEY_INPUT_UP) % 20 == 1) //TODO:この辺の数値はキチンと決める
		{
			m_choose_diff = m_choose_diff != GameMain::DIF_EASY ? --m_choose_diff : GameMain::DIF_LUNATIC;
		}

		if (m_key->GetKeyTime(KEY_INPUT_DOWN) % 20 == 1) //TODO:この辺の数値はキチンと決める
		{
			m_choose_diff = m_choose_diff != GameMain::DIF_LUNATIC ? ++m_choose_diff : GameMain::DIF_EASY;
		}
	}
	break;
	}
	return ret;
}

void Title::PlayBgm()
{
	if (CheckSoundMem(m_sound_bgm)) //再生中なら1
	{

	}
	else //bgmが止まっている場合再生
	{
		PlaySoundMem(m_sound_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
}



Title::~Title()
{

}
