#ifndef _KEY_
#define _KEY_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
class Key : public Object {
private:
	
public:
	Key() {

	}
	Key(const Key& obj) {
		*this = obj;
	}
	~Key() {

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
