#ifndef _S_OPTIONSVIDEO_
#define _S_OPTIONSVIDEO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_OptionsVideo : public MainScene {

public:
	S_OptionsVideo();
	~S_OptionsVideo();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiLabel* VideoLabel = nullptr;
	GuiButton* scale = nullptr;
	GuiButton* fullscreen = nullptr;
	GuiCheck* fullscreen_check = nullptr;
	GuiButton* brightness = nullptr;
	GuiButton* vsync = nullptr;
	GuiCheck* vsync_check = nullptr;
	GuiButton* back = nullptr;
	std::vector<GuiButton*> buttons;
};

#endif // #pragma once
