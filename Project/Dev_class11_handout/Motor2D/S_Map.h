#ifndef _MAP_
#define _MAP_

#include "MainScene.h"

class S_Map : public MainScene {

public:
	bool Start();
	bool Update();
	bool Clean();
public:
	char* test;
	SDL_Texture* map;
};

#endif // 

