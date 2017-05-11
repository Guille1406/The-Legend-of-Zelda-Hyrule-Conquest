#ifndef _ELECTRICBALL_
#define _ELECTRICBALL_
#include "j1Object.h"
#include "Character.h"

class ElectricBall : public Object {
public:
	ElectricBall() {

	}
	ElectricBall(const ElectricBall& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		active = true;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		//object_animation = obj.object_animation;
		object_animation.speed = 0.08f;
		texture_rect = { 0,0,0,0 };
		active_phase = obj.active_phase;
	}
	~ElectricBall() {

	}

	void Action() {


	};
public:
	int active_phase = 0;
};


#endif


