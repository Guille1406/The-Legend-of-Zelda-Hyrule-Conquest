#ifndef _ENDSCENE_
#define _ENDSCENE_

#include "MainScene.h"

class S_End : public MainScene {

public:
	bool Start();
	bool Update();
	bool Clean();
	bool PostUpdate();
public:
	char* test;
	SDL_Texture* finale_texture = nullptr;
};

#endif // 

