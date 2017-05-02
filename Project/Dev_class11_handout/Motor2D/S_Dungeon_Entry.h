#ifndef _DUNGEONENTRY_
#define _DUNGEONENTRY_

#include "MainScene.h"


class S_DungeonEntry : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:
	
	uint World_Audio;
};

#endif // 

