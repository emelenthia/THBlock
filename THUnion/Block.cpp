#include "Block.h"
#include"DXLib.h"


Block::Block()
{
}


Block::~Block()
{
}


void Block::Draw()
{
	if (m_hp > 0)
	{
		DrawBox(m_pointx, m_pointy, m_pointx + m_size_x, m_pointy + m_size_y, m_color, TRUE);
	}
}


void Block::SetPos(int x, int y)
{
	m_pointx = x;
	m_pointy = y;
}


int Block::GetSizeY()
{
	return m_size_y; //Ç»ÇÒÇ©íºê⁄éQè∆Ç≈Ç´Ç»Ç©Ç¡ÇΩÇ©ÇÁÇ±ÇÍÇ≈
}


int Block::GetSizeX()
{
	return m_size_x;
}


void Block::SetColor()
{
	switch (m_hp)
	{
	case 1:
	{
		m_color = GetColor(0, 0, 0);
	}
	break;
	case 2:
	{
		m_color = GetColor(255, 0, 0); //FlagÇÃcolorÇÕÇ‹Çæë„ì¸Ç≥ÇÍÇƒÇ¢Ç»Ç¢
	}
	break;
	case 3:
	{
		m_color = GetColor(255, 102, 0);
	}
	break;
	case 4:
	{
		m_color = GetColor(255, 255, 0);
	}
	break;
	case 5:
	{
		m_color = GetColor(0, 255, 0);
	}
	break;
	case 6:
	{
		m_color = GetColor(0, 0, 255);
	}
	break;
	case 7:
	{
		m_color = GetColor(22, 94, 131);
	}
	break;
	case 8:
	{
		m_color = GetColor(255, 0, 255);
	}
	break;
	default:
	{
		m_color = GetColor(255, 255, 255);
	}
	break;
	}
}