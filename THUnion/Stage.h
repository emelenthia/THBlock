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
	//// 唯一のアクセス経路
	static Stage* GetInstance()
	{
		if (instance == NULL)instance = new Stage();
		return instance;
	}

	int m_block_num = 0; //ブロックの個数
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
	void DrawBG(); //これは背景です


	void SetInfo(); //情報の初期化

	Message::MESSAGE Reaction(); //計算とか反応とかを処理する関数

	void PlayBgm();

	//BallはStageよりはGameMainが持ってるほうが自然な気もしたけど、BlockやBarと判定するから同じのが持ってた方が設計的には自然そうだが…
	GameMain::direction HitCheck(); //ボールと接触しているブロックがあるかどうか判定する

	void HitCheckBomb(); //上のと共通してるから何とかしたいしボム管理はGameMainクラスだし…

	bool HitCheckPointToBlock(int posx, int posy, Block* block);

	bool HitCheckBlockToBomb(Block* block); //ボムクラスを作ったほうがよさ気…?

	GameMain::direction HitCheckBarToBall();


	Message::MESSAGE HitCheckWall(); //ボールが壁と接してないかどうか
private:

	Stage();
	~Stage();
	Stage(const Stage& rhs);
	Stage& operator=(const Stage& rhs);
	Ball* m_ball;
	Bar* m_bar; //BarもBallもStageが持っててここで描画することに変更
	Key_Input* m_key;
	bool m_first_flag;
	void DrawInfo();
	int m_sound_bomb;
	int m_sound_gameover;
	int m_sound_clear;
	void Reset(); //情報のクリア
	void ReadFile(); //ファイルから設定とかを読み込む
};

