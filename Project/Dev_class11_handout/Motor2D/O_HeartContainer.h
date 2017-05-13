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
		this->collider->to_delete = true;
		App->player->hearts_containers_test_purpose++;
		App->player->half_hearts_test_purpose++;
		App->player->half_hearts_test_purpose++;
		if (heart_id == 1) {
			App->scene->heart_1 = false;
			active = false;
		}
		if (heart_id == 2) {
			App->scene->heart_2 = false;
			active = false;
		}
		if (heart_id == 3) {
			App->scene->heart_3 = false;
			active = false;
		}
		if (heart_id == 4) {
			App->scene->heart_4 = false;
			active = false;
		}
		if (heart_id == 5) {
			App->scene->heart_5 = false;
			active = false;
		}
		
	}



public:


	int heart_id = 0;

};


#endif

