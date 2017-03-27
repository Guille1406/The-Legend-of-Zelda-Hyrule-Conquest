#ifndef _BUTTON_
#define _BUTTON_
#include "j1Object.h"
#include"j1Render.h"
class Button : public Object {
private:
	bool triggered;
public:
	Button() {

	}
	Button(const Button& obj) {
		*this = obj;
	}
	~Button() {

	}
	void Action() {
		if(connected_object != NULL)
		this->connected_object->Action();
		
	}

public:
	
};


#endif

