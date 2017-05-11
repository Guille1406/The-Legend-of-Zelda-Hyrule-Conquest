#ifndef _LAKE_
#define _LAKE_

#include "MainScene.h"


class S_Lake : public MainScene {

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