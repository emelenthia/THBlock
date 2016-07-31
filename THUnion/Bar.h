#pragma once
#include"GameMain.h"
#include"Key_Input.h"

class Bar
{
public:
	int m_posx = 0, m_posy = 0;
	const int m_speedx = 5;

	Bar();
	~Bar();

	void Draw();

	void Reaction(int stage_posx, int stage_sizex);

	void KeyCheck(int stage_posx, int stage_sizex); //ƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚éê‡‚Ìˆ—

	int GetSizeX() { return m_sizex; }
	int GetSizeY() { return m_sizey; }

private:
	GameMain* m_gamemain;
	Key_Input* m_key;
	const int m_sizex = 69, m_sizey = 20;
};