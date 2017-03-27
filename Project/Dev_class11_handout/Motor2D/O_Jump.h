#ifndef _JUMP_
#define _JUMP_
#include "j1Object.h"

class Jump : public Object {
public:
	Jump() {

	}
	Jump(const Jump& obj) {
		*this = obj;
	}
	~Jump() {

	}

};


#endif
