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
		height = obj.height;
		//texture_rect = idle_button;
	}
	~Warp() {

	}
	void Action() {
		if (App->object->V_Objects.size() > 0) {			
			App->player->Link->pos = { warp_pos.x * 16, warp_pos.y * 16 };
			App->player->Zelda->pos = { warp_pos.x * 16, warp_pos.y * 16 };
			App->player->Link->logic_height = height;
			App->player->Zelda->logic_height = height;
			App->scene->ChangeScene(scene);
		}
	}

public:

	Scene_ID scene = mainmenu;
	iPoint warp_pos = {0,0};
	int height = 0;
};


#endif


