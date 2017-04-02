#ifndef _HEART_
#define _HEART_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
class Heart : public Object {
private:
	bool triggered;
public:
	Heart() {

	}
	Heart(const Heart& obj) {
		//*this = obj;
	}
	~Heart() {

	}
	void Pick(Character* player) {
	
	}

	void Action() {
		if (connected_object != NULL)
			this->connected_object->Action();

	}

public:

};


#endif

