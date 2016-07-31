#include "Scene.h"
#include"Flag.h"

Scene::Scene()
{
	m_title = new Title;
	m_stage = Stage::GetInstance();
	scene_now = m_title;
	Flag::nowscene = 0x4141e;
	m_gamemain = GameMain::GetInstance();
}


Scene::~Scene()
{
}


void Scene::Draw()
{
	scene_now->Draw();
}


Message::MESSAGE Scene::Reaction()
{
	Message::MESSAGE ret = Message::MES_NONE;
	ret = scene_now->Reaction();


	//�����Ń��b�Z�[�W����?
	switch (ret)
	{
	case Message::MES_GAME_START:
	{
		scene_now = m_stage;
		m_stage->SetInfo();
	}
	break;
	case Message::MES_GO_TITLE:
	{
		scene_now = m_title;
	}
	break;
	}
	m_gamemain->Reaction(ret);

	/*if (Flags::nowscene == 0xf1e1d && scene_now != &dungeon) //�_���W�����Ɉڍs����M�����󂯎������
	{
		//�_���W�����ɓ������ۂ̏�����
		if (scene_now == &guild)
		{
			dungeon.LoadDungeon();
		}
		scene_now = &dungeon; //�_���W�����Ɉڍs����
	}
	if (Flags::nowscene == 0x8011d && scene_now != &guild) //�M���h�Ɉڍs����M�����󂯎������
	{
		scene_now = &guild; //�M���h�Ɉڍs����
	}*/

	return ret;
}