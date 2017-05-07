#ifndef _SECRETEXIT_
#define _SECRETEXIT_

#include "MainScene.h"


class S_SecretExit : public MainScene {

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