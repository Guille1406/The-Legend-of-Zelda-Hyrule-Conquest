#ifndef _UI_WINDOW
#define _UI_WINDOW

#include "j1Gui.h"
#include "j1Module.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_Label.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )



class UI_Window : public UI_Component {
public:
	void Draw() {
		App->render->Blit(App->gui->atlas, pos_x - App->render->camera.x, pos_y - App->render->camera.y, &rect_atlas);
		p2List_item<UI_Component*>* temp = window_components.start;
		while (temp != NULL) {
			temp->data->Draw();
		}

	};

public:

	//Constructors
	UI_Window() {};

	

	~UI_Window() {};

public:
	p2List < UI_Component* > window_components;
	UI_Label title;

};



#endif

