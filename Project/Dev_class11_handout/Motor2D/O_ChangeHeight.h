#ifndef _CHANGEHEIGHT_
#define _CHANGEHEIGHT_
#include "j1Object.h"

class ChangeHeight : public Object {
public:
	ChangeHeight() {

	}
	ChangeHeight(const ChangeHeight& obj) {

		this->rect = obj.rect;
		this->type = obj.type;
		this->active = obj.active;
	}
	~ChangeHeight() {

	}

public:
	int height;
};


#endif
