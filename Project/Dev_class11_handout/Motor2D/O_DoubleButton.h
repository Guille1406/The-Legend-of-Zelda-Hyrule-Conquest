#ifndef _DOUBLEBUTTON_
#define _DOUBLEBUTTON_
#include "j1Object.h"
#include"j1Render.h"
#include "j1Audio.h"
class DoubleButton : public Object {
private:
	bool triggered = false;
public:
	DoubleButton() {

	}
	DoubleButton(const DoubleButton& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = rect_double_button_idle;
		sound = false;
	}
	~DoubleButton() {

	}
	void Action() {
		if (characters_on == 1) {
			texture_rect = rect_double_button_one;
			return;
		}

		if (characters_on>=2) {
			
			texture_rect = rect_double_button_two;
			for (uint i = 0; i < connected_object.size(); i++) {
				connected_object[i]->Action();
			}
			if (!sound) {
				App->audio->PlayFx(App->audio->secret_sound);
				sound = true;
			}
			return;
		}
		
	}
		
	

public:

	bool first_character_pressing = false;
	bool second_character_pressing = false;
	int characters_on = 0;
	SDL_Rect idle_button = rect_button;
	SDL_Rect pressed_button = rect_pressed_button;
	SDL_Rect double_pressed_button = rect_pressed_button;
	bool sound = false;

};


#endif


