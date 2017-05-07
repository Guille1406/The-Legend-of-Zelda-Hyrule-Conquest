#ifndef _FOREST_
#define _FOREST_

#include "MainScene.h"


class S_Forest : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

public:
	//std::vector
	char* test = nullptr;
	uint World_Audio;
};

#endif // 