#ifndef _BUTTON_
#define _BUTTON_

#include "j1Object.h"
#include"j1Render.h"
#include "O_Music.h"

enum buttoncolor {
	nonecolor,
	blue,
	red,
	green,
	yellow,
};

class Button : public Object {
private:
	bool triggered= false;

public:
	Button()
	{
		
	}

	Button(const Button& obj)
	{
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		color = obj.color;
		texture_rect = rect_button;
		note = obj.note;
		switch (color) {
		case buttoncolor::blue:
			texture_rect = rect_blue_button_idle;
			break;
		case buttoncolor::red:
			texture_rect = rect_red_button_idle;
			break;
		case buttoncolor::green:
			texture_rect = rect_green_button_idle;
			break;
		case buttoncolor::yellow:
			texture_rect = rect_yellow_button_idle;
			break;
		case buttoncolor::nonecolor:
			texture_rect = idle_button;
			break;
		}
	}

	~Button()
	{

	}
	void Action(int note)
	{
		switch (color) {
		case buttoncolor::blue:
			texture_rect = rect_blue_button_pressed;
			break;
		case buttoncolor::red:
			texture_rect = rect_red_button_pressed;
			break;
		case buttoncolor::green:
			texture_rect = rect_green_button_pressed;
			break;
		case buttoncolor::yellow:
			texture_rect = rect_yellow_button_pressed;
			break;
		case buttoncolor::nonecolor:
			texture_rect = pressed_button;
		}

		for (uint i = 0; i < connected_object.size(); i++)
		{
			if (connected_object[i]->type == objectType::object_music) {
				Object_Music* temp = (Object_Music*)connected_object[i];
				temp->Action(note);
			}
		}
	}
	void Action()
	{
		
		switch (color) {
		case buttoncolor::blue:
			texture_rect = rect_blue_button_pressed;
			break;
		case buttoncolor::red:
			texture_rect = rect_red_button_pressed;
			break;
		case buttoncolor::green:
			texture_rect = rect_green_button_pressed;
			break;
		case buttoncolor::yellow:
			texture_rect = rect_yellow_button_pressed;
			break;
		case buttoncolor::nonecolor:
			texture_rect = pressed_button;
		}
		for (uint i = 0; i < connected_object.size(); i++)
		{
			connected_object[i]->Action();
		}
		
	}
	void EndAction() {
		
		switch (color) {
		case buttoncolor::blue:
			texture_rect = rect_blue_button_idle;
			break;
		case buttoncolor::red:
			texture_rect = rect_red_button_idle;
			break;
		case buttoncolor::green:
			texture_rect = rect_green_button_idle;
			break;
		case buttoncolor::yellow:
			texture_rect = rect_yellow_button_idle;
			break;
		case buttoncolor::nonecolor:
			texture_rect = idle_button;
		}
		for (uint i = 0; i < connected_object.size(); i++)
		{
			connected_object[i]->EndAction();
		}
	}

public:

	SDL_Rect idle_button = rect_button;
	SDL_Rect pressed_button = rect_pressed_button;
	buttoncolor color = nonecolor;
	int note = 0;
};

#endif