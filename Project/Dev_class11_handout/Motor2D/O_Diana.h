#ifndef _DIANA_
#define _DIANA_
#include "j1Object.h"
#include"j1Render.h"
class Diana : public Object {
private:
	bool triggered;
public:
	Diana() {

	}
	Diana(const Diana& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
	}
	~Diana() {

	}
	void Action() {
		for (int i = 0; i < connected_object.size(); i++) {

			connected_object[i]->Action();

		}
	}

public:

};

#endif