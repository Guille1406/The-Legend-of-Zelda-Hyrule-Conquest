#ifndef _WARP_
#define _WARP_
#include "j1Object.h"
#include"j1Render.h"
#include "MainScene.h"
#include "j1Scene.h"
class Warp : public Object {
private:
	
public:
	Warp() {

	}
	Warp(const Warp& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		name = obj.name;
		logic_height = obj.logic_height;
		scene = obj.scene;
		//texture_rect = idle_button;
	}
	~Warp() {

	}
	void Action() {
		App->scene->ChangeScene(scene);
	}

public:

	Scene_ID scene;

};


#endif


