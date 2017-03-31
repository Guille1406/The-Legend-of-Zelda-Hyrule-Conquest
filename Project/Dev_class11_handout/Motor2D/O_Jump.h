#ifndef _JUMP_
#define _JUMP_
#include "j1Object.h"

class Jump : public Object {
public:
	Jump() {

	}
	Jump(const Jump& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
	}
	~Jump() {

	}

};


#endif
