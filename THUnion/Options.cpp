#pragma warning(disable : 4996)
#include "Options.h"
#include"DxLib.h"
#include<stdio.h>
Options* Options::instance;

Options::Options()
{
	m_key = Key_Input::GetInstance();
	move_speed = 4;
	revolve_speed = 4;
	choosenow = 0;
	optionflag = 0;
	black = GetColor(0, 0, 0);
	yellow = GetColor(255, 255, 0);
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);
	keyconfigflag = 0;
	choosenow_keyconfig = 0;
	keyconfingflag = 0;
	fp = fopen("./scn/save/options.cns", "r");
	key_fp = fopen("./scn/save/keyconfig.txt", "r+");
	key_name_fp = fopen("./scn/save/keyconfig_list.cns", "r");
	if (fp == NULL || key_fp == NULL || key_name_fp == NULL)
	{
		DrawString(0, 0, "Error. I can not open file.", yellow);
		WaitKey();
	}

	//オプションのリストを読み込む
	fscanf(fp, "%d", &option_max);
	for (int i = 0; i < option_max; i++)
	{
		fscanf(fp, "%s", option_list[i]);
		fscanf(fp, "%s", option_explanation[i]);
	}

	//現在のキー情報を読み込む
	fscanf(key_fp, "%d", &key_max);
	for (int i = 0; i < key_max; i++)
	{
		fscanf(key_fp, "%d", &key_deside[i]);
	}

	//キーコンフィグのリストを読み込む
	fscanf(key_name_fp, "%d", &key_name_max);
	for (int i = 0; i < key_name_max; i++)
	{
		fscanf(key_name_fp, "%s", &key_name_list[i]);
	}

}


void Options::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120); //透過
	DrawBox(0, 0, 640, 480, black, TRUE); //明るい背景を暗くする
	if (!keyconfigflag)
	{
		DrawBox(0, 25, 100, 55, yellow, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す
		DrawExtendString(20, 30, 1.5, 1.5, "Option", black);
		DrawBox(0, choosenow * 25 + 65, 640, (choosenow + 1) * 25 + 65, yellow, TRUE);
		for (int i = 0; i < option_max; i++)
		{
			DrawFormatString(200 - GetDrawFormatStringWidth("%s", option_list[i]), i * 25 + 70, (choosenow == i ? black : white), "%s", option_list[i]);
		}
		DrawString(400, (option_max - 2) * 25 + 70, "設定", (choosenow == option_max - 2 ? black : white));
	}
	else
	{
		DrawBox(0, 25, 200, 55, yellow, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す
		DrawExtendString(20, 30, 1.5, 1.5, "KeyConfig", black);
		DrawString(222, 35, "キーボード", white);
		DrawString(422, 35, "ゲームパッド", white);


		DrawBox(0, choosenow_keyconfig * 20 + 58, 640, (choosenow_keyconfig + 1) * 20 + 58, (keyconfingflag?black:yellow), TRUE);
		for (int i = 0; i < key_name_max - 1; i++)
		{
			DrawFormatString(160, i * 20 + 60, (choosenow_keyconfig == i ? black : white),"%s",key_name_list[i]);
			DrawKey(260, i * 20 + 60, key_deside_temp[i]);
		}
		DrawString(60, (key_name_max - 1) * 20 + 60, "設定を反映して戻る", (choosenow_keyconfig == 8 ? black : white));
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
	DrawBox(0, 0, 640, 20, blue, TRUE); //説明欄
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	DrawFormatString(22, 2, white, "%s", option_explanation[choosenow], TRUE); //説明しよう
}


int Options::Reaction()
{
	/*
	if (!keyconfigflag)
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			choosenow = (choosenow > 0 ? choosenow - 1 : option_max - 1); //ループできるように
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			choosenow = (choosenow < option_max - 1 ? choosenow + 1 : 0);
		}

		if (Key_Input::buff_time[KEY_INPUT_X] == 1 || (choosenow == option_max - 1 && Key_Input::buff_time[KEY_INPUT_Z] == 1)) optionflag = 0;
		if (choosenow == option_max - 2 && Key_Input::buff_time[KEY_INPUT_Z] == 1)
		{
			keyconfigflag++;
			
			//現在のキー情報をコピー
			for (int i = 0; i < key_max; i++)
			{
				key_deside_temp[i] = key_deside[i];
			}
			int n = 0;
		}
	}
	else if (!keyconfingflag)
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			choosenow_keyconfig = (choosenow_keyconfig > 0 ? choosenow_keyconfig - 1 : key_max); //ループできるように
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			choosenow_keyconfig = (choosenow_keyconfig < key_max ? choosenow_keyconfig + 1 : 0);
		}

		//設定を反映して戻る
		if (choosenow_keyconfig == key_max && Key_Input::buff_time[KEY_INPUT_Z] == 1)
		{
			keyconfigflag = 0;

			//キー情報の更新
			//書き込む前に閉じて再度開く必要がある
			fclose(key_fp);
			key_fp = fopen("./scn/save/keyconfig.txt", "r+");
			fprintf(key_fp, "%d\n", key_max);
			for (int i = 0; i < key_max; i++)
			{
				fprintf(key_fp, "%d\n", key_deside_temp[i]);
				key_deside[i] = key_deside_temp[i];
			}
			//更新する
			fclose(key_fp);
			key_fp = fopen("./scn/save/keyconfig.txt", "r+");
		}


		if (choosenow_keyconfig < key_max && Key_Input::buff_time[KEY_INPUT_Z] == 1) keyconfingflag++;

	}
	else
	{
		int keep = key_deside_temp[choosenow_keyconfig];
		key_deside_temp[choosenow_keyconfig] = GetKeyKwsk();
		for (int i = 0; i < key_max; i++)
		{
			if (key_deside_temp[choosenow_keyconfig] == key_deside_temp[i] && i != choosenow_keyconfig)
			{
				//既に登録されているキーなら破棄する
			}
		}
	}*/
	return 0;
}


void Options::DrawKey(int pos_x,int pos_y,int key)
{
	char temp_key[20];
	switch (key)
	{
	case 14:
		strcpy(temp_key, "バックスペース");
		break;
	case 16:
		strcpy(temp_key, "Q");
		break;
	case 17:
		strcpy(temp_key, "W");
		break;
	case 18:
		strcpy(temp_key, "E");
		break;
	case 19:
		strcpy(temp_key, "R");
		break;
	case 20:
		strcpy(temp_key, "T");
		break;
	case 21:
		strcpy(temp_key, "Y");
		break;
	case 22:
		strcpy(temp_key, "U");
		break;
	case 23:
		strcpy(temp_key, "I");
		break;
	case 24:
		strcpy(temp_key, "O");
		break;
	case 25:
		strcpy(temp_key, "P");
		break;
	case 30:
		strcpy(temp_key , "A");
		break;
	case 31:
		strcpy(temp_key , "S");
		break;
	case 32:
		strcpy(temp_key , "D");
		break;
	case 33:
		strcpy(temp_key, "F");
		break;
	case 34:
		strcpy(temp_key, "G");
		break;
	case 35:
		strcpy(temp_key, "H");
		break;
	case 36:
		strcpy(temp_key, "J");
		break;
	case 37:
		strcpy(temp_key, "K");
		break;
	case 38:
		strcpy(temp_key, "L");
		break;
	case 44:
		strcpy(temp_key, "Z");
		break;
	case 45:
		strcpy(temp_key, "X");
		break;
	case 46:
		strcpy(temp_key, "C");
		break;
	case 47:
		strcpy(temp_key, "V");
		break;
	case 48:
		strcpy(temp_key, "B");
		break;
	case 49:
		strcpy(temp_key, "N");
		break;
	case 50:
		strcpy(temp_key, "M");
		break;
	case 54:
		strcpy(temp_key, "右シフト");
		break;
	case 42:
		strcpy(temp_key, "左シフト");
		break;
	case 57:
		strcpy(temp_key, "スペース");
		break;
	case 28:
		strcpy(temp_key, "エンター");
		break;
	case 200:
		strcpy(temp_key, "↑");
		break;
	case 205:
		strcpy(temp_key, "→");
		break;
	case 208:
		strcpy(temp_key, "↓");
		break;
	case 203:
		strcpy(temp_key, "←");
		break;
	default:
		strcpy(temp_key, " ");
		break;
	}

	//真ん中揃えで描写
	DrawFormatString(pos_x - 0.5 * GetDrawFormatStringWidth("%s",temp_key), pos_y, blue, "%s", temp_key);
}


int Options::GetKeyKwsk()
{
	int temp_key = 0;
	while (temp_key < 256)
	{
		if (m_key->GetKeyTime(temp_key) == 1) break;
		temp_key++;
	}

	//既に登録されているキーなら破棄する
	for (int i = 0; i < key_max; i++)
	{
		if (key_deside_temp[i] == temp_key && i != choosenow_keyconfig)
		{
			temp_key = 256;
		}
	}

	if (temp_key < 256) keyconfingflag = 0;
	else temp_key = -1;

	return temp_key;
}