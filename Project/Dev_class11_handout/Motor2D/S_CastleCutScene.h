#ifndef _S_CASTLE_CUT_SCENE_
#define _S_CASTLE_CUT_SCENE_

#include "MainScene.h"


class S_CastleCutScene : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:
	char* test = nullptr;
	uint World_Audio;
	bool done = false;
};

#endif // 