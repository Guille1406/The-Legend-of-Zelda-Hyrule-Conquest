#ifndef _HEART_
#define _HEART_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
class Heart : public Object {
private:
	bool triggered = false;
public:
	Heart() {

	}
	Heart(const Heart& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = obj.texture_rect;
	}
	~Heart() {

	}
	void Pick(Character* player) {
		if (App->player->half_hearts_test_purpose == (App->player->hearts_containers_test_purpose * 2) - 1) {
			App->player->half_hearts_test_purpose++;
		}
		else if ((App->player->half_hearts_test_purpose/2)<=(App->player->hearts_containers_test_purpose-1)) {
			App->player->half_hearts_test_purpose += 2;
		}

		tokill = true;
	}



public:




};


#endif

