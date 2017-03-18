#ifndef _CHANGE_HEIGHT_
#define _CHANGE_HEIGHT_
#include "j1Object.h"

class ChangeHeight : public Object {
public:
	ChangeHeight() {

	}
	ChangeHeight(const ChangeHeight& obj) {

		this->rect = obj.rect;
		this->type = obj.type;
		this->active = obj.active;
		this->height = obj.height;
	}
	~ChangeHeight() {

	}

public: 
	int height;
};


#endif

