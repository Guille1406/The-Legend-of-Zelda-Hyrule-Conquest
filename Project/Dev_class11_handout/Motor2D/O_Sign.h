#ifndef _SIGN_
#define _SIGN_
#include "j1Object.h"
#include"j1Render.h"
class Sign : public Object {
private:
	char* string;
public:
	Sign() {

	}
	Sign(const Sign& obj) {
		*this = obj;
	}
	~Sign() {

	}
	
	void Action() {
		if (connected_object != NULL)
			this->connected_object->Action();

	}

public:

};


#endif

