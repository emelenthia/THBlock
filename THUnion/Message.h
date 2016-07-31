#pragma once



class Message //ゲーム内メッセージ(命令)の一覧クラス
{
public:
	typedef enum MESSAGES_
	{
		MES_NONE = 0,
		MES_END = 1,
		MES_GAME_START,
		MES_GAME_CLEAR,
		MES_GAME_OVER,
		MES_GO_TITLE,
		MES_FALL = 11,
		MES_WALL_BOUND,
		MES_RANKING
	} MESSAGE;

	static MESSAGE MESLIST;
	Message();
	~Message();
};

