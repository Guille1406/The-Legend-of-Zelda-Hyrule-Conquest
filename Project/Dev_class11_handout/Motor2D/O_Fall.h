#ifndef _FALL_
#define _FALL_
#include "j1Object.h"
#include"j1Render.h"
#include "MainScene.h"
#include "j1Scene.h"
class Fall : public Object {
private:

public:
	Fall() {

	}
	Fall(const Fall& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		fallpos = obj.fallpos;
		texture_rect = { 0,0,0,0 };
		//texture_rect = idle_button;
	}
	~Fall() {

	}
	void Action() {
		
	}

public:
	iPoint fallpos = { 0,0 };
	

};


#endif


