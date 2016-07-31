#include "Stage.h"
#include"DxLib.h"
#include"Common_TH.h"
#pragma warning(disable:4996)

Stage* Stage::instance;

Stage::Stage()
{
	//���������̂͐擪�ɏ����ׂ�
	m_gamemain = GameMain::GetInstance();
	m_key = Key_Input::GetInstance();


	m_sound_ball_block_nonbreak = LoadSoundMem("../data/sound/cursor6.wav");
	m_sound_ball_block_break = LoadSoundMem("../data/sound/decision19.wav");
	m_clearflag = false;
	m_first_flag = true;
	m_bg_stage = LoadGraph("../data/pic/BG00b0_80.jpg");
	m_bg_around = LoadGraph("../data/pic/BG00a0_80.jpg");
	m_sound_bomb = LoadSoundMem("../data/sound/flash2.wav");
	m_sound_gameover = LoadSoundMem("../data/sound/�Q�[���I�[�o�[�̃W���O��.wav");
	m_sound_clear = LoadSoundMem("../data/sound/�h���̃t�@���t�@�[��.wav");
}


Stage::~Stage()
{
}


void Stage::Draw()
{
	DrawBG();
	DrawInfo();
	if (m_gamemain->GetDiff() == GameMain::DIF_EXTRA)
	{
		DrawHSN();
	}
	for (int i = 0; i < m_block_num; i++)
	{
		m_blocks[i]->Draw();
	}

	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		if (m_first_flag) //��ԍŏ�����
		{
			if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA)
			{
				char tempstr[16];
				sprintf(tempstr, "%s%d", "Stage", m_gamemain->m_stage_number);
				DrawString(160, 310, tempstr, Flag::color.red);
			}
			else
			{
				DrawString(162, 310, "Extra", Flag::color.red);
			}
			DrawString(150, 340, "Press Z", Flag::color.red);
		}
	}
	break;
	case GameMain::STATE_GAMEOVER:
	{
		if (m_gamemain->GetGameTime() == 60)
		{
			PlaySound_Back(m_sound_gameover);
		}
		if (m_gamemain->GetGameTime())
		{
			DrawString(120, 220, "Game Over", Flag::color.red);
			DrawString(105, 270, "PRESS 'R' TO TRY AGAIN", Flag::color.red);
		}
	}
	break;
	}

	m_ball->Draw();
	m_bar->Draw();
}


void Stage::DrawBG()
{
	DrawExtendGraph(0, 0, 640, 480, m_bg_around, FALSE);
	DrawExtendGraph(m_posx, m_posy, m_posx+ m_sizex, m_posy+m_sizey, m_bg_stage, FALSE);
}


void Stage::DrawHSN()
{
	//�摜�t�@�C����ǂݍ���ŁAImage�I�u�W�F�N�g�Ƃ��Ď擾����
	if (img == NULL)
	{
		img = LoadGraph("../data/pic/hsn2.jpg");
	}
	DrawGraph(100, 56, img, FALSE);
}


void Stage::DrawInfo() //�v���C���[����X�R�A���̕\��
{
	string tempstr;

	tempstr = "Player : ";
	for (int i = 0; i < m_gamemain->m_players; i++)
	{
		tempstr += "��";
	}
	DrawString(420, 100, tempstr.data(), Flag::color.red);

	tempstr = "Bomb   : ";
	for (int i = 0; i < m_gamemain->m_bombs; i++)
	{
		tempstr += "��";
	}
	DrawString(420, 125, tempstr.data(), Flag::color.red);

	char tempcstr[16];
	sprintf(tempcstr, "%d", m_gamemain->m_gametime);
	tempstr = "Time   : ";
	tempstr += tempcstr;
	DrawString(420, 150, tempstr.data(), Flag::color.red);

	DrawString(400, 225, "  �ʔ���   : Z�L�[", Flag::color.red);
	DrawString(400, 250, "   �ړ�    : �����L�[", Flag::color.red);
	DrawString(400, 275, "   �{��    : X�L�[", Flag::color.red);
	DrawString(400, 300, "�Q�[���I�� : Esc�L�[", Flag::color.red);
}


void Stage::SetInfo()
{
	ReadFile();
	m_sound_bgm = LoadSoundMem(m_bgm_fileName->data());
	m_bar = new Bar();
	m_ball = new Ball();
}


void Stage::Reset()
{
	delete m_bar;
	delete m_ball;
}


void Stage::ReadFile() //�t�@�C������ݒ�Ƃ���ǂݍ���
{
	//�t�@�C�����J���Ƃ��납��
	string* stage_file;
	if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA)
	{
		stage_file = new string("../data/stage/stage1.cns");
	}
	else
	{
		stage_file = new string("../data/stage/extra1.cns");
	}
	FILE* fp;
	fp = fopen(stage_file->data(), "r");

	string* str;
	char temp_block_str[64];

	//�u���b�N�̌����擾
	fscanf(fp, "%d", &m_block_num); \

	//���̌������u���b�N�𐶐��B�����ɏ��������Ȃ����ǁc���[��
	m_blocks = new Block*[m_block_num]; //�I�u�W�F�N�g�𐶐�����ۂɗv�f����ϐ��Œ��ڎw��ł���͕̂֗�
	for (int i = 0; i < m_block_num; i++) //�����ǂ�������Ȃ��Ƃ����Ȃ��̂͊ԈႦ����
	{
		m_blocks[i] = new Block();
	}

	//�u���b�N�̍��W�Ƃ����擾�B�`����"x,y,hp"
	for (int i = 0; i < m_block_num; i++)
	{
		fscanf(fp, "%s", temp_block_str);
		str = new string(temp_block_str);
		string temp_str = Split(*str, ',', 1);

		if (temp_str[0] != '*')
		{
			int posx = atoi(temp_str.data());
			temp_str = Split(*str, ',', 2);
			int posy = atoi(temp_str.data());
			m_blocks[i]->SetPos(posx, posy);

			m_blocks[i]->m_hp = atoi(Split(*str, ',', 3).data());
			m_blocks[i]->SetColor();
		}
		else //����Ȏw�肾�����ꍇ�B�����č��W�w�肪�ʓ|�Ȗ�ł��B���Ƃ��o���Ȃ����Ȃ�
		{
			//��ŏC��
			/*
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_posx = int.Parse(temp_str[0]);
			int temp_posy = int.Parse(temp_str[1]);
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_numx = int.Parse(temp_str[0]);
			int temp_numy = int.Parse(temp_str[1]);
			str = sr.ReadLine();
			temp_str = str.Split(',');
			int temp_clearancex = int.Parse(temp_str[0]);
			int temp_clearancey = int.Parse(temp_str[1]);
			int temp_hp = int.Parse(temp_str[2]);
			int temp_sizex = m_blocks[i].GetSizeX();
			int temp_sizey = m_blocks[i].GetSizeY();
			for (int block_number = 0; block_number < m_block_num; block_number++)
			{
				m_blocks[block_number].SetPos(temp_posx + (temp_sizex + temp_clearancex) * ((block_number % temp_numx)), temp_posy + (temp_sizey + temp_clearancey) * (block_number / temp_numx));
				m_blocks[block_number].m_hp = temp_hp;
				m_blocks[block_number].SetColor();
			}
			break;*/
		}
		delete str;
	}

	//����string�^�g���Ă�Ӗ�����?
	char sound_str[128];
	fscanf(fp, "%s", sound_str);
	m_bgm_fileName = new string(sound_str); //bgm�̃t�@�C�������擾
	fclose(fp);
}


Message::MESSAGE Stage::Reaction() //�v�Z�Ƃ������Ƃ�����������֐�
{
	Message::MESSAGE ret = Message::MES_NONE;
	m_bar->Reaction(m_posx, m_sizex);
	ret = m_ball->Reaction(m_bar, this);
	switch (m_gamemain->GetState())
	{
	case GameMain::STATE_START:
	{
		PlayBgm();
		if (m_key->GetKeyTime(KEY_INPUT_Z) % 30 == 1)
		{
			m_gamemain->SetState(GameMain::STATE_PLAY);
			m_first_flag = false;
		}
	}
	break;
	case GameMain::STATE_PLAY:
	{
		PlayBgm();
		if (m_clearflag)
		{
			ret = Message::MES_GAME_CLEAR;
		}
		if (ret == Message::MES_FALL)
		{
			if (m_gamemain->m_players > 0)
			{
				m_gamemain->SetState(GameMain::STATE_FALL);
				m_gamemain->m_players--;
				m_gamemain->m_bombs = m_gamemain->MAX_BOMB;
			}
			else
			{
				m_gamemain->SetState(GameMain::STATE_GAMEOVER);
			}
		}
		if (m_key->GetKeyOn(KEY_INPUT_X))
		{
			if (m_gamemain->m_bombs > 0)
			{
				m_gamemain->SetState(GameMain::STATE_BOMB);
				m_gamemain->m_bombs--;
			}
		}
	}
	break;
	case GameMain::STATE_BOMB:
	{
		PlayBgm();
		if (m_gamemain->GetGameTime() == 120 - 2) //TODO:��̓I�Ȏ��Ԃ͌��
		{
			HitCheckBomb();
		}
		if (m_clearflag)
		{
			ret = Message::MES_GAME_CLEAR;
		}
		if (m_gamemain->GetGameTime() == 20)
		{
			PlaySound_Back(m_sound_bomb);
		}
		if (m_gamemain->GetGameTime() >= 120)
		{
			m_gamemain->SetState(GameMain::STATE_PLAY);
		}
	}
	break;
	case GameMain::STATE_FALL:
	{
		PlayBgm();
		if (m_gamemain->GetGameTime() >= 60)
		{
			m_gamemain->SetState(GameMain::STATE_START);
		}
	}
	break;
	case GameMain::STATE_GAMEOVER:
	{
		if (m_gamemain->GetGameTime() == 60)
		{
			StopSoundMem(m_sound_bgm);
		}
		if (m_key->GetKeyOn(KEY_INPUT_R))
		{
			m_gamemain->SetState(GameMain::STATE_TITLE);
			
			Reset();
			StopSoundMem(m_sound_gameover);
			ret = Message::MES_GO_TITLE;
		}
	}
	break;
	case GameMain::STATE_GAMECLEAR:
	{
		if (m_gamemain->GetGameTime() == 29)
		{
			StopSoundMem(m_sound_bgm);
		}
	}
	break;
	}

	return ret;
}


void Stage::PlayBgm()
{
	if (CheckSoundMem(m_sound_bgm))
	{

	}
	else //bgm���~�܂��Ă���ꍇ�Đ�
	{
		PlaySoundMem(m_sound_bgm, DX_PLAYTYPE_LOOP);
	}
}


GameMain::direction Stage::HitCheck() //�{�[���ƐڐG���Ă���u���b�N�����邩�ǂ������肷��
{
	int count = 0;
	GameMain::direction hitnumber = GameMain::DIRECT_NONE; //1�c�����瓖�������A2�c�E���瓖�������A3�c�ォ�瓖�������A4�c�����瓖������
	for (int i = 0; i < m_block_num; i++)
	{
		if (m_blocks[i]->m_hp > 0) //����Ă��Ȃ��u���b�N�������肷��
		{
			count++;
			hitnumber = m_ball->HitCheckSquare(m_blocks[i]->m_pointx, m_blocks[i]->m_pointy, m_blocks[i]->GetSizeX(), m_blocks[i]->GetSizeY()); //�`�F�b�N�p�̊֐�

			if (hitnumber != GameMain::DIRECT_NONE) //�������ĂȂ��Ȃ���Γ�����
			{
				//�����ɓ����������̏���(���Ƃ����˕Ԃ�Ƃ�)������
				//�u���b�N�̘V����
				m_blocks[i]->m_hp--;
				if (m_blocks[i]->m_hp > 0) //���鎞�Ƃ����łȂ����Ō��ʉ����Ⴄ
				{
					PlaySoundMem(m_sound_ball_block_nonbreak, DX_PLAYTYPE_BACK);
				}
				else
				{
					PlaySoundMem(m_sound_ball_block_break, DX_PLAYTYPE_BACK);
				}

				//���ˏ���
				m_ball->Refrection(hitnumber);
				return hitnumber; //���������炷���A��
			}
		}
	}
	if (count == 0)
	{
		m_clearflag = true;
	}

	return hitnumber;
}


void Stage::HitCheckBomb() //��̂Ƌ��ʂ��Ă邩�牽�Ƃ����������{���Ǘ���GameMain�N���X�����c
{
	int keep_mr = m_ball->m_r; //���a���o���Ă���
	m_ball->m_r = 60; //�{���̑傫���ɕς���BTODO:��������̓I�ɂ͌��
	for (int i = 0; i < m_block_num; i++)
	{
		if (m_blocks[i]->m_hp > 0) //����Ă��Ȃ��u���b�N�������肷��
		{
			//HitCheckSquare()���g���񂷗\�肾�������A�{�����傫���̂ŁA���S�ɓ����Ă��܂����u���b�N�Ƃ��͎擾�ł��Ȃ������̂ŕʊ֐������c
			if (HitCheckBlockToBomb(m_blocks[i]))
			{
				//�����ɓ����������̏���(��������?)������
				//TODO:�{���_���[�W�̓{���𕡐���ނ�������ۂɕς���
				if (m_gamemain->GetDiff() != GameMain::DIF_EXTRA) //extra�̓{������
				{
					m_blocks[i]->m_hp -= 3;
				}
			}
		}
	}
	m_ball->m_r = keep_mr; //���a�͌��ɖ߂�
}


bool Stage::HitCheckPointToBlock(int posx, int posy, Block* block)
{
	if (
		(block->m_pointx < posx && posx < block->m_pointx + block->GetSizeX()) && //�{�[���̓���̓_���l�p�`�̓����ɂ��邩�ǂ���
		(block->m_pointy < posy && posy < block->m_pointy + block->GetSizeY())
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Stage::HitCheckBlockToBomb(Block* block) //�{���N���X��������ق����悳�C�c?
{
	
	bool ret = false;
	if (pow(m_ball->m_pos_x - block->m_pointx, 2) + pow(m_ball->m_pos_y - block->m_pointy, 2) < pow(m_ball->m_r, 2))//����̓_
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - (block->m_pointx + block->GetSizeX()), 2) + pow(m_ball->m_pos_y - block->m_pointy, 2) < pow(m_ball->m_r, 2)) //�E��̓_
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - (block->m_pointx + block->GetSizeX()), 2) + pow(m_ball->m_pos_y - (block->m_pointy + block->GetSizeY()), 2) < pow(m_ball->m_r, 2)) //�E���̓_
	{
		ret = true;
	}
	else if (pow(m_ball->m_pos_x - block->m_pointx, 2) + pow(m_ball->m_pos_y - (block->m_pointy + block->GetSizeY()), 2) < pow(m_ball->m_r, 2)) //�����̓_
	{
		ret = true;
	}
	return ret;
}


GameMain::direction Stage::HitCheckBarToBall()
{
	GameMain::direction hitnumber = m_ball->HitCheckSquare(m_bar->m_posx, m_bar->m_posy, m_bar->GetSizeX(), m_bar->GetSizeY()); //�`�F�b�N�p�̊֐�

	if (hitnumber != GameMain::DIRECT_NONE) //�������ĂȂ��Ȃ���Γ�����
	{
		//���ˏ���
		m_ball->RefrectionBar(hitnumber, m_bar);
	}
	return hitnumber;
}


Message::MESSAGE Stage::HitCheckWall() //�{�[�����ǂƐڂ��ĂȂ����ǂ���
{
	int ball_size = m_ball->GetSize_r(); //����֐��Ăяo���̂��₾���L�����Ă���
	Message::MESSAGE ret = Message::MES_NONE;
	if (m_ball->m_pos_y - ball_size <= m_posy) //�㑤�̕ǂƂԂ����Ă��邩
	{
		m_ball->Refrection(GameMain::DIRECT_BUTTOM); //�㑤�̕ǂƂԂ�����=�u���b�N�̉��ɂԂ�����
		ret = Message::MES_WALL_BOUND; //SE��炷���߂Ɂc�т݂傢
	}
	else if (m_ball->m_pos_y + ball_size >= m_posy + m_sizey) //��
	{
		//���̕ǂƐڐG�����玀��
		ret = Message::MES_FALL;
	}
	else if (m_ball->m_pos_x - ball_size <= m_posx) //��
	{
		m_ball->Refrection(GameMain::DIRECT_RIGHT);
		ret = Message::MES_WALL_BOUND;
	}
	else if (m_ball->m_pos_x + ball_size >= m_posx + m_sizex) //�E
	{
		m_ball->Refrection(GameMain::DIRECT_LEFT);
		ret = Message::MES_WALL_BOUND;
	}

	return ret;
}