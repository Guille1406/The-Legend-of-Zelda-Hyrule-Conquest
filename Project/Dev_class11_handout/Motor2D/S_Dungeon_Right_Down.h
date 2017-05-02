
#ifndef _DUNGEONRIGHTDOWN_
#define _DUNGEONRIGHTDOWN_

#include "MainScene.h"


class S_DungeonRightDown : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:

	uint World_Audio;
};

#endif // 

