
#include "DxLib.h"
#include"Flag.h"
#include"Scene.h"
#include"FPSer.h"
#include"Common_TH.h"
#include"Key_Input.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	SetMainWindowText("�������ŋ�"); //�^�C�g���̎w��B���ɂ��悤
	SetDrawScreen(DX_SCREEN_BACK);
	//SetBackgroundColor(0, 0, 0); //�w�i�̐F�ύX5
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Scene scene; //���݂̏��
	Key_Input* m_key; //�L�[���͗p
	m_key = Key_Input::GetInstance();
						 //int reaction_return; //Reaction()�̕Ԃ�l���󂯎��
	Flag flag;
	//Events *events = Events::GetInstance();
	//Colors colors; //�R���X�g���N�^
	FPSer fpser;
	Common_TH common_th; //����������

	while (1) //���C�����[�v
	{

		ClearDrawScreen(); //��ʂ��N���A�B�`�揈���͂������ɏ���

		m_key->KeyUpdate();
		//key_input.KeyUpdate(); //�L�[����
							   //reaction_return = nowpointa->Reaction(); //�L�[���͂Ȃǂɂ����̍X�V
		scene.Reaction(); //�L�[���͂Ȃǂɂ����̍X�V
		scene.Draw(); //���݂̏�ʂ̕`��
		fpser.CountFPS(); //�f�o�b�O�I��

		ScreenFlip(); //���ƕ\�̒�����B�`�揈��������ɏ���


		if (ProcessMessage()) //�~�N���b�N�҂�
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)  //Esc���͑҂�
		{
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
