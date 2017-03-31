#ifndef _CHEST_
#define _CHEST_
#include "j1Object.h"

class Chest : public Object {
public:
	Chest() {

	}
	Chest(const Chest& obj) {		
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
	}
	~Chest() {
	
	}

public:
	//Objeto que contiene
};


#endif
