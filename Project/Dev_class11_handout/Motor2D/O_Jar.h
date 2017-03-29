#ifndef _JAR_
#define _JAR_
#include "j1Object.h"
#include"j1Render.h"
class Jar : public Object {
private:
	bool picked;
public:
	Jar() {

	}
	Jar(const Jar& obj) {
		*this = obj;
	}
	~Jar() {

	}

	void Action() {
		if (connected_object != NULL)
			this->connected_object->Action();

	}

public:

};


#endif

