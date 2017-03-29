#ifndef _BOSSKEY_
#define _BOSSKEY_
#include "j1Object.h"
#include"j1Render.h"
#include "Character.h"
class Boss_Key : public Object {
private:
	bool triggered;
public:
	Boss_Key() {

	}
	Boss_Key(const Boss_Key& obj) {
		*this = obj;
	}
	~Boss_Key() {

	}
	void Pick(Character* player){
	
	}

	void Action() {
		if (connected_object != NULL)
			this->connected_object->Action();

	}

public:

};


#endif
