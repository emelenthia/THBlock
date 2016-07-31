#include"GameMain.h"

GameMain* GameMain::instance;


GameMain::GameMain() 
{
	m_time = 0;
	m_difficulty = DIF_NORMAL;
	m_state = STATE_TITLE;

}


void GameMain::Reaction(Message::MESSAGE mes)
{

	m_time++;

	switch (mes)
	{
	case Message::MES_GAME_START:
	{
		m_state = STATE_START;

		//�Q�[���J�n���̏����ݒ�
		m_players = MAX_PLAYER;
		m_bombs = MAX_BOMB;
		m_time = 0;
		m_gametime = 0;
	}
	break;
	}
	/*
	switch (m_state)
	{
	case STATE_PLAY:
	{
		m_gametime++;
		if (Key_Manage.GetKeyOn(Key_Manage.KEYLIST.KEY_X))
		{
			if (m_bombs > 0)
			{
				m_state = STATE_BOMB;
				m_time = 0;
				m_bombs--;
			}
		}
	}
	break;
	case STATE_GAMECLEAR:
	{
		if (m_time == 40)
		{
			m_sound_clear.Play();
		}
		if (m_time == 60)
		{
			m_textinput = new Text_Input();
			m_textinput.ShowDialog(); //���͂̂��߂Ƀ��[�_���_�C�A���O�ŕ\��������
			RankingWriteFile();
			RankingReadFile();
			m_state = STATE_RANKING;
			m_time = 0;
		}
	}
	break;
	case STATE_RANKING:
	{
		if (m_time >= 10) //�ی��I��
		{
			if (Key_Manage.GetKeyOn(Key_Manage.KEYLIST.KEY_X)) //�L�����Z���{�^���Ń^�C�g���ɖ߂�
			{
				m_state = STATE_TITLE;
				m_ball = null; //�K����null���Ă����Ηǂ����ۂ�?�K�x�[�W�R���N�V�����̂��������
				m_bar = null;
				m_stage = null;
				m_time = 0;
				m_sound_clear.Stop();
			}
		}
	}
	break;
	}*/


	/*
	Message::MESSAGE ret = Message::MES_NONE, tempret = MESSAGES.NONE;





	switch (ret)
	{
	case MESSAGES.GAME_START:
	{
		s_state = STATE.START;
		m_stage = new Stage();
		m_ball = new Ball();
		m_bar = new Bar();
		//�Q�[���J�n���̏����ݒ�
		m_players = MAX_PLAYER;
		m_bombs = MAX_BOMB;
		m_gametime = 0;
		m_title_z_flag = true;
	}
	break;
	case MESSAGES.END:
	{
		Close();
	}
	break;
	case MESSAGES.GAME_CLEAR:
	{
		s_state = STATE.GAMECLEAR;
		s_time = 0; //����Astate���N���X�ɂ��āA=���I�[�o�[���[�h���āA������s_time��0��������悤�ɂ����ق����ǂ�������
	}
	break;
	case MESSAGES.RANKING:
	{
		RankingReadFile();
		s_state = STATE.RANKING;
		s_time = 0;
	}
	break;
	}

	if (Key_Manage.GetKeyOn(Key_Manage.KEYLIST.KEY_ESC)) //Esc�������ꂽ��Q�[�����I������B�I�����܂���?�_�C�A���O���������Ă��ǂ���������Ȃ�
	{
		Close();
	}*/
}


void GameMain::SetState(STATE state)
{
	m_state = state;
	m_time = 0;
}



	/*
	GameMain()
	{
		//��{�ݒ�
		this.Width = 640;
		this.Height = 480;
		this.Text = "�u���b�N����";

		//�`��p�̏ꏊ���m��
		m_pictureBox = new PictureBox();
		m_pictureBox.Width = this.Width;
		m_pictureBox.Height = this.Height;
		m_pictureBox.Location = new Point(0, 0);

		//�I�u�W�F�N�g�̐���
		m_font = new Font("�l�r �S�V�b�N", 12);
		m_font_go = new Font("�l�r �S�V�b�N", 24);
		m_title = new Title();
		m_key = new Key_Manage();
		m_bg_rank = Image.FromFile("./pic/free-background30895.jpg");

		//�C�x���g��ǉ�
		m_pictureBox.Paint += new PaintEventHandler(m_pictureBox_Paint);
		KeyDown += new KeyEventHandler(gameKeyDown);
		KeyUp += new KeyEventHandler(gameKeyUp);

		Controls.Add(m_pictureBox);

		//fps�\���֘A
		m_fps = m_draw_fps = 0;
		m_oldtime = System.Environment.TickCount;

		//���̑��ݒ�
		s_state = STATE.TITLE; //�K���^�C�g������n�܂�
		s_time = 0;
		s_difficulty = DIFFCULT.NORMAL; //�Ƃ肠����������Ă���
		m_ranknum = 0;
		m_stage_number = 1;
	}

	void m_pictureBox_Paint(object sender, PaintEventArgs e)
	{
		if (s_state == STATE.TITLE)
		{
			m_title.Draw(e);
		}
		else if (s_state == STATE.RANKING)
		{

		}
		else if (s_state != STATE.TITLE)
		{
			e.Graphics.DrawImage(m_bg_play, 0, 0);

			m_stage.Draw(e);
			m_ball.Draw(e);
			m_bar.Draw(e);
		}
		DrawGM(e);
	}

	public void Draw() //����͖��t���[���Ăяo��Draw()
	{
		Refresh(); //���ڕ`�悷��Ə�肭�s���Ȃ��̂ŁAPaint�C�x���g���Ăяo���Ă��
	}

	void DrawGM(PaintEventArgs e)
	{
		//���݂ɁA���̃N���X�Ɉȉ��̃R�[�h�������ƃt���[�Y����̂Œ���
		//Bitmap canvas = new Bitmap(m_pictureBox.Width, m_pictureBox.Height);
		//m_pictureBox.Image = canvas;

		SolidBrush s_brush = new SolidBrush(Color.Red); //���������������Ȃ��Ȃ��Ǝv���Ă���w�i�Ɠ����F���g���Ă�������
		String tempstr;

		switch (s_state)
		{
		case STATE.PLAY:
		{
			DrawInfo(e);
		}
		break;
		case STATE.FALL:
		{
			DrawInfo(e);
		}
		break;
		case STATE.BOMB:
		{
			DrawInfo(e);
		}
		break;
		case STATE.GAMECLEAR:
		{
			if (s_time > 30)
			{
				tempstr = "Game Clear";
				e.Graphics.DrawString(tempstr, m_font_go, s_brush, 120, 200);
			}
			DrawInfo(e);
		}
		break;
		case STATE.RANKING:
		{
			DrawRanking(e);
		}
		break;
		}

		s_brush.Dispose();
	}

	void DrawRanking(PaintEventArgs e) //�����L���O���̕\���B�^�C�g���V�[���ł��Ăяo��
	{
		String tempstr;
		Encoding sjisEnc = Encoding.GetEncoding("Shift_JIS"); //2�o�C�g���ʂ̂���

		e.Graphics.DrawImage(m_bg_rank, 0, 0); //�w�i

		for (int i = 0; i < m_ranknum; i++)
		{
			if (i < 9)
			{
				tempstr = " ";
			}
			else
			{
				tempstr = "";
			}
			tempstr += (i + 1).ToString() + "��   " + m_ranking[i].name;
			for (int charcount = sjisEnc.GetByteCount(m_ranking[i].name); charcount < 11; charcount++)
			{
				tempstr += " "; //%11d�݂����Ȍ��Ԓ���
			}
			tempstr += ":   " + m_ranking[i].score.ToString() + " f";
			e.Graphics.DrawString(tempstr, m_font_go, Brushes.Violet, 80, 40 + i * 30);
		}

		e.Graphics.DrawString("X�L�[�Ń^�C�g���ɖ߂�", m_font, Brushes.Black, 10, 410);
	}

	public void CulFps()
	{
		m_fps++;
		if (System.Environment.TickCount >= m_oldtime + 1000)
		{
			m_draw_fps = m_fps;
			m_oldtime = System.Environment.TickCount;
			m_fps = 0;
		}
	}

	void RankingWriteFile() //�����L���O���t�@�C���ɏ������ނ���
	{
		using (StreamWriter fp = new StreamWriter("./scn/ranking.cns", true)) //true���ƒǉ���������
		{
			String writestr = s_name + "," + m_gametime.ToString() + '\n';
			fp.Write(writestr);
		}
	}

	void RankingReadFile() //�����L���O���t�@�C������ǂݍ��ނ���
	{
		using (StreamReader fp = new StreamReader("./scn/ranking.cns", true)) //true���ƒǉ���������
		{
			String[] readstr;
			RANKING[] temp_ranking;
			ArrayList arraylist = new ArrayList(); //������Ƃ͎g���Ă݂悤�Ǝv����

			int array_num = 0;
			while (fp.EndOfStream == false) //EOF�Ȃ�true���ۂ���
			{
				readstr = fp.ReadLine().Split(',');
				RANKING t_rank;
				t_rank.name = readstr[0];
				t_rank.score = int.Parse(readstr[1]);
				arraylist.Add(t_rank);
				array_num++;
			}

			if (array_num > 1) //�ی��I��
			{
				QuickSort(arraylist, 0, array_num - 1);
			}

			m_ranknum = (RANKING_MAX < array_num ? RANKING_MAX : array_num);
			//�����L���O�p�̔z��ɃR�s�[����
			for (int i = 0; i < m_ranknum; i++)
			{
				m_ranking[i] = (RANKING)arraylist[i];
			}
		}
	}

	void QuickSort(ArrayList arraylist, int left, int right)//�����N�C�b�N�\�[�g�Bwikipedia���Q�l�ɁB
	{
		if (left < right)
		{
			//�܂��̓s�{�b�g�̐ݒ�
			int pivot = ((RANKING)arraylist[left]).score;
			int left_count = left, right_count = right;

			while (true)
			{
				while (((RANKING)arraylist[left_count]).score < pivot) //������T���B�s�{�b�g�ȉ��̂�T�������̃��[�v
				{
					++left_count;
				}
				while (((RANKING)arraylist[right_count]).score > pivot) //�E����T��
				{
					--right_count; //�������̓f�N�������g�Ȃ̂ɒ���
				}
				if (left_count >= right_count) //���̒T���҂��E����̒T���҂Əo�������
				{
					break;
				}
				//�����ɗ������Ă��Ƃ͍��ƉE�̒T���҂͗ǂ������̂����������Ă��ƂȂ̂�
				//����ւ���c�������ւ��p�̊֐��������肵�Ȃ��̂���
				RANKING keep_ranking;
				keep_ranking.name = ((RANKING)arraylist[left_count]).name;
				keep_ranking.score = ((RANKING)arraylist[left_count]).score;

				arraylist[left_count] = arraylist[right_count];
				arraylist[right_count] = keep_ranking;

				++left_count;
				--right_count;
			}
			QuickSort(arraylist, left, left_count - 1); //�������������ċA�I�Ƀ\�[�g
			QuickSort(arraylist, right_count + 1, right); //���������E���ċA�I�Ƀ\�[�g�B�����Ă�
		}
	}

	private void gameKeyDown(object sender, KeyEventArgs k)
	{
		m_key.CheckDownKey(k);
	}

	private void gameKeyUp(object sender, KeyEventArgs k) //�����ɗ������ɘA��Ă���k�́A��������Ă���L�[�}�b�v�������Ă���̂ł͂Ȃ��A���������L�[�������Ă���
	{
		m_key.CheckUpKey(k);
	}

}
*/