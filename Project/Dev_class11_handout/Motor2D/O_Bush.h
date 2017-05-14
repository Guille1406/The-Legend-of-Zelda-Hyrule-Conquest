#ifndef _BUSH_
#define _BUSH_
#include "j1Object.h"
#include "Character.h"
#include <time.h>

class Bush : public Object {
public:
	Bush() {

	}
	Bush(const Bush& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		active = true;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		object_animation = obj.object_animation;
		object_animation.speed = 0.08f;
		texture_rect = rect_bush;
	}
	~Bush() {

	}

	void Action() {
		srand(time(NULL));
		int what_drope = 0;
		what_drope = rand() % 25;
		switch (what_drope) {

		case 0:
			//Drop nothing
			break;
		case 1:
			App->object->CreateHeart(this, this->logic_height);
			break;
			//If we finally add fire arrows
			break;
		}

	};
public:

};


#endif

