#ifndef _CHEST_
#define _CHEST_
#include "j1Object.h"

class Chest : public Object {
public:
	Chest() {

	}
	Chest(const Chest& obj) {
		
		this->rect = obj.rect;
		this->type = obj.type;
		this->active = obj.active;
	}
	~Chest() {
	
	}

};


#endif
