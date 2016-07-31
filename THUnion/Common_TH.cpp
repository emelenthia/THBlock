#include "Common_TH.h"
#include"DxLib.h"
#pragma warning(disable : 4996)

Common_TH::Common_TH()
{
	Font_h = CreateFontToHandle(NULL, 32, -1, DX_FONTTYPE_ANTIALIASING);
	if (Font_h == -1) //失敗したら
	{
		FILE* fp = fopen("../err_log.txt", "w");
		if (fp != NULL)
		{
			fprintf(fp, "フォントハンドルの作成に失敗しました。\n");
			fclose(fp);
		}
		exit(1);
	}
}


Common_TH::~Common_TH()
{
}

void DrawString_Title(int x, int y, char * String, unsigned int Color, int mode)
{
	switch (mode)
	{
	case 1:
		DrawStringToHandle(x, y, String, Color, Font_h); //大きく書く
		break;
	default:
		DrawString(x, y, String, Color);
		break;
	}
}


string Split(string str, char splitter, int number) //splitterで区切ったうちのnumber個目(最小は1)の文字列を返す
{
	int start = 0, end = 0, count = 0;

	for (int i = 0; i < number; i++, count++)
	{
		if (i == number - 1)
		{
			start = count;
		}
		count = str.find(splitter, count);
		if (count == -1) //無かったならそれはもう探す必要が無いということ
		{
			break;
		}
		if (i == number - 1)
		{
			end = count;
		}
	}

	if (!end)
	{
		end = str.size();
	}

	return str.substr(start, end - start);
}


int PlaySound_Back(int sound_h)
{
	return PlaySoundMem(sound_h, DX_PLAYTYPE_BACK);
}
