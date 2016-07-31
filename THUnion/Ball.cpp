#include"Ball.h"
#include"DxLib.h"
#include"Common_TH.h"

Ball::Ball()
{

	m_speed_x = m_default_speed_x; m_speed_y = -m_default_speed_y;
	m_r = 6;
	m_sound_bar = LoadSoundMem("../data/sound/cursor1.wav");
	m_sound_wall = LoadSoundMem("../data/sound/decision22.wav");
	m_sound_fall = LoadSoundMem("../data/sound/decision6.wav");
	m_gamemain = GameMain::GetInstance();
	m_color = Flag::color.purple_low;
}


void Ball::Draw()
{

	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		DrawCircle (m_pos_x, m_pos_y, m_r, m_color, TRUE); //�������������g��`�悵�Ă���
	}
	break;
	case GameMain::STATE_PLAY:
	{
		DrawCircle(m_pos_x, m_pos_y, m_r, m_color, TRUE);
	}
	break;
	case GameMain::STATE_BOMB:
	{
		DrawCircle(m_pos_x, m_pos_y, m_r, m_color, TRUE);
		//�{���̉��o�͂����ŗǂ��̂��ȁc?
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 212); //����
		DrawCircle(m_pos_x, m_pos_y, m_r + m_gamemain->GetGameTime() / 2, m_color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
	}
	break;
	}

}


Message::MESSAGE Ball::Reaction(Bar* bar, Stage* stage) //�ʒu�̈ړ��Ƃ�������֐�
{
	bool breakflag = false;
	Message::MESSAGE ret = Message::MES_NONE;
	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		m_pos_x = bar->m_posx + bar->GetSizeX() / 2;
		m_pos_y = bar->m_posy - m_r;
	}
	break;
	case GameMain::STATE_PLAY:
	{
		//�{�[���������ňړ������Ă�����R�ꂪ�����悤�ɂ��邽��
		for (int i = 0; i < (int)((m_gamemain->GetDiff() == GameMain::DIF_EXTRA) ? GameMain::DIF_NORMAL : m_gamemain->GetDiff()); i++) //��Փx���オ��قǑ����Ȃ�Ƃ����킯
		{
			m_pos_x += m_speed_x;
			m_pos_y += m_speed_y; //��x��1�����₵�ĂȂ��̂̓��[�v���Ƒ��v���̌��ˍ���
								  //�����Ƀ`�F�b�N����
								  //�u���b�N�Ɠ������Ă��Ȃ���

			if (stage->HitCheck() != GameMain::DIRECT_NONE)
			{
				//�̗͎Q�Ƃ̓s����A�����̃q�b�g����stage.HitCheck()�ɏ���
				breakflag = true; //�������Ă��炻���œ����̂���߂�
			}
			//�o�[�Ɠ������Ă��Ȃ���
			if (stage->HitCheckBarToBall() != GameMain::DIRECT_NONE)
			{
				PlaySoundMem(m_sound_bar, DX_PLAYTYPE_BACK);
				breakflag = true;

			}
			//�ǂƓ������Ă��Ȃ���
			ret = stage->HitCheckWall();
			if (ret == Message::MES_WALL_BOUND)
			{
				PlaySoundMem(m_sound_wall, DX_PLAYTYPE_BACK);
				breakflag = true;
			}
			//�ǂꂩ�ɓ������Ă����烋�[�v���甲����
			if (breakflag)
			{
				break;
			}
		}
	}
	break;
	case GameMain::STATE_FALL:
	{
		if (m_gamemain->GetGameTime() == 2) //���Ԃ͓K���B�����ɏ����ׂ����ASTATE.START�ɏ����ׂ����c�K�����̎��Ԃ��K�ꂻ���Ȃ����ɂ������ǁA�ǂ������ǂ���
		{
			//�ˏo�����̏�����
			m_speed_x = m_default_speed_x; m_speed_y = -m_default_speed_y;
			PlaySound_Back(m_sound_fall);
			//�ʒu�̏�����
			m_pos_x = bar->m_posx + bar->GetSizeX() / 2;
			m_pos_y = bar->m_posy - m_r;
		}

	}
	break;
	case GameMain::STATE_BOMB:
	{
		if (m_pos_y + m_r > bar->m_posy && m_gamemain->GetGameTime() == 0) //�o�[��艺�ɂ���Ȃ�A�o�[�̏�����Ɉړ�����
		{
			m_pos_y = bar->m_posy - m_r - 4;
		}
	}
	break;
	}
	return ret;
}


void Ball::Refrection(GameMain::direction number)
{
	switch (number)
	{
	case GameMain::DIRECT_TOP:
		m_speed_y = -m_default_speed_y;
		break;
	case GameMain::DIRECT_RIGHT:
		m_speed_x = m_default_speed_x;
		break;
	case GameMain::DIRECT_BUTTOM:
		m_speed_y = m_default_speed_y;
		break;
	case GameMain::DIRECT_LEFT:
		m_speed_x = -m_default_speed_x;
		break;
	}
}


void Ball::RefrectionBar(GameMain::direction number, Bar* bar) //�_�Ɠ��������ꍇ�̔��ˏ����B������posx�͍���̍��W
{
	switch (number)
	{
	case GameMain::DIRECT_TOP:
		if (m_pos_x < bar->m_posx + bar->GetSizeX() / 4) //�_�̍����̍��ɓ��������ꍇ
		{
			m_speed_x = -m_default_speed_x;
		}
		else if (m_pos_x >= bar->m_posx + bar->GetSizeX() / 4 && m_pos_x < bar->m_posx + bar->GetSizeX() / 2) //�_�̍����̉E�ɓ��������ꍇ
		{
			m_speed_x = -m_default_speed_x / 2;
		}
		else if (m_pos_x > bar->m_posx + bar->GetSizeX() / 2 && m_pos_x < bar->m_posx + 3 * bar->GetSizeX() / 4) //�_�̉E���̍��ɓ��������ꍇ
		{
			m_speed_x = m_default_speed_x / 2;
		}
		else if (m_pos_x >= bar->m_posx + 3 * bar->GetSizeX() / 4) //�_�̉E���̉E�ɓ��������ꍇ
		{
			m_speed_x = m_default_speed_x;
		}
		else //�_�̐^�񒆂ɓ��������ꍇ
		{
			m_speed_x = 0;
		}
		m_speed_y = -m_default_speed_y; //y���̑��x�͂ǂ�ł��ς��Ȃ�


										//�f���Ă߂荞�܂Ȃ��悤�ɂ���ł�?
		m_pos_y = bar->m_posy - m_r;
		break;
	case GameMain::DIRECT_RIGHT:
		m_speed_x = m_default_speed_x;
		m_speed_y = -m_default_speed_y;

		m_pos_x = bar->m_posx + bar->GetSizeX() + m_r;
		break;
	case GameMain::DIRECT_BUTTOM:
		if (m_pos_x < bar->m_posx) //�_�̍����ɓ��������ꍇ
		{
			m_speed_x = -m_default_speed_x;
		}
		else if (m_pos_x > bar->m_posx) //�_�̉E���ɓ��������ꍇ
		{
			m_speed_x = m_default_speed_x;
		}
		else //�_�̐^�񒆂ɓ��������ꍇ
		{
			m_speed_x = 0;
		}
		m_speed_y = m_default_speed_y;

		m_pos_y = bar->m_posy + bar->GetSizeY() + m_r;
		break;
	case GameMain::DIRECT_LEFT:
		m_speed_x = -m_default_speed_x;
		m_speed_y = -m_default_speed_y;

		m_pos_x = bar->m_posx - m_r;
		break;
	}
}

GameMain::direction Ball::HitCheckSquare(int posx, int posy, int sizex, int sizey) //�^����ꂽ�l�p�`�ƃ{�[�����ڐG���Ă��邩�ǂ����𒲂ׂ�BBar��Block�̓����蔻������ʉ����邽�߂ɂ����ɏ����B
{
	GameMain::direction hitnumber = GameMain::DIRECT_NONE;
	int ball_size_sqrt2 = (int)(m_r / sqrt(2)); //���x���v�Z�������Ȃ��̂�
	int temp_posx = 0, temp_posy = 0;

	//�H�^���̓_�̃`�F�b�N
	if (
		((((temp_posx = m_pos_x) == INT32_MAX) || ((temp_posy = m_pos_y + m_r) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_TOP;
	}
	//�H�^�E�̓_�̃`�F�b�N
	else if (
		((((temp_posx = m_pos_x + m_r) == INT32_MAX) || ((temp_posy = m_pos_y) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_LEFT;
	}
	//�H�^���̓_�̃`�F�b�N
	else if (
		((((temp_posx = m_pos_x - m_r) == INT32_MAX) || ((temp_posy = m_pos_y) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_RIGHT;
	}
	//�H�^��̓_�̃`�F�b�N
	else if (
		((((temp_posx = m_pos_x) == INT32_MAX) || ((temp_posy = m_pos_y - m_r) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		hitnumber = GameMain::DIRECT_BUTTOM; //������ɂ������A�u���b�N���猩�ĉ����Ƃ�������
	}
	//�����`����̓_�̃`�F�b�N�B�������̈ʒu���͌덷���o�₷��
	else if (
		((((temp_posx = m_pos_x - ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y - ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy < posy + sizey) //�{�[���̒��S���u���b�N��艺�Ȃ�
		{
			hitnumber = GameMain::DIRECT_BUTTOM; //�����瓖�������ƌ��Ȃ��B���傤�ǉE���̕ӂ肾�Ƒz��ƈႤ���˕Ԃ������ꍇ�����邪�A�ǂ�����Ηǂ���������Ȃ�
		}
		else //����ȊO��
		{
			hitnumber = GameMain::DIRECT_RIGHT; //�E���瓖�������ƌ��Ȃ�
		}
	}
	//�����`�E��̓_�̃`�F�b�N�B
	else if (
		((((temp_posx = m_pos_x + ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y - ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy < posy + sizey) //�{�[���̒��S���u���b�N��艺�Ȃ�
		{

			hitnumber = GameMain::DIRECT_BUTTOM;
		}
		else
		{
			hitnumber = GameMain::DIRECT_LEFT;
		}
	}
	//�����`�E���̓_�̃`�F�b�N�B
	else if (
		((((temp_posx = m_pos_x + ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y + ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy > posy) //�{�[���̒��S���u���b�N����Ȃ�
		{
			hitnumber = GameMain::DIRECT_TOP;
		}
		else
		{
			hitnumber = GameMain::DIRECT_LEFT;
		}
	}
	//�����`�����̓_�̃`�F�b�N�B
	else if (
		((((temp_posx = m_pos_x - ball_size_sqrt2) == INT32_MAX) || ((temp_posy = m_pos_y + ball_size_sqrt2) == INT32_MAX)) || true) &&
		HitCheckPointinSquare(temp_posx, temp_posy, posx, posy, sizex, sizey)
		)
	{
		if (temp_posy > posy) //�{�[���̒��S���u���b�N����Ȃ�
		{
			hitnumber = GameMain::DIRECT_TOP;
		}
		else
		{
			hitnumber = GameMain::DIRECT_RIGHT;
		}
	}

	return hitnumber;
}


bool Ball::HitCheckPointinSquare(int ball_posx, int ball_posy, int posx, int posy, int sizex, int sizey)
{
	if (
		(posx < ball_posx && ball_posx < posx + sizex) && //����̓_������̎l�p�`�̓����ɂ��邩�ǂ���
		(posy < ball_posy && ball_posy < posy + sizey)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}