#pragma once
class Ball;
#include"Bar.h"
#include"GameMain.h"
#include"Message.h"
#include"Stage.h"

class Ball //玉のクラス
{
public:
	int m_color; //colors.purple_lowに
	int m_pos_x = 99, m_pos_y = 400; //中心の点
	int m_r; //円の半径
	const int m_default_speed_x = 2; //ボールの速さの絶対値的な
	const int m_default_speed_y = 3; //1:3が綺麗な気がする…けど、反射位置とか考えて2に…
	int m_speed_x = 0, m_speed_y = 0;
	int m_sound_bar;
	int m_sound_wall;
	int m_sound_fall;
	GameMain* m_gamemain;


	void Draw();

	Message::MESSAGE Reaction(Bar* bar, Stage* stage); //位置の移動とかをする関数

	int GetSize_r() { return m_r; }

	void Refrection(GameMain::direction number);

	void RefrectionBar(GameMain::direction number, Bar* bar); //棒と当たった場合の反射処理。ここのposxは左上の座標

	GameMain::direction HitCheckSquare(int posx, int posy, int sizex, int sizey); //与えられた四角形とボールが接触しているかどうかを調べる。BarとBlockの当たり判定を共通化するためにここに書く。

	Ball();
	~Ball() {}

private:
	bool HitCheckPointinSquare(int ball_posx, int ball_posy, int posx, int posy, int sizex, int sizey);

};
