#pragma once
#include"Flag.h"

class Block
{
public:
	Block();
	~Block();

	int m_color;
	int m_pointx = 0, m_pointy = 0; //����̎x�_
	int m_hp; //�u���b�N�̎c��HP�B�{�[���ɓ����閈��1����A0�ɂȂ�Ɖ���B���ʂ̃u���b�N�̏���HP��1

	void Draw();
	void SetColor(); //hp���擾�����ۂ�1�񂾂��Ăяo��
	void SetPos(int x, int y);
	int GetSizeY();
	int GetSizeX();

private:
	const int m_size_x = 30;
	const int m_size_y = 20;

};

