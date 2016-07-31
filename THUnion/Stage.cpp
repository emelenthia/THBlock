#include "Stage.h"
#include"DxLib.h"
#include"Common_TH.h"
#pragma warning(disable:4996)

Stage* Stage::instance;

Stage::Stage()
{
	//こういうのは先頭に書くべき
	m_gamemain = GameMain::GetInstance();
	m_key = Key_Input::GetInstance();


	m_sound_ball_block_nonbreak = LoadSoundMem("../data/sound/cursor6.wav");
	m_sound_ball_block_break = LoadSoundMem("../data/sound/decision19.wav");
	m_clearflag = false;
	m_first_flag = true;
	m_bg_stage = LoadGraph("../data/pic/BG00b0_80.jpg");
	m_bg_around = LoadGraph("../data/pic/BG00a0_80.jpg");
	m_sound_bomb = LoadSoundMem("../data/sound/flash2.wav");
	m_sound_gameover = LoadSoundMem("../data/sound/ゲームオーバーのジングル.wav");
	m_sound_clear = LoadSoundMem("../data/sound/栄光のファンファーレ.wav");
}


Stage::~Stage()
{
}


void Stage::Draw()
{
	DrawBG();
	DrawInfo();
	if (m_gamemain->GetDiff() == GameMain::DIF_EXTRA)
	{
		DrawHSN();
	}
	for (int i = 0; i < m_block_num; i++)
	{
		m_blocks[i]->Draw();
	}

	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		if (m_first_flag) //一番最初だけ
		{
			if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA)
			{
				char tempstr[16];
				sprintf(tempstr, "%s%d", "Stage", m_gamemain->m_stage_number);
				DrawString(160, 310, tempstr, Flag::color.red);
			}
			else
			{
				DrawString(162, 310, "Extra", Flag::color.red);
			}
			DrawString(150, 340, "Press Z", Flag::color.red);
		}
	}
	break;
	case GameMain::STATE_GAMEOVER:
	{
		if (m_gamemain->GetGameTime() == 60)
		{
			PlaySound_Back(m_sound_gameover);
		}
		if (m_gamemain->GetGameTime())
		{
			DrawString(120, 220, "Game Over", Flag::color.red);
			DrawString(105, 270, "PRESS 'R' TO TRY AGAIN", Flag::color.red);
		}
	}
	break;
	}

	m_ball->Draw();
	m_bar->Draw();
}


void Stage::DrawBG()
{
	DrawExtendGraph(0, 0, 640, 480, m_bg_around, FALSE);
	DrawExtendGraph(m_posx, m_posy, m_posx+ m_sizex, m_posy+m_sizey, m_bg_stage, FALSE);
}


void Stage::DrawHSN()
{
	//画像ファイルを読み込んで、Imageオブジェクトとして取得する
	if (img == NULL)
	{
		img = LoadGraph("../data/pic/hsn2.jpg");
	}
	DrawGraph(100, 56, img, FALSE);
}


void Stage::DrawInfo() //プレイヤー情報やスコア等の表示
{
	string tempstr;

	tempstr = "Player : ";
	for (int i = 0; i < m_gamemain->m_players; i++)
	{
		tempstr += "★";
	}
	DrawString(420, 100, tempstr.data(), Flag::color.red);

	tempstr = "Bomb   : ";
	for (int i = 0; i < m_gamemain->m_bombs; i++)
	{
		tempstr += "●";
	}
	DrawString(420, 125, tempstr.data(), Flag::color.red);

	char tempcstr[16];
	sprintf(tempcstr, "%d", m_gamemain->m_gametime);
	tempstr = "Time   : ";
	tempstr += tempcstr;
	DrawString(420, 150, tempstr.data(), Flag::color.red);

	DrawString(400, 225, "  玉発射   : Zキー", Flag::color.red);
	DrawString(400, 250, "   移動    : 方向キー", Flag::color.red);
	DrawString(400, 275, "   ボム    : Xキー", Flag::color.red);
	DrawString(400, 300, "ゲーム終了 : Escキー", Flag::color.red);
}


void Stage::SetInfo()
{
	ReadFile();
	m_sound_bgm = LoadSoundMem(m_bgm_fileName->data());
	m_bar = new Bar();
	m_ball = new Ball();
}


void Stage::Reset()
{
	delete m_bar;
	delete m_ball;
}


void Stage::ReadFile() //ファイルから設定とかを読み込む
{
	//ファイルを開くところから
	string* stage_file;
	if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA)
	{
		stage_file = new string("../data/stage/stage1.cns");
	}
	else
	{
		stage_file = new string("../data/stage/extra1.cns");
	}
	FILE* fp;
	fp = fopen(stage_file->data(), "r");

	string* str;
	char temp_block_str[64];

	//ブロックの個数を取得
	fscanf(fp, "%d", &m_block_num); \

	//その個数だけブロックを生成。ここに書きたくないけど…うーん
	m_blocks = new Block*[m_block_num]; //オブジェクトを生成する際に要素数を変数で直接指定できるのは便利
	for (int i = 0; i < m_block_num; i++) //だけどこれをしないといけないのは間違えそう
	{
		m_blocks[i] = new Block();
	}

	//ブロックの座標とかを取得。形式は"x,y,hp"
	for (int i = 0; i < m_block_num; i++)
	{
		fscanf(fp, "%s", temp_block_str);
		str = new string(temp_block_str);
		string temp_str = Split(*str, ',', 1);

		if (temp_str[0] != '*')
		{
			int posx = atoi(temp_str.data());
			temp_str = Split(*str, ',', 2);
			int posy = atoi(temp_str.data());
			m_blocks[i]->SetPos(posx, posy);

			m_blocks[i]->m_hp = atoi(Split(*str, ',', 3).data());
			m_blocks[i]->SetColor();
		}
		else //特殊な指定だった場合。決して座標指定が面倒な訳です。何とか出来ないかなあ
		{
			//後で修正
			/*
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_posx = int.Parse(temp_str[0]);
			int temp_posy = int.Parse(temp_str[1]);
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_numx = int.Parse(temp_str[0]);
			int temp_numy = int.Parse(temp_str[1]);
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_clearancex = int.Parse(temp_str[0]);
			int temp_clearancey = int.Parse(temp_str[1]);
			int temp_hp = int.Parse(temp_str[2]);
			int temp_sizex = m_blocks[i].GetSizeX();
			int temp_sizey = m_blocks[i].GetSizeY();
			for (int block_number = 0; block_number < m_block_num; block_number++)
			{
				m_blocks[block_number].SetPos(temp_posx + (temp_sizex + temp_clearancex) * ((block_number % temp_numx)), temp_posy + (temp_sizey + temp_clearancey) * (block_number / temp_numx));
				m_blocks[block_number].m_hp = temp_hp;
				m_blocks[block_number].SetColor();
			}
			break;*/
		}
		delete str;
	}

	//これstring型使ってる意味ある?
	char sound_str[128];
	fscanf(fp, "%s", sound_str);
	m_bgm_fileName = new string(sound_str); //bgmのファイル名を取得
	fclose(fp);
}


Message::MESSAGE Stage::Reaction() //計算とか反応とかを処理する関数
{
	Message::MESSAGE ret = Message::MES_NONE;
	m_bar->Reaction(m_posx, m_sizex);
	ret = m_ball->Reaction(m_bar, this);
	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		PlayBgm();
		if (m_key->GetKeyTime(KEY_INPUT_Z) % 30 == 1)
		{
			m_gamemain->SetState(GameMain::STATE_PLAY);
			m_first_flag = false;
		}
	}
	break;
	case GameMain::STATE_PLAY:
	{
		PlayBgm();
		if (m_clearflag)
		{
			ret = Message::MES_GAME_CLEAR;
		}
		if (ret == Message::MES_FALL)
		{
			if (m_gamemain->m_players > 0)
			{
				m_gamemain->SetState(GameMain::STATE_FALL);
				m_gamemain->m_players--;
				m_gamemain->m_bombs = m_gamemain->MAX_BOMB;
			}
			else
			{
				m_gamemain->SetState(GameMain::STATE_GAMEOVER);
			}
		}
		if (m_key->GetKeyOn(KEY_INPUT_X))
		{
			if (m_gamemain->m_bombs > 0)
			{
				m_gamemain->SetState(GameMain::STATE_BOMB);
				m_gamemain->m_bombs--;
			}
		}
	}
	break;
	case GameMain::STATE_BOMB:
	{
		PlayBgm();
		if (m_gamemain->GetGameTime() == 120 - 2) //TODO:具体的な時間は後で
		{
			HitCheckBomb();
		}
		if (m_clearflag)
		{
			ret = Message::MES_GAME_CLEAR;
		}
		if (m_gamemain->GetGameTime() == 20)
		{
			PlaySound_Back(m_sound_bomb);
		}
		if (m_gamemain->GetGameTime() >= 120)
		{
			m_gamemain->SetState(GameMain::STATE_PLAY);
		}
	}
	break;
	case GameMain::STATE_FALL:
	{
		PlayBgm();
		if (m_gamemain->GetGameTime() >= 60)
		{
			m_gamemain->SetState(GameMain::STATE_START);
		}
	}
	break;
	case GameMain::STATE_GAMEOVER:
	{
		if (m_gamemain->GetGameTime() == 60)
		{
			StopSoundMem(m_sound_bgm);
		}
		if (m_key->GetKeyOn(KEY_INPUT_R))
		{
			m_gamemain->SetState(GameMain::STATE_TITLE);
			
			Reset();
			StopSoundMem(m_sound_gameover);
			ret = Message::MES_GO_TITLE;
		}
	}
	break;
	case GameMain::STATE_GAMECLEAR:
	{
		if (m_gamemain->GetGameTime() == 29)
		{
			StopSoundMem(m_sound_bgm);
		}
	}
	break;
	}

	return ret;
}


void Stage::PlayBgm()
{
	if (CheckSoundMem(m_sound_bgm))
	{

	}
	else //bgmが止まっている場合再生
	{
		PlaySoundMem(m_sound_bgm, DX_PLAYTYPE_LOOP);
	}
}


GameMain::direction Stage::HitCheck() //ボールと接触しているブロックがあるかどうか判定する
{
	int count = 0;
	GameMain::direction hitnumber = GameMain::DIRECT_NONE; //1…下から当たった、2…右から当たった、3…上から当たった、4…左から当たった
	for (int i = 0; i < m_block_num; i++)
	{
		if (m_blocks[i]->m_hp > 0) //崩れていないブロックだけ判定する
		{
			count++;
			hitnumber = m_ball->HitCheckSquare(m_blocks[i]->m_pointx, m_blocks[i]->m_pointy, m_blocks[i]->GetSizeX(), m_blocks[i]->GetSizeY()); //チェック用の関数

			if (hitnumber != GameMain::DIRECT_NONE) //当たってなくなければ当たり
			{
				//ここに当たった時の処理(音とか跳ね返りとか)を書く
				//ブロックの老朽化
				m_blocks[i]->m_hp--;
				if (m_blocks[i]->m_hp > 0) //壊れる時とそうでない時で効果音が違う
				{
					PlaySoundMem(m_sound_ball_block_nonbreak, DX_PLAYTYPE_BACK);
				}
				else
				{
					PlaySoundMem(m_sound_ball_block_break, DX_PLAYTYPE_BACK);
				}

				//反射処理
				m_ball->Refrection(hitnumber);
				return hitnumber; //当たったらすぐ帰る
			}
		}
	}
	if (count == 0)
	{
		m_clearflag = true;
	}

	return hitnumber;
}


void Stage::HitCheckBomb() //上のと共通してるから何とかしたいしボム管理はGameMainクラスだし…
{
	int keep_mr = m_ball->m_r; //半径を覚えておき
	m_ball->m_r = 60; //ボムの大きさに変える。TODO:ここも具体的には後で
	for (int i = 0; i < m_block_num; i++)
	{
		if (m_blocks[i]->m_hp > 0) //崩れていないブロックだけ判定する
		{
			//HitCheckSquare()を使い回す予定だったが、ボムが大きいので、完全に入ってしまったブロックとかは取得できなかったので別関数を作る…
			if (HitCheckBlockToBomb(m_blocks[i]))
			{
				//ここに当たった時の処理(何かある?)を書く
				//TODO:ボムダメージはボムを複数種類を作った際に変える
				if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA) //extraはボム無効
				{
					m_blocks[i]->m_hp -= 3;
				}
			}
		}
	}
	m_ball->m_r = keep_mr; //半径は元に戻す
}


bool Stage::HitCheckPointToBlock(int posx, int posy, Block* block)
{
	if (
		(block->m_pointx < posx && posx < block->m_pointx + block->GetSizeX()) && //ボールの特定の点が四角形の内部にあるかどうか
		(block->m_pointy < posy && posy < block->m_pointy + block->GetSizeY())
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Stage::HitCheckBlockToBomb(Block* block) //ボムクラスを作ったほうがよさ気…?
{
	
	bool ret = false;
	if (pow(m_ball->m_pos_x - block->m_pointx, 2) + pow(m_ball->m_pos_y - block->m_pointy, 2) < pow(m_ball->m_r, 2))//左上の点
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - (block->m_pointx + block->GetSizeX()), 2) + pow(m_ball->m_pos_y - block->m_pointy, 2) < pow(m_ball->m_r, 2)) //右上の点
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - (block->m_pointx + block->GetSizeX()), 2) + pow(m_ball->m_pos_y - (block->m_pointy + block->GetSizeY()), 2) < pow(m_ball->m_r, 2)) //右下の点
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - block->m_pointx, 2) + pow(m_ball->m_pos_y - (block->m_pointy + block->GetSizeY()), 2) < pow(m_ball->m_r, 2)) //左下の点
	{
		ret = true;
	}
	return ret;
}


GameMain::direction Stage::HitCheckBarToBall()
{
	GameMain::direction hitnumber = m_ball->HitCheckSquare(m_bar->m_posx, m_bar->m_posy, m_bar->GetSizeX(), m_bar->GetSizeY()); //チェック用の関数

	if (hitnumber != GameMain::DIRECT_NONE) //当たってなくなければ当たり
	{
		//反射処理
		m_ball->RefrectionBar(hitnumber, m_bar);
	}
	return hitnumber;
}


Message::MESSAGE Stage::HitCheckWall() //ボールが壁と接してないかどうか
{
	int ball_size = m_ball->GetSize_r(); //毎回関数呼び出すのもやだし記憶しておく
	Message::MESSAGE ret = Message::MES_NONE;
	if (m_ball->m_pos_y - ball_size <= m_posy) //上側の壁とぶつかっているか
	{
		m_ball->Refrection(GameMain::DIRECT_BUTTOM); //上側の壁とぶつかった=ブロックの下にぶつかった
		ret = Message::MES_WALL_BOUND; //SEを鳴らすために…びみょい
	}
	else if (m_ball->m_pos_y + ball_size >= m_posy + m_sizey) //下
	{
		//下の壁と接触したら死ぬ
		ret = Message::MES_FALL;
	}
	else if (m_ball->m_pos_x - ball_size <= m_posx) //左
	{
		m_ball->Refrection(GameMain::DIRECT_RIGHT);
		ret = Message::MES_WALL_BOUND;
	}
	else if (m_ball->m_pos_x + ball_size >= m_posx + m_sizex) //右
	{
		m_ball->Refrection(GameMain::DIRECT_LEFT);
		ret = Message::MES_WALL_BOUND;
	}

	return ret;
}