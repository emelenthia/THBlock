#pragma once
#include"DxLib.h"
#include"Message.h"

class GameMain //ゲームマスターみたいなもので、色んな情報を管理する
{
public :
	static GameMain* instance;
	//// 唯一のアクセス経路
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
		STATE_START = 10, //ボールがバーにくっついている状態
		STATE_PLAY = 11, //ボールが動いている状態
		STATE_FALL = 12, //ボールが落ちた状態
		STATE_BOMB = 13, //ボムを撃っている状態。この状態は必ずSTATE.PLAYと重なる
		STATE_GAMEOVER = 20,
		STATE_STAGECLEAR = 21, //ステージクリアー状態。このまま
		STATE_GAMECLEAR = 22, //ゲームクリア状態。ステージクリアとは別
		STATE_RANKING = 23 //ランキング表示状態
	};
	STATE GetState() { return m_state; }
	void SetState(STATE state); //これで外からstateを弄る…あんまりよく無さそうだけど
	int GetGameTime() { return m_time; } //m_gametimeと非常にわかりにくくなってしまった…GetStateTime()にしようそうしよう
	enum direction { DIRECT_NONE = 0, DIRECT_BUTTOM = 1, 
		DIRECT_RIGHT, DIRECT_TOP, DIRECT_LEFT };
	void Reaction(Message::MESSAGE mes); //stateの更新とかを行う
	int m_players; //残り残機
	const int MAX_PLAYER = 2; //プレイヤーの初期残機。0になってもゲームオーバーじゃないことに留意
	int m_bombs; //残りボム
	const int MAX_BOMB = 3; //プレイヤーの初期残機
	int m_stage_number; //現在の面数
	int m_gametime;
	
private:
	DIFFCULT m_difficulty;
	// 生成やコピーを禁止する
	GameMain();
	GameMain(const GameMain& rhs);
	GameMain& operator=(const GameMain& rhs);
	~GameMain() {}
	STATE m_state; //現在の状態。s_stateからm_stateへ
	int m_time; //元はs_time

	/*
	PictureBox m_pictureBox; //自身を描画するための領域
	Stage m_stage;
	Bar m_bar;
	Ball m_ball;
	Font m_font;
	Font m_font_go;
	Title m_title;
	Key_Manage m_key;
	Text_Input m_textinput; //名前入力用のダイアログ
	int m_fps;
	int m_oldtime;
	int m_draw_fps;
	int m_gametime; //スコア的なタイム。早いほど良い
	public static String s_name; //別ダイアログからのデータの受け渡しがうんたら
	struct RANKING //これ、何かstd::Pairというのがあるらしいよ?
	{
		public int score;
		public String name;
	}
	const int RANKING_MAX = 10; //10位まで表示しよう
	RANKING[] m_ranking = new RANKING[RANKING_MAX];
	int m_ranknum;
	Image m_bg_rank;
	Image m_bg_play;
	bool m_title_z_flag; //難易度選択からいきなり始まらないように。falseなら離されている。もっと良くならんかなあ
	*/

};