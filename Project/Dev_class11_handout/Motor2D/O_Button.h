#ifndef _BUTTON_
#define _BUTTON_
#include "j1Object.h"
#include"j1Render.h"
class Button : public Object {
private:
	bool triggered;
public:
	Button() {
		
	}
	Button(const Button& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = idle_button;
	}
	~Button() {

	}
	void Action() {
		for (int i = 0; i < connected_object.size(); i++) {

			connected_object[i]->Action();

		}
	}

public:

	SDL_Rect idle_button = rect_button;
	SDL_Rect pressed_button = rect_pressed_button;
	
};


#endif

