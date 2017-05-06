#ifndef _BEFOREDUNGEON_
#define _BEFOREDUNGEON_

#include "MainScene.h"


class S_BeforeDungeon : public MainScene {

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
