#ifndef _HEARTCONTAINER_
#define _HEARTCONTAINER_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
class HeartContainer : public Object {
private:
	bool triggered = false;
public:
	HeartContainer() {

	}
	HeartContainer(const HeartContainer& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = rect_Heart;
		heart_id = obj.heart_id;
	}
	~HeartContainer() {

	}
	void Pick(Character* player) {
		/*
		if (App->player->half_hearts_test_purpose == (App->player->hearts_containers_test_purpose * 2) - 1) {
			App->player->half_hearts_test_purpose++;
		}
		else if ((App->player->half_hearts_test_purpose / 2) <= (App->player->hearts_containers_test_purpose - 1)) {
			App->player->half_hearts_test_purpose += 2;
		}

		tokill = true;*/
	}



public:


	int heart_id = 0;

};


#endif

