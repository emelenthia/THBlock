#pragma once
#include"Flag.h"

class Block
{
public:
	Block();
	~Block();

	int m_color;
	int m_pointx = 0, m_pointy = 0; //左上の支点
	int m_hp; //ブロックの残りHP。ボールに当たる毎に1減り、0になると壊れる。普通のブロックの初期HPは1

	void Draw();
	void SetColor(); //hpを取得した際に1回だけ呼び出す
	void SetPos(int x, int y);
	int GetSizeY();
	int GetSizeX();

private:
	const int m_size_x = 30;
	const int m_size_y = 20;

};

