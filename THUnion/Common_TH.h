#pragma once
#include<string>
using namespace std;

class Common_TH //���x���g���֐����܂Ƃ߂Ă����G�ύX���₷�����邽�߂Ƃ�
{
public:
	Common_TH();
	~Common_TH();


};

static int Font_h;
void DrawString_Title(int x, int y, char* String, unsigned int Color, int mode = 0); //�^�C�g����ʂŎg�p���镶����`��֐�
string Split(string str, char splitter, int number);
int PlaySound_Back(int sound_h);


