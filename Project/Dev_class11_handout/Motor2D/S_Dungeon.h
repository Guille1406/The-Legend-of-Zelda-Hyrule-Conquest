#ifndef _DUNGEON_
#define _DUNGEON_

#include "MainScene.h"

class S_Dungeon : public MainScene {

public:
	bool Start();
	bool Update();
	bool Clean();
public:
	char* test = nullptr;
};

#endif // 

