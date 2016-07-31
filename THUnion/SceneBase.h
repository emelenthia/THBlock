#pragma once
#include"Message.h"

class SceneBase
{
public:
	SceneBase();
	~SceneBase();
	virtual void Draw() = 0;
	virtual Message::MESSAGE Reaction() = 0;
};
