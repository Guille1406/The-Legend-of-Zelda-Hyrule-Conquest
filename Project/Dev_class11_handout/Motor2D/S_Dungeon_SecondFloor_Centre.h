#ifndef _DUNGEON_SECONDFLOOR_CENTRE_
#define _DUNGEON_SECONDFLOOR_CENTRE_

#include "MainScene.h"


class S_DungeonSecondFloorCentre : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:

	uint World_Audio;
};

#endif // 

