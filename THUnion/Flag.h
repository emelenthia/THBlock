#pragma once

typedef struct Colors_ { //何かクラスの外に出しておかないといけないらしい
	int red;
	int blue;
	int yellow;
	int white;
	int black;
	int aqua;
	int dark_aqua;
	int green;
	int purple;
	int indigo;
	int orange;
	int purple_low;
} Colors;

class Flag //グローバルに参照したいものを入れるクラス
{
public:
	Flag();
	~Flag(){}

	static int nowscene; //現在のシーンを表す。0x4141eならtitle
	static Colors color; //毎回カラーを調べるのが面倒そうだったので纏めておく

};
