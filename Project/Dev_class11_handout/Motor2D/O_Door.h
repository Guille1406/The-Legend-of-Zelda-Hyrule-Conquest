#ifndef _DOOR_
#define _DOOR_
#include "j1Object.h"
#include "Character.h"
class Door : public Object {
public:
	Door() {

	}
	Door(const Door& obj) {
		*this = obj;
		
	}
	~Door() {

	}

	void Open() {
		for (int i = 0; i < rect.w / 16; i++) {
			for (int n = 0; n < rect.h / 16; n++) {
				iPoint temp;
				temp.x =rect.x + i * 16;
				temp.y = rect.y + n * 16;
				active = false;
				App->map->V_Colision[logic_height][0].data[(temp.y / 16) * 100 + temp.x / 16] = 0;
			}
		}
	};

	void Action() {
		Open();
	}

public:
	bool multi_button = false;
	bool key_needed = false;
	bool open = false;


};


#endif
