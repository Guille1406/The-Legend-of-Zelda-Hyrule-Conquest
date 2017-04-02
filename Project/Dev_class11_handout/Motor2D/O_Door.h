#ifndef _DOOR_
#define _DOOR_
#include "j1Object.h"
#include "Character.h"
#include"j1Player.h"
class Door : public Object {
public:
	Door() {

	}
	Door(const Door& obj) {
		type = obj.type;
		rect = obj.rect;
		active = obj.active;
		open = false;
		name = obj.name;
		logic_height = obj.logic_height;
		collider_tiles = obj.collider_tiles;
		texture_rect = obj.texture_rect;
	}
	~Door() {

	}

	void Open() {

		for (int i = 0; i < this->collider_tiles.size(); i++) {
			if (App->player->loop_game_menu==false) {
				App->map->V_Colision[logic_height]->data[(collider_tiles[i].y / 16) * App->map->data.width + (collider_tiles[i].x / 16)] = 0;
			}
		}
		active = false;
		/*for (int i = 0; i < rect.w / 16; i++) {
			for (int n = 0; n < rect.h / 16; n++) {
				iPoint temp;
				temp.x =rect.x + i * 16;
				temp.y = rect.y + n * 16;
				active = false;
				if(App->map->V_Colision[logic_height][0].data[(temp.y / 16) * 100 + temp.x / 16] == TILE_COL_ID)
				App->map->V_Colision[logic_height][0].data[(temp.y / 16) * 100 + temp.x / 16] = 0;
			}
		}*/
	};

	void Action() {
		Open();
	}

public:
	bool multi_button = false;
	bool key_needed = false;
	bool open = false;
	int dir = 0;
	//Change this
	SDL_Rect closed_door = rect_door_down;
	/*SDL_Rect closed_door_up = rect_door_up;
	SDL_Rect closed_door_left = rect_door_left;
	SDL_Rect closed_door_right = rect_door_right;
	*/
};


#endif

