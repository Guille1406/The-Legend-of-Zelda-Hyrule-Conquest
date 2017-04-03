#ifndef _WORLD_
#define _WORLD_

#include "MainScene.h"


class S_World: public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public: 
	char* test;
	uint World_Audio;
};

#endif // 