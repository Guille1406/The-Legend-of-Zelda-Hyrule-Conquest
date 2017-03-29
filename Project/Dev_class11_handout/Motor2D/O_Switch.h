#ifndef _LEVER_
#define _LEVER_
#include "j1Object.h"
#include"j1Render.h"
class Lever : public Object {
private:
	bool triggered;
public:
	Lever() {

	}
	Lever(const Lever& obj) {
		*this = obj;
	}
	~Lever() {

	}
	void Action() {
		if (connected_object != NULL)
			this->connected_object->Action();

	}

public:

};


#endif
