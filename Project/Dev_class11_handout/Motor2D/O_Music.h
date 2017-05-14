#ifndef _OBJECTMUSIC_
#define _OBJECTMUSIC_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
#include "j1Audio.h"
class Object_Music : public Object {
private:
	bool triggered = false;
public:
	Object_Music() {

	}
	Object_Music(const Object_Music& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;

		notes[0] = App->audio->LoadFx("audio/fx/note_1.wav");
		notes[1] = App->audio->LoadFx("audio/fx/note_2.wav");
		notes[2] = App->audio->LoadFx("audio/fx/note_3.wav");
		notes[3] = App->audio->LoadFx("audio/fx/note_4.wav");

		
		object_music = App->audio->LoadFx("audio/fx/Zelda Lullaby.wav");
	
	}
	~Object_Music() {

	}

	void Action(int note) {
		for (; count < 8; count++) {
			if (temp_notes[count] == 0) {
				temp_notes[count] = note;
				if (temp_notes[count] != notes_order[count]) {
					for (int n = 0; n < 8; n++) {
						temp_notes[n] = 0;
						count = 0;

					}
				}
				break;
			}
			
			
		}
		if (temp_notes[7] == notes_order[7]) {
			for (uint i = 0; i < connected_object.size(); i++)
			{
				
				connected_object[i]->Action();
			
			}
		}
		
		
		App->audio->PlayFx(notes[note - 1]);
	}
	void Action() {
		App->audio->StopMusic(0);
		if (music_delay.Read() > 3000) {
			App->audio->PlayFx(object_music);
			music_delay.Start();
		}

	}

public:
	int temp_notes[8] = { 0,0,0,0,0,0,0,0 };
	int notes_order[8] = { 1,2,3,4,3,1,2,3 };
	uint notes[4] = { 0,0,0,0 };
	uint object_music =0;
	int count = 0;
	j1Timer music_delay;
};


#endif

