#ifndef _BUSH_
#define _BUSH_
#include "j1Object.h"
#include "Character.h"

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


	};
public:

};


#endif

