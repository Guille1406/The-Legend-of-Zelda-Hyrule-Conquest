#ifndef _S_OPTIONSCONTROLS_
#define _S_OPTIONSCONTROLS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_OptionsControls : public MainScene {

public:
	S_OptionsControls();
	~S_OptionsControls();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	SDL_Rect controller_layout_normal_rect = { 0,0,0,0 };
	SDL_Rect controller_layout_alternative_rect = { 0,0,0,0 };
	GuiImage* controller_layout_normal = nullptr;
	GuiImage* controller_layout_alternative = nullptr;
	GuiButton* ControlsLabel = nullptr;
	GuiButton* ControllerAlternative = nullptr;
	GuiCheck*  ControllerAlternative_check = nullptr;
	GuiButton* back = nullptr;
	bool alternative_active = false;
};

#endif // #pragma once
