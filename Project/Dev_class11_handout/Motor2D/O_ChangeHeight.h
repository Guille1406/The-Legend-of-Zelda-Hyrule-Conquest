#ifndef _CHANGE_HEIGHT_
#define _CHANGE_HEIGHT_
#include "j1Object.h"

class ChangeHeight : public Object {
public:
	ChangeHeight() {

	}
	ChangeHeight(const ChangeHeight& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		height = obj.height;
		name = obj.name;
		logic_height = obj.logic_height;
	}
	~ChangeHeight() {

	}

public: 
	int height;
};


#endif

