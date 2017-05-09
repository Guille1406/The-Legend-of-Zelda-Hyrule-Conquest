#ifndef _S_VIDEOINTRO_
#define _S_VIDEOINTRO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_VideoIntro : public MainScene {

public:
	S_VideoIntro();
	~S_VideoIntro();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
};

#endif // #pragma once
