#pragma once
#include"Title.h"
#include"Message.h"
#include"Stage.h"
#include"GameMain.h"

class Scene //各シーンを遷移
{
public:
	Scene();
	~Scene();
	void Draw();
	Message::MESSAGE Reaction();

private:
	Stage* m_stage;
	Title* m_title;
	SceneBase* scene_now;
	GameMain* m_gamemain;
};

