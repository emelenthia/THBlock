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

		//ゲーム開始時の初期設定
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
			m_textinput.ShowDialog(); //入力のためにモーダルダイアログで表示させる
			RankingWriteFile();
			RankingReadFile();
			m_state = STATE_RANKING;
			m_time = 0;
		}
	}
	break;
	case STATE_RANKING:
	{
		if (m_time >= 10) //保険的な
		{
			if (Key_Manage.GetKeyOn(Key_Manage.KEYLIST.KEY_X)) //キャンセルボタンでタイトルに戻る
			{
				m_state = STATE_TITLE;
				m_ball = null; //適当にnullしておけば良いっぽい?ガベージコレクションのちからって
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
		//ゲーム開始時の初期設定
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
		s_time = 0; //これ、stateをクラスにして、=をオーバーロードして、同時にs_timeに0を代入するようにしたほうが良かったな
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

	if (Key_Manage.GetKeyOn(Key_Manage.KEYLIST.KEY_ESC)) //Escが押されたらゲームを終了する。終了しますか?ダイアログを実装しても良いかもしれない
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
		//基本設定
		this.Width = 640;
		this.Height = 480;
		this.Text = "ブロック崩せ";

		//描画用の場所を確保
		m_pictureBox = new PictureBox();
		m_pictureBox.Width = this.Width;
		m_pictureBox.Height = this.Height;
		m_pictureBox.Location = new Point(0, 0);

		//オブジェクトの生成
		m_font = new Font("ＭＳ ゴシック", 12);
		m_font_go = new Font("ＭＳ ゴシック", 24);
		m_title = new Title();
		m_key = new Key_Manage();
		m_bg_rank = Image.FromFile("./pic/free-background30895.jpg");

		//イベントを追加
		m_pictureBox.Paint += new PaintEventHandler(m_pictureBox_Paint);
		KeyDown += new KeyEventHandler(gameKeyDown);
		KeyUp += new KeyEventHandler(gameKeyUp);

		Controls.Add(m_pictureBox);

		//fps表示関連
		m_fps = m_draw_fps = 0;
		m_oldtime = System.Environment.TickCount;

		//その他設定
		s_state = STATE.TITLE; //必ずタイトルから始まる
		s_time = 0;
		s_difficulty = DIFFCULT.NORMAL; //とりあえず代入しておく
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

	public void Draw() //これは毎フレーム呼び出すDraw()
	{
		Refresh(); //直接描画すると上手く行かないので、Paintイベントを呼び出してやる
	}

	void DrawGM(PaintEventArgs e)
	{
		//因みに、このクラスに以下のコードを書くとフリーズするので注意
		//Bitmap canvas = new Bitmap(m_pictureBox.Width, m_pictureBox.Height);
		//m_pictureBox.Image = canvas;

		SolidBrush s_brush = new SolidBrush(Color.Red); //何か文字が書けないなあと思ってたら背景と同じ色を使っていたあほ
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

	void DrawRanking(PaintEventArgs e) //ランキング情報の表示。タイトルシーンでも呼び出す
	{
		String tempstr;
		Encoding sjisEnc = Encoding.GetEncoding("Shift_JIS"); //2バイト判別のため

		e.Graphics.DrawImage(m_bg_rank, 0, 0); //背景

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
			tempstr += (i + 1).ToString() + "位   " + m_ranking[i].name;
			for (int charcount = sjisEnc.GetByteCount(m_ranking[i].name); charcount < 11; charcount++)
			{
				tempstr += " "; //%11dみたいな隙間調整
			}
			tempstr += ":   " + m_ranking[i].score.ToString() + " f";
			e.Graphics.DrawString(tempstr, m_font_go, Brushes.Violet, 80, 40 + i * 30);
		}

		e.Graphics.DrawString("Xキーでタイトルに戻る", m_font, Brushes.Black, 10, 410);
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

	void RankingWriteFile() //ランキングをファイルに書き込むだけ
	{
		using (StreamWriter fp = new StreamWriter("./scn/ranking.cns", true)) //trueだと追加書き込み
		{
			String writestr = s_name + "," + m_gametime.ToString() + '\n';
			fp.Write(writestr);
		}
	}

	void RankingReadFile() //ランキングをファイルから読み込むだけ
	{
		using (StreamReader fp = new StreamReader("./scn/ranking.cns", true)) //trueだと追加書き込み
		{
			String[] readstr;
			RANKING[] temp_ranking;
			ArrayList arraylist = new ArrayList(); //ちょっとは使ってみようと思った

			int array_num = 0;
			while (fp.EndOfStream == false) //EOFならtrueっぽいよ
			{
				readstr = fp.ReadLine().Split(',');
				RANKING t_rank;
				t_rank.name = readstr[0];
				t_rank.score = int.Parse(readstr[1]);
				arraylist.Add(t_rank);
				array_num++;
			}

			if (array_num > 1) //保険的な
			{
				QuickSort(arraylist, 0, array_num - 1);
			}

			m_ranknum = (RANKING_MAX < array_num ? RANKING_MAX : array_num);
			//ランキング用の配列にコピーする
			for (int i = 0; i < m_ranknum; i++)
			{
				m_ranking[i] = (RANKING)arraylist[i];
			}
		}
	}

	void QuickSort(ArrayList arraylist, int left, int right)//多分クイックソート。wikipediaを参考に。
	{
		if (left < right)
		{
			//まずはピボットの設定
			int pivot = ((RANKING)arraylist[left]).score;
			int left_count = left, right_count = right;

			while (true)
			{
				while (((RANKING)arraylist[left_count]).score < pivot) //左から探索。ピボット以下のを探すだけのループ
				{
					++left_count;
				}
				while (((RANKING)arraylist[right_count]).score > pivot) //右から探索
				{
					--right_count; //こっちはデクリメントなのに注意
				}
				if (left_count >= right_count) //左の探索者が右からの探索者と出会ったら
				{
					break;
				}
				//ここに来たってことは左と右の探索者は良い感じのを見つけたってことなので
				//入れ替える…これ入れ替え用の関数あったりしないのかな
				RANKING keep_ranking;
				keep_ranking.name = ((RANKING)arraylist[left_count]).name;
				keep_ranking.score = ((RANKING)arraylist[left_count]).score;

				arraylist[left_count] = arraylist[right_count];
				arraylist[right_count] = keep_ranking;

				++left_count;
				--right_count;
			}
			QuickSort(arraylist, left, left_count - 1); //分割した左を再帰的にソート
			QuickSort(arraylist, right_count + 1, right); //分割した右を再帰的にソート。だってさ
		}
	}

	private void gameKeyDown(object sender, KeyEventArgs k)
	{
		m_key.CheckDownKey(k);
	}

	private void gameKeyUp(object sender, KeyEventArgs k) //ここに来た時に連れてきたkは、今押されているキーマップが入っているのではなく、今離したキーが入っている
	{
		m_key.CheckUpKey(k);
	}

}
*/