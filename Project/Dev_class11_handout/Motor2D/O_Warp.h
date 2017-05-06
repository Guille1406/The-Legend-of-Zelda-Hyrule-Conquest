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
		texture_rect = { 0,0,0,0 };
		warp_pos = obj.warp_pos;
		//texture_rect = idle_button;
	}
	~Warp() {

	}
	void Action() {
		App->scene->ChangeScene(scene);
		App->player->Link->pos = { warp_pos.x * 16, warp_pos.y * 16 };
		App->player->Zelda->pos = { warp_pos.x * 16, warp_pos.y * 16 };
	}

public:

	Scene_ID scene = mainmenu;
	iPoint warp_pos = {0,0};
};


#endif


