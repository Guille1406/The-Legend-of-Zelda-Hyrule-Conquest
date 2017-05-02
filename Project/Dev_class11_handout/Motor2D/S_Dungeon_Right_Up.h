#ifndef _DUNGEONRIGHTUP_
#define _DUNGEONRIGHTUP_

#include "MainScene.h"


class S_DungeonRightUp : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:

	uint World_Audio;
};

#endif // 


