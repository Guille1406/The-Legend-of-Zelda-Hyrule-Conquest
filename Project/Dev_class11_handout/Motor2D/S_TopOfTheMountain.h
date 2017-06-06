#ifndef _TOPOFTHEMOUNTAIN_
#define _TOPOFTHEMOUNTAIN_

#include "MainScene.h"


class S_TopOfTheMountain : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();

public:
	char* test = nullptr;
	uint World_Audio;
	bool temp = true;
	bool cutscene = false;
};

#endif // 

