#ifndef _DOUBLEBUTTON_
#define _DOUBLEBUTTON_
#include "j1Object.h"
#include"j1Render.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "Video.h"
#include "j1Enemy.h"
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
		
		sound = false;
		cutscene = obj.cutscene;

		bool temp = false;
		
		if (cutscene == 2) {
			idle_button = rect_double_button_music_idle;
			pressed_button = rect_double_button_music_one;
			double_pressed_button = rect_double_button_music_pressed;
		}
		else {
			idle_button = rect_double_button_idle;
			pressed_button = rect_double_button_one;
			double_pressed_button = rect_double_button_two;
			
		}
		
	}
	~DoubleButton() {

	}
	void Action() {
		if (characters_on == 1) {
			texture_rect = pressed_button;
			if(can_reproduce_audio)

			return;
		}

		if (characters_on>=2) {
			
			texture_rect = double_pressed_button;
			
			for (uint i = 0; i < connected_object.size(); i++) {
				connected_object[i]->Action();
				if (connected_object[i]->type == objectType::object_music)
					return;
			}
			if (cutscene == 1 && !App->scene->blocks_out) {
				//App->cutscenemanager->StartCutscene(cutscene_intro);
				App->scene->blocks_out = true;
				SDL_Rect r = { 0,0,1280,720 };
				App->videoplayer->PlayVideo("unlock-door.ogv",r);
				App->videoplayer->video_finished = false;
				App->scene->puzzle_video_finished = true;		
				App->enemy->paused = true;
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
	int cutscene = 0;
	bool can_reproduce_audio = true;

};


#endif


