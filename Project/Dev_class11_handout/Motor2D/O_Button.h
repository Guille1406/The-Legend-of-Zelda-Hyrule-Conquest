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

		this->rect = obj.rect;
		this->type = obj.type;
		this->active = obj.active;
	}
	~Button() {

	}
	void Action() {
		//Example
		App->render->DrawQuad({ 100,100,200,200 }, 255, 255, 255, 255, true, true);
	}

};


#endif

