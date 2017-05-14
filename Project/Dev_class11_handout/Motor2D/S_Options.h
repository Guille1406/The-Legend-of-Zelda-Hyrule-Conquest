#ifndef _S_OPTIONS_
#define _S_OPTIONS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_Options : public MainScene {

public:
	S_Options();
	~S_Options();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* OptionsLabel = nullptr;
	GuiButton* controls = nullptr;
	GuiButton* video = nullptr;
	//GuiButton* audio = nullptr;
	GuiButton* gameplay = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
