#pragma once

typedef struct Colors_ { //�����N���X�̊O�ɏo���Ă����Ȃ��Ƃ����Ȃ��炵��
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

class Flag //�O���[�o���ɎQ�Ƃ��������̂�����N���X
{
public:
	Flag();
	~Flag(){}

	static int nowscene; //���݂̃V�[����\���B0x4141e�Ȃ�title
	static Colors color; //����J���[�𒲂ׂ�̂��ʓ|�����������̂œZ�߂Ă���

};
