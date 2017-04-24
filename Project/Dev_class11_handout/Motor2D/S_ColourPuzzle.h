#ifndef _COLOURPUZZLE_
#define _COLOURPUZZLE_

#include "MainScene.h"


class S_ColourPuzzle : public MainScene {

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
