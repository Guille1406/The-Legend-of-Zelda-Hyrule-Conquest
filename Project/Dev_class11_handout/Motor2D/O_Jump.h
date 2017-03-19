#ifndef _JUMP_
#define _JUMP_
#include "j1Object.h"

class Jump : public Object {
public:
	Jump() {

	}
	Jump(const Jump& obj) {

		this->rect = obj.rect;
		this->type = obj.type;
		this->active = obj.active;
	}
	~Jump() {

	}

};


#endif
