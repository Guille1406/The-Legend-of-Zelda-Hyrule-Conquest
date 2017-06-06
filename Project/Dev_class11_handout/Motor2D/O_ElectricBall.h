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
		active = false;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		//object_animation = obj.object_animation;
		object_animation.speed = 0.08f;
		actual_animation = obj.actual_animation;
		actual_animation.speed = 0.05;
		texture_rect = { 464,192,32,32 };
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


