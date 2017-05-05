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
		App->audio->PlayFx(notes[note - 1]);
	}
	void Action() {

		App->audio->PlayFx(object_music);

	}

public:
	uint notes[4] = { 0,0,0,0 };
	uint object_music =0;
};


#endif

