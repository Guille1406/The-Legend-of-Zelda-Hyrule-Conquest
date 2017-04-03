#ifndef _DIANA_
#define _DIANA_
#include "j1Object.h"
#include"j1Render.h"
class Diana : public Object {
private:
	bool triggered = false;
public:
	Diana() {

	}
	Diana(const Diana& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = obj.texture_rect;
		dir = obj.dir;
	}
	~Diana() {

	}
	void Action() {
		for (int i = 0; i < connected_object.size(); i++) {

			connected_object[i]->Action();

		}
		switch (dir) {

			//UP
		case 0:
			texture_rect = rect_diana_up_active;
			break;

			//DOWN
		case 1:
			texture_rect = rect_diana_down_active;
			break;

			//LEFT
		case 2:
			texture_rect = rect_diana_left_active;
			break;

			//RIGHT
		case 3:
			texture_rect = rect_diana_right_active;
			break;
		}

	}

public:
	int dir = 0;

};

#endif