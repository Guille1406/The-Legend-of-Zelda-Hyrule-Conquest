#ifndef _BRIDGE_
#define _BRIDGE_
#include "j1Object.h"

class Bridge : public Object {
public:
	Bridge() {

	}
	Bridge(const Bridge& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		height = obj.height;
		name = obj.name;
		logic_height = obj.logic_height;
		texture_rect = obj.rect;
	}
	~Bridge() {

	}

public:
	int height = 0;
};


#endif

