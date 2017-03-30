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
		for (int i = 0; i < connected_object.size(); i++) {

			connected_object[i]->Action();

		}
	}

public:
	
};


#endif

