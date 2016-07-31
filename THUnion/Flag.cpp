#include"Flag.h"
#include"DxLib.h"

int Flag::nowscene;
Colors Flag::color;

Flag::Flag()
{
	color.red = GetColor(255, 0, 0);
	color.blue = GetColor(0, 0, 255);
	color.black = GetColor(0, 0, 0);
	color.white = GetColor(255, 255, 255);
	color.yellow = GetColor(255, 255, 0);
	color.aqua = GetColor(0, 255, 255);
	color.dark_aqua = GetColor(0, 35, 35);
	color.green = GetColor(0, 255, 0);
	color.purple = GetColor(255, 0, 255);
	color.indigo = GetColor(22, 94, 131);
	color.orange = GetColor(255, 102, 0);
	color.purple_low = GetColor(128, 0, 128);
}