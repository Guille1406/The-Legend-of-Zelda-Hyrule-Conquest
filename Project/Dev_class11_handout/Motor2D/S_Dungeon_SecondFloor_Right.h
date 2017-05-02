#ifndef _DUNGEON_SECONDFLOOR_RIGHT_
#define _DUNGEON_SECONDFLOOR_RIGHT_

#include "MainScene.h"


class S_DungeonSecondFloorRight : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:

	uint World_Audio;
};

#endif // 

