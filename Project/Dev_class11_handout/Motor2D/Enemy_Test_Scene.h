#ifndef _ENEMY_TEST_SCENE_
#define _ENEMY_TEST_SCENE_

#include "MainScene.h"


class S_Enemy_Test_Scene : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:
	char* test = nullptr;
	uint World_Audio;
};

#endif // 