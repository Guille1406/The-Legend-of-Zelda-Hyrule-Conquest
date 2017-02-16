#ifndef _WORLD_
#define _WORLD_

#include "MainScene.h"


class S_World: public MainScene {

public:
	bool Start();
	bool Update();
	bool Clean();

public: 
	char* test;

};

#endif // 