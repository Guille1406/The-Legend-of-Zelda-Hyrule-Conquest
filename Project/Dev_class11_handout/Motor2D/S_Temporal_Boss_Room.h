#ifndef _TEMPBOSSROOM_
#define _TEMPBOSSROOM_

#include "MainScene.h"


class S_TempBossRoom : public MainScene {

public:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

public:
	char* test = nullptr;
	uint World_Audio;
};

#endif // 