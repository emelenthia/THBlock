#include"Ball.h"
#include"DxLib.h"
#include"Common_TH.h"

Ball::Ball()
{

	m_speed_x = m_default_speed_x; m_speed_y = -m_default_speed_y;
	m_r = 6;
	m_sound_bar = LoadSoundMem("../data/sound/cursor1.wav");
	m_sound_wall = LoadSoundMem("../data/sound/decision22.wav");
	m_sound_fall = LoadSoundMem("../data/sound/decision6.wav");
	m_gamemain = GameMain::GetInstance();
	m_color = Flag::color.purple_low;
}


void Ball::Draw()
{

	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		DrawCircle (m_pos_x, m_pos_y, m_r, m_color, TRUE); //こここそが自身を描画している
	}
	break;
	case GameMain::STATE_PLAY:
	{
		DrawCircle(m_pos_x, m_pos_y, m_r, m_color, TRUE);
	}
	break;
	case GameMain::STATE_BOMB:
	{
		DrawCircle(m_pos_x, m_pos_y, m_r, m_color, TRUE);
		//ボムの演出はここで良いのかな…?
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 212); //透過
		DrawCircle(m_pos_x, m_pos_y, m_r + m_gamemain->GetGameTime() / 2, m_color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す
	}
	break;
	}

}


Message::MESSAGE Ball::Reaction(Bar* bar, Stage* stage) //位置の移動とかをする関数
{
	bool breakflag = false;
	Message::MESSAGE ret = Message::MES_NONE;
	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		m_pos_x = bar->m_posx + bar->GetSizeX() / 2;
		m_pos_y = bar->m_posy - m_r;
	}
	break;
	case GameMain::STATE_PLAY:
	{
		//ボールを高速で移動させても判定漏れが無いようにするため
		for (int i = 0; i < (int)((m_gamemain->GetDiff() == GameMain::DIF_EXTRA) ? GameMain::DIF_NORMAL : m_gamemain->GetDiff()); i++) //難易度が上がるほど早くなるというわけ
		{
			m_pos_x += m_speed_x;
			m_pos_y += m_speed_y; //一度に1ずつ増やしてないのはループ数と大丈夫感の兼ね合い
								  //ここにチェック処理
								  //ブロックと当たっていないか

			if (stage->HitCheck() != GameMain::DIRECT_NONE)
			{
				//体力参照の都合上、ここのヒット音はstage.HitCheck()に書く
				breakflag = true; //当たってたらそこで動くのをやめる
			}
			//バーと当たっていないか
			if (stage->HitCheckBarToBall() != GameMain::DIRECT_NONE)
			{
				PlaySoundMem(m_sound_bar, DX_PLAYTYPE_BACK);
				breakflag = true;

			}
			//壁と当たっていないか
			ret = stage->HitCheckWall();
			if (ret == Message::MES_WALL_BOUND)
			{
				PlaySoundMem(m_sound_wall, DX_PLAYTYPE_BACK);
				breakflag = true;
			}
			//どれかに当たっていたらループから抜ける
			if (breakflag)
			{
				break;
			}
		}
	}
	break;
	case GameMain::STATE_FALL:
	{
		if (m_gamemain->GetGameTime() == 2) //時間は適当。ここに書くべきか、STATE.STARTに書くべきか…必ずこの時間が訪れそうなここにしたけど、どっちが良いか
		{
			//射出方向の初期化
			m_speed_x = m_default_speed_x; m_speed_y = -m_default_speed_y;
			PlaySound_Back(m_sound_fall);
			//位置の初期化
			m_pos_x = bar->m_posx + bar->GetSizeX() / 2;
			m_pos_y = bar->m_posy - m_r;
		}

	}
	break;
	case GameMain::STATE_BOMB:
	{
		if (m_pos_y + m_r > bar->m_posy && m_gamemain->GetGameTime() == 0) //バーより下にあるなら、バーの少し上に移動する
		{
			m_pos_y = bar->m_posy - m_r - 4;
		}
	}
	break;
	}
	return ret;
}


void Ball::Refrection(GameMain::direction number)
{
	switch (number)
	{
	case GameMain::DIRECT_TOP:
		m_speed_y = -m_default_speed_y;
		break;
	case GameMain::DIRECT_RIGHT:
		m_speed_x = m_default_speed_x;
		break;
	case GameMain::DIRECT_BUTTOM:
		m_speed_y = m_default_speed_y;
		break;
	case GameMain::DIRECT_LEFT:
		m_speed_x = -m_default_speed_x;
		break;
	}
}


void Ball::RefrectionBar(GameMain::direction number, Bar* bar) //棒と当たった場合の反射処理。ここのposxは左上の座標
{
	switch (number)
	{
	case GameMain::DIRECT_TOP:
		if (m_pos_x < bar->m_posx + bar->GetSizeX() / 4) //棒の左側の左に当たった場合
		{
			m_speed_x = -m_default_speed_x;
		}
		else if (m_pos_x >= bar->m_posx + bar->GetSizeX() / 4 && m_pos_x < bar->m_posx + bar->GetSizeX() / 2) //棒の左側の右に当たった場合
		{
			m_speed_x = -m_default_speed_x / 2;
		}
		else if (m_pos_x > bar->m_posx + bar->GetSizeX() / 2 && m_pos_x < bar->m_posx + 3 * bar->GetSizeX() / 4) //棒の右側の左に当たった場合
		{
			m_speed_x = m_default_speed_x / 2;
		}
		else if (m_pos_x >= bar->m_posx + 3 * bar->GetSizeX() / 4) //棒の右側の右に当たった場合
		{
			m_speed_x = m_default_speed_x;
		}
		else //棒の真ん中に当たった場合
		{
			m_speed_x = 0;
		}
		m_speed_y = -m_default_speed_y; //y軸の速度はどれでも変わらない


										//断じてめり込まないようにするです?
		m_pos_y = bar->m_posy - m_r;
		break;
	case GameMain::DIRECT_RIGHT:
		m_speed_x = m_default_speed_x;
		m_speed_y = -m_default_speed_y;

		m_pos_x = bar->m_posx + bar->GetSizeX() + m_r;
		break;
	case GameMain::DIRECT_BUTTOM:
		if (m_pos_x < bar->m_posx) //棒の左側に当たった場合
		{
			m_speed_x = -m_default_speed_x;
		}
		else if (m_pos_x > bar->m_posx) //棒の右側に当たった場合
		{
			m_speed_x = m_default_speed_x;
		}
		else //棒の真ん中に当たった場合
		{
			m_speed_x = 0;
		}
		m_speed_y = m_default_speed_y;

		m_pos_y = bar->m_posy + bar->GetSizeY() + m_r;
		break;
	case GameMain::DIRECT_LEFT:
		m_speed_x = -m_default_speed_x;
		m_speed_y = -m_default_speed_y;

		m_pos_x = bar->m_posx - m_r;
		break;
	}
}

GameMain::direction Ball::HitCheckSquare(int posx, int posy, int sizex, int sizey) //与えられた四角形とボールが接触しているかどうかを調べる。BarとBlockの当たり判定を共通化するためにここに書く。
{
	GameMain::direction hitnumber = GameMain::DIRECT_NONE;
	int ball_size_sqrt2 = (int)(m_r / sqrt(2)); //何度も計算したくないので
	int temp_posx = 0, temp_posy = 0;

	//菱型下の点のチェック
	if (
		((((temp_posx = m_pos_x) == INT32_MAX) || ((temp_posy = m_pos_y + m_r) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_TOP;
	}
	//菱型右の点のチェック
	else if (
		((((temp_posx = m_pos_x + m_r) == INT32_MAX) || ((temp_posy = m_pos_y) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_LEFT;
	}
	//菱型左の点のチェック
	else if (
		((((temp_posx = m_pos_x - m_r) == INT32_MAX) || ((temp_posy = m_pos_y) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_RIGHT;
	}
	//菱型上の点のチェック
	else if (
		((((temp_posx = m_pos_x) == INT32_MAX) || ((temp_posy = m_pos_y - m_r) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_BUTTOM; //分かりにくいが、ブロックから見て下だということ
	}
	//正方形左上の点のチェック。こっちの位置情報は誤差が出やすい
	else if (
		((((temp_posx = m_pos_x - ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y - ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy < posy + sizey) //ボールの中心がブロックより下なら
		{
			hitnumber = GameMain::DIRECT_BUTTOM; //下から当たったと見なす。ちょうど右下の辺りだと想定と違う跳ね返りをする場合があるが、どうすれば良いか分からない
		}
		else //それ以外は
		{
			hitnumber = GameMain::DIRECT_RIGHT; //右から当たったと見なす
		}
	}
	//正方形右上の点のチェック。
	else if (
		((((temp_posx = m_pos_x + ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y - ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy < posy + sizey) //ボールの中心がブロックより下なら
		{

			hitnumber = GameMain::DIRECT_BUTTOM;
		}
		else
		{
			hitnumber = GameMain::DIRECT_LEFT;
		}
	}
	//正方形右下の点のチェック。
	else if (
		((((temp_posx = m_pos_x + ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y + ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy > posy) //ボールの中心がブロックより上なら
		{
			hitnumber = GameMain::DIRECT_TOP;
		}
		else
		{
			hitnumber = GameMain::DIRECT_LEFT;
		}
	}
	//正方形左下の点のチェック。
	else if (
		((((temp_posx = m_pos_x - ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y + ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy > posy) //ボールの中心がブロックより上なら
		{
			hitnumber = GameMain::DIRECT_TOP;
		}
		else
		{
			hitnumber = GameMain::DIRECT_RIGHT;
		}
	}

	return hitnumber;
}


bool Ball::HitCheckPointinSquare(int ball_posx, int ball_posy, int posx, int posy, int sizex, int sizey)
{
	if (
		(posx < ball_posx && ball_posx < posx + sizex) && //特定の点が特定の四角形の内部にあるかどうか
		(posy < ball_posy && ball_posy < posy + sizey)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}