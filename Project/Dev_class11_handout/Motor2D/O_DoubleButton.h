#ifndef _DOUBLEBUTTON_
#define _DOUBLEBUTTON_
#include "j1Object.h"
#include"j1Render.h"
class DoubleButton : public Object {
private:
	bool triggered;
public:
	DoubleButton() {

	}
	DoubleButton(const DoubleButton& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = idle_button;
	}
	~DoubleButton() {

	}
	void Action() {
		
		if (characters_on>=2) {
			for (int i = 0; i < connected_object.size(); i++) {
				connected_object[i]->Action();
			}
		}
	}
		
	

public:

	bool first_character_pressing;
	bool second_character_pressing;
	int characters_on =0;
	SDL_Rect idle_button = rect_button;
	SDL_Rect pressed_button = rect_pressed_button;
	SDL_Rect double_pressed_button = rect_pressed_button;

};


#endif


