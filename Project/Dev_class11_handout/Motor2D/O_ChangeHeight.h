#ifndef _CHANGE_HEIGHT_
#define _CHANGE_HEIGHT_
#include "j1Object.h"

class ChangeHeight : public Object {
public:
	ChangeHeight() {

	}
	ChangeHeight(const ChangeHeight& obj) {
		*this = obj;
	}
	~ChangeHeight() {

	}

public: 
	int height;
};


#endif

