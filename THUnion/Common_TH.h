#pragma once
#include<string>
using namespace std;

class Common_TH //何度も使う関数をまとめておく；変更しやすくするためとか
{
public:
	Common_TH();
	~Common_TH();


};

static int Font_h;
void DrawString_Title(int x, int y, char* String, unsigned int Color, int mode = 0); //タイトル画面で使用する文字列描画関数
string Split(string str, char splitter, int number);
int PlaySound_Back(int sound_h);


